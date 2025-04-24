#ifndef INTELHEX_H
#define INTELHEX_H
/***********************************************************************************************
_____________________________________杭州大仁科技有限公司_______________________________________
@文 件 名: IntelHex.c
@日    期: 2016.09.02
@作    者: 张诗星

@文件说明:

IntelHex是用于处理Intel的HEX记录文件的操作库

@修订说明:

2016.09.02  初始版本
2016.09.10  对函数和实现进行重构

***********************************************************************************************/


/*----------------------------------------头文件----------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
/*---------------------------------------常量定义---------------------------------------------*/

#define IHEX_MAX_BINDATA_NUM    (255)       /* 单个记录最大数据大小 */
#define IHEX_RECORD_STR_LEN     (9+IHEX_MAX_BINDATA_NUM*2+2+4)  /* 最大行记录长度 */
#define IHEX_EXTADDR_STR_LEN    (9+4+4)     /* 扩展线性地址最大字符串数量 */
/* bin转换为hex时最大字符缓冲区大小 */
#define IHEX_STRING_BUFF_SIZE   (IHEX_RECORD_STR_LEN+IHEX_EXTADDR_STR_LEN)

/*----------------------------------------常量定义----------------------------------------------*/

//字段偏移量定义
#define OFFSET_BYTE_COUNT		(1) 	/* 字节数量偏移 1字节 */
#define OFFSET_ADDRESS			(3) 	/* 地址字段偏移 2字节 */
#define OFFSET_RECORD_TYPE		(7) 	/* 记录类型字段偏移 1字节 */
#define OFFSET_BIN_DATA 		(9) 	/* 数据字段偏移 1字节 */

/*----------------------------------------内部定义----------------------------------------------*/

/*---------------------------------------枚举定义---------------------------------------------*/
//错误码枚举
typedef enum eErrorEnum
{
    IHEX_RESULT_NOERROR = 0,            /* 无错误 */
    IHEX_RESULT_INVALID_RECORD,         /* 首字符非`:`，非法的记录 */
    IHEX_RESULT_INVALID_CHAR,           /* 16进制存在非法的字符 */
    IHEX_RESULT_INVALID_TYPE,           /* 非法的记录类型 */
    IHEX_RESULT_ERROR_CHECKSUM,         /* 校验和错误 */
    IHEX_RESULT_ERROR_RECORD_COUNT,     /* 数据数量错误 */
    IHEX_RESULT_RECORD_END,             /* 数据记录结束 */
}IHexResult;

//HEX记录类型枚举
typedef enum eRecordTypeEnum
{
    IHEX_TYPE_DATARECORD = 0,       /* 数据记录类型 */
    IHEX_TYPE_ENDFILE    = 1,       /* 文件结束 位于文件最后一行 */
    IHEX_TYPE_EXTSEG     = 2,       /* 扩展段 地址段为0 数据段*16累加在后面所有地址上 */
    IHEX_TYPE_STARTSEG   = 3,       /* 起始段扩展 */
    IHEX_TYPE_EXTADDRESS = 4,       /* 扩展线性地址 地址段为0   数据段为后面所有地址的高16位 */
    IHEX_TYPE_STARTADDRESS  = 5,    /* 起始线性地址记录 */
}HexRecordType;

/*---------------------------------------类型定义---------------------------------------------*/

//HEX记录结构
typedef struct eHexRecord
{
    uint8_t count;          /* 当前记录行数据字节数 */
    uint16_t rcdAddr;       /* 当前记录数据起始地址 */
    HexRecordType type;     /* 当前记录类型 */
    uint32_t fileAddr;      /* 文件地址=当前记录地址+扩展地址 */
    uint32_t extAddr;       /* 用于保存记录中的扩展地址 */
    uint8_t *pbuff;         /* 转换数据缓存内存指针 */

    uint32_t minAddr;       /* 记录中最小地址 */
    uint32_t maxAddr;       /* 记录中最大地址 */
}IHexRecord;

//写HEX描述结构体
typedef struct eHexWirteInfo
{
    uint8_t* pbuff;         /* bin内存区 */
    uint32_t size;          /* bin文件大小 */
    uint32_t startAddr;     /* bin起始偏移地址 */
    uint16_t linewidth;     /* 每行数据字节数量 */

    uint32_t offset;        /* 当前索引 */
}IHexWriteDescribe;
//写入记录结构体
typedef struct
{
    uint16_t rcdAddr;       /* 记录数据起始地址 */
    uint16_t extAddr;       /* 扩展地址 */
    HexRecordType type;     /* 记录类型 */
    uint8_t count;          /* 数据字节数 */
    uint8_t *pbuff;         /* 内存指针 */
}IHEXWriteRecord;

// **************************************************************************
// 类型定义
typedef struct
{
    FILE* rfile;        // 读取文件句柄
    FILE* wfile;        // 写入文件句柄

    uint8_t* binbuff;   // 二进制缓冲区
    uint8_t* rambuff;   // ram数据缓冲区
    char* strbuff;      // 字符串缓冲区
}ConvertContext;

// **************************************************************************
//  内部数据定义

// 字符串资源定义
#define STRING_OPEN_FILEERROR  "打开文件:\"%s\" 时出现错误!\r\n"
#define STRING_MALLO_MEMERROR  "分配内存错误!\r\n"
#define STRING_READ_ERROREND  "读取文件时发现意外的文件结尾!\r\n"
#define STRING_FILE_ERROR  "文件数据错误，错误码为:%d 错误行:%d\r\n"
/*---------------------------------------接口函数---------------------------------------------*/

//兼容C C++混合编程
#ifdef __cplusplus
extern "C" {
#endif

void IHex_InitRecord(IHexRecord* precord, uint8_t* pbuff);
IHexResult IHex_GetNextHeadInfo(IHexRecord* precord, const char * linestr);
IHexResult IHex_GetNextBindata(IHexRecord* precord, const char * str);
void IHex_InitWriteDesc(IHexWriteDescribe* pinfo);
uint32_t IHex_GetNextHexlinestr(IHexWriteDescribe* pinfo, char* str);
void Hex2Bin(const char* rpath, const char* wpath);
void CheckPatchValid(const char* rpath, const char* wpath);
void ExitApplication(ConvertContext* pctx, const char*fmt, ...);
bool CheckSpaceLine(const char* linstr);
void InitContext(ConvertContext* pctx);


uint8_t* Hex2Binfile(const char* rpath,uint32_t fileSize,uint32_t startAddr);
    //兼容C C++混合编程
#ifdef __cplusplus
}
#endif


#endif // INTELHEX_H
