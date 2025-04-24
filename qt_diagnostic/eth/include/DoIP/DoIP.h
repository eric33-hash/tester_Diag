/*******************************************************************************
*
*  File name: DoIP.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
*******************************************************************************
*
* History
*------------------------------------------------------------------------------
*******************************************************************************
* Version: 3.0
* Author/Date: SongQW/2020.02.03
* Change: New created.
* Cause: New
*******************************************************************************
* Version: 3.1
* Author/Date: SongQW/2020.07.01
* Change: Add AutoSAR version.
* Cause: New
*******************************************************************************
* Version: 3.2
* Author/Date: HongYQ/2020.09.06
* Change: Modify DOIP_GATEWAY and DOIP_NODE code generation rules
          Add API Id of DoIP_API_ID_ACTIVATION_LINE_SWITCH.
* Cause: Update.
*******************************************************************************
* Version: 3.3
* Author/Date : HongYQ/2020.09.14
* Change: Add the memory definition of AUTOSAR to the code. 
          By #define DOIP_START_SEC_CODE
             #include "DoIP_MemMap.h" 
             #define DOIP_STOP_SEC_CODE
             #include "DoIP_MemMap.h"
          form realization.
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.4
* Author/Date : HongYQ/2020.09.16
* Change: Convert the definition of the Function declaration to the style
             of AUTOSAR code.
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.5
* Author/Date : HongYQ/2020.10.16
* Change: 1.Modify the AUTOSAR code style (formal parameters).
		  2.2.Complete QAC test.
* Cause: In order to be in accordance with style of AUTOSAR code. And, Improve 
			code quality.
*******************************************************************************
* Version: 3.6
* Author/Date : WangC/2021.9.26
* Change: 1.Modify the Macro of DOIP_MAX_REQUEST_BYTES.
* Cause: Bugfix.
*******************************************************************************
* Version: 3.7
* Author/Date : LiZH/2021.11.1
* Change: Updata versions.
* Cause: Optimize.
********************************************************************************
* Version: 3.8
* Author/Date: WangC/2021.11.11
* Change: Modify header file reference.
* Cause: Optimization.
********************************************************************************
* Version: 3.9
* Author/Date: WangC/2021.11.18
* Change: Modify the patch number.
* Cause: Bugfix.
********************************************************************************
* Version: 3.10
* Author/Date: LiuHJ/2022.05.26
* Change: Add gateway function.
* Cause: New function.
********************************************************************************
* Version: 3.11
* Author/Date: LiuHJ/2022.06.21
* Change: Modify the patch number.
* Cause: Bugfix.
********************************************************************************
* Version: 3.12
* Author/Date: LiuHJ/2022.07.07
* Change: Modify the patch number.
* Cause: Bugfix.
********************************************************************************
* Version: 3.13
* Author/Date: LiuZY/2022.11.07
* Change: Modify the patch number.
* Cause: Optimization.
********************************************************************************
* Version: 3.14
* Author/Date: LiuZY/2022.12.09
* Change: Modify the patch number.
* Cause: Optimization.
********************************************************************************
* Version: 3.15
* Author/Date: LiuZY/2022.12.29
* Change: Modify the patch number.
* Cause: Bugfix.
********************************************************************************
* Version: 3.16
* Author/Date: LiuZY/2023.01.09
* Change: Modify the patch number.
* Cause: Bugfix.
********************************************************************************
* Version: 3.17
* Author/Date: LiuZY/2023.02.06
* Change: Modify the patch number.
* Cause: Optimization.
********************************************************************************

*/
#ifndef DOIP_H_
#define DOIP_H_

/*
*******************************************************************************
*    Includes
*******************************************************************************
*/
//#include "DoIP_Cfg.h"

#include "../TcpIP/client.h"
#include "../Type/Type.h"
#include "../Type/DoIP_Types.h"
#include "DoIP_Lcfg.h"
#include "../Type/Platform_Types.h"
#include "../Type/Std_Types.h"
/*
*******************************************************************************
*    Global Macros
*******************************************************************************
*/
/* Module identification and version*/
#define DOIP_MODULE_ID                            (173U)
#define DOIP_VENDOR_ID                            (119U)
#define DOIP_SW_MAJOR_VERSION                     (3U)
#define DOIP_SW_MINOR_VERSION                     (3U)
#define DOIP_SW_PATCH_VERSION                     (10U)

/* AUTOSAR Version. */
#define DOIP_AR_RELEASE_MAJOR_VERSION             (4U)
#define DOIP_AR_RELEASE_MINOR_VERSION             (4U)
#define DOIP_AR_RELEASE_REVISION_VERSION          (0U)
#define SOAD_INV_SO_CON_ID                      (0xFFFFU)

#define SOAD_IPADDR_STATE_ASSIGNED              (0x00U)
#define SOAD_IPADDR_STATE_ONHOLD                (0x01U)
#define SOAD_IPADDR_STATE_UNASSIGNED            (0x02U)

//用于唯一标识 SoAd 套接字连接的 SoCon 标识符类型。
typedef uint16_t SoAd_SoConIdType ;
struct sockaddr_in    servaddr;
struct sockaddr_in    clientAddr;
struct sockaddr_in    servaddrUDP;
static boolean Flag_DcmStartofReception = FALSE;
extern uint8 sockCon;
extern boolean FlagIsconnect;
extern pthread_mutex_t mutex;

/*
*******************************************************************************
*    Global Types
*******************************************************************************
*/
typedef struct
{
  uint8 config;	/* Not used. */
}DoIP_ConfigType;
/*
*******************************************************************************
*    Global Variables
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Types
*******************************************************************************
*/
// typedef enum	/* Variables of this type shall be used to store the result of a buffer request. */	
// {
// 	BUFREQ_OK,			/* 0: Buffer request accomplished successful. */
// 	BUFREQ_E_NOT_OK,	/* 1: Buffer request not successful. Buffer cannot be accessed. */
// 	BUFREQ_E_BUSY,		/* 2: Temporarily no buffer available. It's up the requester to retry request for a certain time. */
// 	BUFREQ_E_OVFL		/* 3: No Buffer of the required length can be provided. */
// } BufReq_ReturnType;		/* SWS_COMTYPE_00012 */

// typedef enum	/* Variables of this type shall be used to store the state of TP buffer. */
// {
// 	TP_DATACONF,	/* 0x00: TP_DATACONF indicates that all data, that have been 
// 	                   copied so far, are confirmed and can be removed from the TP buffer. */
// 	TP_DATARETRY,	/* 0x01: TP_DATARETRY indicates that this API call shall copy
//                        already copied data in order to recover from an error. */
// 	TP_CONFPENDING	/* 0x02: TP_CONFPENDING indicates that the previously copied data must remain in the TP. */
// } TpDataStateType;	/* SWS_COMTYPE_00027 */

// typedef struct	/* Variables of this type shall be used to store the information about Tp buffer handling. */
// {
// 	TpDataStateType TpDataState;	/* The enum type to be used to store the state of Tp buffer. */
// 	PduLengthType TxTpDataCnt;		/* Offset from the current position which identifies the number of bytes to be retransmitted. */
// } RetryInfoType;	/* SWS_COMTYPE_00037 */

// /* This type shall be used to request the version of a BSW module. */
// typedef struct
// {
//    uint16 vendorID;
//    uint16 moduleID;
//    uint8  sw_major_version;
//    uint8  sw_minor_version;
//    uint8  sw_patch_version;
// } Std_VersionInfoType;	/* SWS_Std_00015 */

/*
*******************************************************************************
*    Global Constants
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Functions
*******************************************************************************
*/
extern void ActiveConfig_Init
(
    PduIdType connnection
);
extern Std_ReturnType DoIP_TpTransmit
(
   // PduIdType connection,
	PduIdType DoIPPduRTxId,
	const PduInfoType* DoIPPduRTxInfoPtr
);
extern Std_ReturnType DoIP_TpCancelTransmit
(
	PduIdType DoIPPduRTxId
);
extern Std_ReturnType DoIP_TpCancelReceive
(
	PduIdType DoIPPduRRxId
);
extern Std_ReturnType DoIP_IfTransmit
(
	PduIdType id,
	const PduInfoType* info
);
extern Std_ReturnType DoIP_IfCancelTransmit(PduIdType id);
extern void DoIP_Init
(
	const DoIP_ConfigType* DoIPConfigPtr
);
extern Std_ReturnType SoAd_GetPhysAddr(uint16 sock,uint8 *mac) ;
extern Std_ReturnType SoAd_IfTransmit(uint16 sock,const PduInfoType* msgStruct);
extern Std_ReturnType DoIP_TcpTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param1,
    uint16 param2,
    uint32 param3,
    SduDataPtrType dataPtr,
    boolean closeSocket
);

#if( STD_ON == DOIP_VERSIONINFOAPI )
extern void DoIP_GetVersionInfo
(
	Std_VersionInfoType* versionInfo
);
#endif
extern BufReq_ReturnType PduR_DoIPTpCopyRxData(   
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr);

extern BufReq_ReturnType PduR_DoIPTpStartOfReception(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)info,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA)bufferSizePtr);
extern void DoIP_ActivationLineSwitchActive(void);
extern void DoIP_ActivationLineSwitchInactive(void);
extern void DoIP_MainFunction(void);
extern Std_ReturnType DoIP_GetSoConIdByConId
(
    uint16 connection,
    SoAd_SoConIdType* soConIdPtr
);
extern void DoIP_Memcpy
(
	uint8* destData, 
	const uint8* srcData, 
	uint32 dataCnt
);

#endif /* DOIP_H_ */