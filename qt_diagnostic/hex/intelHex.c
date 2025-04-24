
/***********************************************************************************************
_____________________________________杭州大仁科技有限公司_______________________________________
@文 件 名: IntelHex.c
@日	期: 2016.09.02
@作	者: 张诗星

@文件说明:

IntelHex是用于处理Intel的HEX记录文件的操作库

@修订说明:

2016.09.02	初始版本
2016.09.10	对函数和实现进行重构

***********************************************************************************************/

/*----------------------------------------头文件----------------------------------------------*/
#include <assert.h>
#include "intelHex.h"


//外部函数引用
uint32_t Bcv_Hexstring2Uint32(const char* pchr, uint8_t len, uint8_t* presult);
void Bcv_Byte2Hexstring(char pdes[], uint8_t adata);
char* Bcv_strcpy(char* dest, const char* source);
char* Bcv_ConvertHexAndSum(char* deststr, void* binbuff, uint8_t count, uint8_t* sum);


/******************************************************************************************
说明:			解析记录头数据[:][字节数][地址][记录类型][数据][CRC]
                用于快速的浏览记录的地址和记录类型等信息
参数:
// @precord		HEX记录指针
// @pchr		字符数组
返回值:	IHEXResult	结果
******************************************************************************************/
static IHexResult ParseHead(IHexRecord* precord, const char pchr[])
{
    uint8_t res = 0;

    //`：`数据起始标志
    if (':' != pchr[0])
        return IHEX_RESULT_INVALID_RECORD;
    //获取字节数
    precord->count = (uint8_t)Bcv_Hexstring2Uint32(&pchr[OFFSET_BYTE_COUNT], 2, &res);
    if (!res)
        return IHEX_RESULT_INVALID_CHAR;
    //获取地址
    precord->rcdAddr = (uint16_t)Bcv_Hexstring2Uint32(&pchr[OFFSET_ADDRESS], 4, &res);
    if (!res)
        return IHEX_RESULT_INVALID_CHAR;
    //获取记录类型
    precord->type = (HexRecordType)Bcv_Hexstring2Uint32(&pchr[OFFSET_RECORD_TYPE], 2, &res);
    if (!res)
        return IHEX_RESULT_INVALID_CHAR;

    //处理各个记录类型
    switch (precord->type)
    {
        /* 数据记录类型 */
    case IHEX_TYPE_DATARECORD:
        if (!precord->count)
            return IHEX_RESULT_ERROR_RECORD_COUNT;

        //计算文件HEX地址
        precord->fileAddr = precord->extAddr + precord->rcdAddr;
        break;
        /* 记录结束 */
    case IHEX_TYPE_ENDFILE:
        if (precord->count)
            return IHEX_RESULT_ERROR_RECORD_COUNT;
        break;
        /* 扩展记录类型 */
    case IHEX_TYPE_EXTADDRESS:
        if (2 != precord->count)
            return IHEX_RESULT_ERROR_RECORD_COUNT;

        //获取地址
        precord->extAddr = Bcv_Hexstring2Uint32(&pchr[OFFSET_BIN_DATA], 4, &res);
        precord->extAddr <<= 16;
        if (!res)
            return IHEX_RESULT_INVALID_CHAR;
        break;
        /* 扩展段记录类型 */
    case IHEX_TYPE_EXTSEG:
        if (2 != precord->count)
            return IHEX_RESULT_ERROR_RECORD_COUNT;

        //获取地址
        precord->extAddr = Bcv_Hexstring2Uint32(&pchr[OFFSET_BIN_DATA], 4, &res);
        precord->extAddr <<= 4;
        if (!res)
            return IHEX_RESULT_INVALID_CHAR;
        break;
    case IHEX_TYPE_STARTSEG:
    case IHEX_TYPE_STARTADDRESS:
        if (4 != precord->count)
            return IHEX_RESULT_ERROR_RECORD_COUNT;

        //获取地址
        precord->fileAddr = Bcv_Hexstring2Uint32(&pchr[OFFSET_BIN_DATA], 8, &res);
        if (!res)
            return IHEX_RESULT_INVALID_CHAR;
        break;
    default:
        return IHEX_RESULT_INVALID_TYPE;
    }
    return IHEX_RESULT_NOERROR;
}
/******************************************************************************************
说明:			转换记录BIN数据
参数:
// @precord		HEX记录指针
// @pchr		字符数组
返回值:	uint8_t	结算结果
******************************************************************************************/
static IHexResult ConvertData(const IHexRecord* precord, const char pchr[])
{
    uint8_t res = 0, temp, i;
    uint8_t sum;

    //计算字节数、地址、记录类型校验和
    sum = precord->count;						/* 字节数 */
    sum += (uint8_t)precord->type;				/* 数据类型 */
    sum += (uint8_t)(precord->rcdAddr >> 8);	/* 地址高字节 */
    sum += (uint8_t)precord->rcdAddr;			/* 地址低字节 */

    pchr = &pchr[OFFSET_BIN_DATA];	/* 数据字段偏移 */
    //解析二进制数据
    for (i = 0; i < precord->count; i++, pchr += 2)
    {
        temp = (uint8_t)Bcv_Hexstring2Uint32(pchr, 2, &res);
        if (!res)
            return IHEX_RESULT_INVALID_CHAR;

        precord->pbuff[i] = temp;	  /* 保存转换结果数值 */
        sum += temp;
    }

    //检查校验和
    temp = (uint8_t)Bcv_Hexstring2Uint32(pchr, 2, &res);
    if (!res)
        return IHEX_RESULT_INVALID_CHAR;
    if ((uint8_t)(temp + sum))
        return IHEX_RESULT_ERROR_CHECKSUM;

    return IHEX_RESULT_NOERROR;
}
/******************************************************************************************
说明:			转换记录为HEX文件字符串
参数:
// @str			字符串
// @precord		记录指针
返回值:	char*	返回字符串末尾指针
******************************************************************************************/
static char* ConvertHexline(char pchr[], IHEXWriteRecord* precord)
{
    uint8_t sum = 0, temp;
    static const char endline[] = ":00000001FF";

    //参数断言
    assert(pchr);
    assert(precord);

    //对于扩展段和扩展地址 强制指定其他字段
    if (IHEX_TYPE_EXTADDRESS == precord->type)
    {
        precord->count = 2;
        precord->rcdAddr = 0;
    }

    //开始转换为记录字符串
    if (IHEX_TYPE_ENDFILE == precord->type)
    {	/* 记录结束 */
        pchr = Bcv_strcpy(pchr, endline);
    }
    else
    {
        // :标志
        pchr[0] = ':';
        // 转换记录头
        Bcv_Byte2Hexstring(&pchr[OFFSET_BYTE_COUNT], precord->count);					/* 字节数量 */
        Bcv_Byte2Hexstring(&pchr[OFFSET_ADDRESS], (uint8_t)(precord->rcdAddr >> 8));	/* 地址高字节 */
        Bcv_Byte2Hexstring(&pchr[OFFSET_ADDRESS + 2], (uint8_t)precord->rcdAddr);		/* 地址低字节 */
        Bcv_Byte2Hexstring(&pchr[OFFSET_RECORD_TYPE], (uint8_t)precord->type);			/* 记录类型 */
        // 计算字节数、地址、记录类型校验和
        sum += precord->count;						/* 字节数 */
        sum += (uint8_t)(precord->rcdAddr >> 8);	/* 地址高字节 */
        sum += (uint8_t)precord->rcdAddr;			/* 地址低字节 */
        sum += (uint8_t)precord->type;				/* 数据类型 */

        // 转换数据
        switch (precord->type)
        {
            /* 数据记录类型 */
        case IHEX_TYPE_DATARECORD:
            pchr = Bcv_ConvertHexAndSum(&pchr[OFFSET_BIN_DATA], precord->pbuff,
                precord->count, &sum);
            break;
            /* 扩展记录类型 */
        case IHEX_TYPE_EXTADDRESS:
            pchr = &pchr[OFFSET_BIN_DATA];
            sum += (temp = (uint8_t)(precord->extAddr >> 8));
            Bcv_Byte2Hexstring(pchr, temp);
            sum += (temp = (uint8_t)(precord->extAddr));
            Bcv_Byte2Hexstring(&pchr[2], temp);
            pchr += 4;
            break;
        default:
            assert(0);
            break;
        }

        //计算校验和
        Bcv_Byte2Hexstring(pchr, (uint8_t)(-sum));
        pchr += 2;
    }

    //添加换行和\0字符
    pchr[0] = '\n';
    pchr[1] = '\0';
    return &pchr[1];
}

/*----------------------------------------接口函数----------------------------------------------*/

/******************************************************************************************
说明:			初始化记录结构体
参数:
// @precord		HEX记录结构体指针
返回值:	void
******************************************************************************************/
void IHex_InitRecord(IHexRecord* precord, uint8_t* pbuff)
{
    //参数断言
    assert(precord);

    precord->fileAddr = 0;
    precord->rcdAddr = 0;
    precord->extAddr = 0;
    precord->count = 0;
    precord->type = IHEX_TYPE_DATARECORD;
    precord->pbuff = pbuff;
    precord->maxAddr = 0;
    precord->minAddr = (uint32_t)-1;
}

/******************************************************************************************
说明:			初始化写结构体
参数:
// @pinfo		HEX写结构体指针
返回值:	void
******************************************************************************************/
void IHex_InitWriteDesc(IHexWriteDescribe* pdes)
{
    //参数断言
    assert(pdes);

    pdes->offset = 0;
}

/******************************************************************************************
说明:			获取下一个记录头
参数:
// @pinfo		HEX记录信息结构体指针
// @precord		HEX记录结构体指针
// @linestr			记录行字符
返回值:	IHEXResult 结果
******************************************************************************************/
IHexResult IHex_GetNextHeadInfo(IHexRecord* precord, const char * linestr)
{
    IHexResult result;

    //参数断言
    assert(precord);
    assert(linestr);

    //遇到结束记录将忽略后面所有的记录
    if (IHEX_TYPE_ENDFILE == precord->type)
        return IHEX_RESULT_RECORD_END;

    //转换记录头数据
    if (IHEX_RESULT_NOERROR != (result = ParseHead(precord, linestr)))
        return result;

    //数据记录类型
    if (IHEX_TYPE_DATARECORD == precord->type)
    {
        uint32_t end = precord->fileAddr + precord->count - 1;
        //获取地址范围信息
        if (precord->maxAddr < end)
            precord->maxAddr = end;
        if (precord->minAddr > precord->fileAddr)
            precord->minAddr = precord->fileAddr;
    }
    return IHEX_RESULT_NOERROR;
}

/******************************************************************************************
说明:			获取下一个记录数据
参数:
// @precord		HEX记录结构体指针
// @linestr			记录行字符
返回值:	IHEXResult 结果
******************************************************************************************/
IHexResult IHex_GetNextBindata(IHexRecord* precord, const char * linestr)
{
    IHexResult result;

    //参数断言
    assert(precord);
    assert(linestr);

    if (IHEX_RESULT_NOERROR != (result = IHex_GetNextHeadInfo(precord, linestr)))
        return result;

    //数据记录类型转换BIN数据
    return ConvertData(precord, linestr);
}

/******************************************************************************************
说明:			获取下一个HEX记录字符串
参数:
// @str			字符串缓冲区
// @pdes		写操作描述结构体指针
返回值:	uint32_t 返回发送索引
******************************************************************************************/
uint32_t IHex_GetNextHexlinestr(IHexWriteDescribe* pinfo, char* str)
{
    IHEXWriteRecord wrecd;
    uint32_t rlen;

    //参数断言
    assert(str);
    assert(pinfo);

    //检查转换是否结束
    if (pinfo->offset >= pinfo->size)
    {
        wrecd.type = IHEX_TYPE_ENDFILE;
        ConvertHexline(str, &wrecd);
        return 0;
    }

    //计算所需发送数据数量
    rlen = pinfo->size - pinfo->offset;
    if (rlen > pinfo->linewidth)
        rlen = pinfo->linewidth;

    if ((pinfo->offset && (pinfo->startAddr & 0xffffu) < rlen) ||	// 地址溢出
        (!pinfo->offset && pinfo->startAddr & 0xffff0000u))		// 首次地址
    {
        wrecd.type = IHEX_TYPE_EXTADDRESS; 		            /* 扩展类型 */
        wrecd.extAddr = (uint16_t)(pinfo->startAddr>>16);   /* 扩展地址 */
        str = ConvertHexline(str, &wrecd);
    }

    //处理数据记录为HEX记录行
    wrecd.type = IHEX_TYPE_DATARECORD;  /* 数据记录类型 */
    wrecd.count = (uint8_t)rlen;        /* 数据数量 */
    wrecd.pbuff = pinfo->pbuff;		    /* 缓冲区 */
    wrecd.rcdAddr = (uint16_t)pinfo->startAddr;	/* HEX记录地址 */
    ConvertHexline(str, &wrecd);

    //处理地址、索引
    pinfo->offset += rlen;
    pinfo->pbuff += rlen;
    pinfo->startAddr += rlen;

    return pinfo->offset;
}


// **************************************************************************
//  内部函数

// 初始化上下文对象
void InitContext(ConvertContext* pctx)
{
    if (pctx)
    {
        pctx->rfile = NULL;
        pctx->wfile = NULL;
        pctx->strbuff = NULL;
        pctx->binbuff = NULL;
        pctx->rambuff = NULL;
    }
}
// 检测空行
bool CheckSpaceLine(const char* linstr)
{
    for (char chr; '\0' != (chr = *linstr); ++linstr)
    {
        if ('\n' == chr || '\r' == chr ||
            ' ' == chr || '\t' == chr)
            continue;
        else
            return false;
    }
    return true;
}
// 退出应用程序
void ExitApplication(ConvertContext* pctx, const char*fmt, ...)
{
    // 打印信息字符串
    if (fmt)
    {
        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
    }

    // 清理使用的资源
    if (pctx)
    {
        if (pctx->rfile) fclose(pctx->rfile);
        if (pctx->wfile) fclose(pctx->wfile);
        if (pctx->binbuff) free(pctx->binbuff);
        if (pctx->strbuff) free(pctx->strbuff);
        if (pctx->rambuff) free(pctx->rambuff);
    }

//    getchar();
}
// 检查路径有效
void CheckPatchValid(const char* rpath, const char* wpath)
{
    if (NULL == rpath || *rpath == '\0' ||
        NULL == wpath || *wpath == '\0')
        ExitApplication(NULL, "输入文件路径为空!...\r\n");
}

//HEX2BIN转换

void Hex2Bin(const char* rpath, const char* wpath)
{
    IHexResult result;
    IHexRecord record;

    ConvertContext ctx;
    InitContext(&ctx);

    // 检查路径有效
    CheckPatchValid(rpath, wpath);
    // 打开HEX文件
    if (NULL == (ctx.rfile = fopen(rpath, "r")))
        ExitApplication(&ctx, STRING_OPEN_FILEERROR, rpath);

    // 分配相应的缓冲内存空间
    if (NULL == (ctx.strbuff = (char*)malloc(IHEX_STRING_BUFF_SIZE)) ||
        NULL == (ctx.binbuff = (uint8_t*)malloc(IHEX_MAX_BINDATA_NUM)))
        ExitApplication(&ctx, STRING_MALLO_MEMERROR);

    // 读取HEX信息以分配内存空间
    uint32_t startaddress = 0;
    IHex_InitRecord(&record, ctx.binbuff);
    for (int clen = 0;;)
    {
        if (NULL == fgets(ctx.strbuff, IHEX_RECORD_STR_LEN, ctx.rfile))
            ExitApplication(&ctx, STRING_READ_ERROREND);

        ++clen;
        if (CheckSpaceLine(ctx.strbuff))       // 空行
            continue;

        result = IHex_GetNextHeadInfo(&record, ctx.strbuff);
        if (IHEX_RESULT_NOERROR != result)
            ExitApplication(&ctx, STRING_FILE_ERROR, result, clen);
        else if (record.type == IHEX_TYPE_STARTADDRESS)
        {
            startaddress = record.fileAddr;
        }
        else if (record.type == IHEX_TYPE_ENDFILE)
        {
            printf("文件:\"%s\" 读取成功\r\n", rpath);
            printf("文件记录数据范围为:0X%08X - 0X%08X\r\n", record.minAddr, record.maxAddr);
            printf("共: %d 字节数据 %d 行\r\n", record.maxAddr- record.minAddr + 1, clen);
            if (startaddress)
                printf("起始地址为：0X%08X\r\n", startaddress);
            break;
        }
    }

    const uint32_t bytenum = record.maxAddr - record.minAddr + 1;
    //分配内存并填充0xff
    if (NULL == (ctx.rambuff = (uint8_t*)malloc(bytenum)))
        ExitApplication(&ctx, "分配内存错误!\r\n");
    memset(ctx.rambuff, 0xff, bytenum);
    // 打开写入文件
    if (NULL == (ctx.wfile = fopen(wpath, "wb")))
        ExitApplication(&ctx, STRING_OPEN_FILEERROR, wpath);

    // 开始解析hex文件并保存数据
    rewind(ctx.rfile);              // 重定位读取文件
    IHex_InitRecord(&record, ctx.binbuff);
    for (int clen = 0;;)
    {
        if (NULL == fgets(ctx.strbuff, IHEX_RECORD_STR_LEN, ctx.rfile))
            ExitApplication(&ctx, STRING_READ_ERROREND);

        ++clen;
        if (CheckSpaceLine(ctx.strbuff))       // 空行
            continue;

        if (IHEX_RESULT_NOERROR != (result = IHex_GetNextBindata(&record, ctx.strbuff)))
            ExitApplication(&ctx, STRING_FILE_ERROR, result, clen);
        else if (record.type == IHEX_TYPE_ENDFILE)
        {
            fwrite(ctx.rambuff, 1, bytenum, ctx.wfile);
            ExitApplication(&ctx, "转换数据完成\r\n");
        }
        else if (record.type == IHEX_TYPE_DATARECORD)
            memcpy(ctx.rambuff + (record.fileAddr - record.minAddr), ctx.binbuff, record.count);
    }
}


uint8_t* Hex2Binfile(const char* rpath,uint32_t fileSize,uint32_t startAddr)
{
    IHexResult result;
    IHexRecord record;

    ConvertContext ctx;
    InitContext(&ctx);

    uint32_t currentDataFileAddr = 0;
    uint32_t endDataFileAddr = 0;
    int blockIndex = 1;

    if (NULL == (ctx.rfile = fopen(rpath, "r")))
        ExitApplication(&ctx, STRING_OPEN_FILEERROR, rpath);

    // 分配相应的缓冲内存空间
    if (NULL == (ctx.strbuff = (char*)malloc(IHEX_STRING_BUFF_SIZE)) ||
        NULL == (ctx.binbuff = (uint8_t*)malloc(IHEX_MAX_BINDATA_NUM)))
        ExitApplication(&ctx, STRING_MALLO_MEMERROR);

    uint32_t bytenum = fileSize;
    //分配内存并填充0xff
    if (NULL == (ctx.rambuff = (uint8_t*)malloc(bytenum)))
        ExitApplication(&ctx, "分配内存错误!\r\n");
    memset(ctx.rambuff, 0xff, bytenum);

    // 开始解析hex文件并保存数据
    rewind(ctx.rfile);              // 重定位读取文件
    IHex_InitRecord(&record, ctx.binbuff);
    for (int clen = 0;;)
    {
        if (NULL == fgets(ctx.strbuff, IHEX_RECORD_STR_LEN, ctx.rfile))
            ExitApplication(&ctx, STRING_READ_ERROREND);

        ++clen;
        if (CheckSpaceLine(ctx.strbuff))       // 空行
            continue;

        if (IHEX_RESULT_NOERROR != (result = IHex_GetNextBindata(&record, ctx.strbuff)))
            ExitApplication(&ctx, STRING_FILE_ERROR, result, clen);
        else if (record.type == IHEX_TYPE_ENDFILE ||bytenum == 0)
        {
            return ctx.rambuff;
           break;
        }
        else if ((record.type == IHEX_TYPE_DATARECORD) && (record.fileAddr >= startAddr) )
        {
            if(bytenum >= 0)
            {
                memcpy(ctx.rambuff + (record.fileAddr - startAddr), ctx.binbuff, record.count);

            }
            bytenum -= record.count;
        }

    }
}
