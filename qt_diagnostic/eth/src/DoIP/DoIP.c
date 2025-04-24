/*
*******************************************************************************
*
*  File name: DoIP.c
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
*******************************************************************************
*
* History
*------------------------------------------------------------------------------
*******************************************************************************
* Version: 3.0
* Author/Date : SongQW/2020.02.03
* Change: New created.
* Cause: New
*******************************************************************************
* Version: 3.1
* Author/Date : HongYQ/2020.09.09
* Change: Add routing activation, diagnosis request, vehicle request,
*           node status, diagnosis mode, and connect to gateway functions.
* Cause: Add gataway functions.
*******************************************************************************
* Version: 3.2
* Author/Date : HongYQ/2020.09.11
* Change: Modify VehicleAnnounmentWaitTime and VehicleAnnounmentCount parameter
*          definition of Alive Check .
*          Add DoIP_RefreshDhcpHostName function of DoIP.
*          Add SoAd_RequestIpAddrAssignment function of DoIP.
* Cause: Update.
*******************************************************************************
* Version: 3.3
* Author/Date : HongYQ/2020.09.13
* Change:
*          Increase DoIP_SoAdTpStartOfReception requirement realization.
*          Modify the discrimination conditions in DoIP_SoAdIfRxIndication
*          and DoIP_SoAdIfTxConfirmation.
*          Increase the shape parameter of the DoIP_UdpTransmit function.
*          Add DOIP_MAX_TESTER_CONNECTIONS generation rules, and modify the
*          code of entity status.
* Cause: Update.
*******************************************************************************
* Version: 3.4
* Author/Date : HongYQ/2020.09.14
* Change: Add the memory definition of AUTOSAR to the code.
*          By #define DOIP_START_SEC_CODE
*             #include "DoIP_MemMap.h"
*             #define DOIP_STOP_SEC_CODE
*             #include "DoIP_MemMap.h"
*          form realization
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.5
* Author/Date : HongYQ/2020.09.16
* Change: Convert the definition of the static Function declaration variable
*          and Function implementation to the style of AUTOSAR code.
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.6
* Author/Date : HongYQ/2020.10.16
* Change: 1.Modify the AUTOSAR code style (formal parameters).
*         2.Complete QAC test.
* Cause: In order to be in accordance with style of AUTOSAR code. And, Improve
*        code quality.
*******************************************************************************
* Version: 3.7
* Author/Date : HongYQ/2021.1.27
* Change: 1.Remove #pragma.
* Cause: For different compilers, pre-compiled #pragma is used in different
*        ways, and memory segmentation is implemented in Memmap.
*******************************************************************************
* Version: 3.8
* Author/Date : HongYQ/2021.2.23
* Change: 1.Modify the status judgment in DoIP_LocalIpAddrAssignmentChg.
*         2.Change the ASCII code in the DoIP_RefreshDhcpHostName function
*           to hexadecimal.
* Cause: For different compilers, pre-compiled #pragma is used in different
*        ways, and memory segmentation is implemented in Memmap.
*******************************************************************************
* Version: 3.9
* Author/Date : WangC/2021.9.26
* Change: 1.Modify the processing of DoIP_RefreshDhcpHostName.
*         2.Modify the processing of DoIP_CopyTpDataHandler.
* Cause: BugFix.
*******************************************************************************
* Version: 3.10
* Author/Date : WangC/2021.11.11
* Change: Activation line processing.
* Cause: Optimization.
*******************************************************************************
* Version: 3.11
* Author/Date : WangC/2021.11.18
* Change: Mainfunction processing.
* Cause: Bugfix.
*******************************************************************************
* Version: 3.12
* Author/Date : WangC/2021.11.18
* Change: Modify the problem that the socket cannot be closed.
* Cause: Bugfix.
*******************************************************************************
* Version: 3.13
* Author/Date : WangC/2021.11.22
* Change: Modify the socket processing according to SoAd.
* Cause: Bugfix.
*******************************************************************************
* Version: 3.14
* Author/Date: LiuHJ/2022.05.26
* Change: Add gateway function.
* Cause: New function.
********************************************************************************
* Version: 3.15
* Author/Date: LiuHJ/2022.06.21
* Change: Bugfix for CCOREPBUG-2306.
* Cause: Bugfix.
********************************************************************************
* Version: 3.16
* Author/Date: LiuHJ/2022.07.07
* Change: Bugfix for CCOREDBUG-833.
* Cause: Bugfix.
********************************************************************************
* Version: 3.17
* Author/Date: LiuZY/2022.11.07
* Change: Modification of coding specification.
* Cause: Optimization
********************************************************************************
* Version: 3.18
* Author/Date: LiuZY/2022.12.09
* Change: When receiving TP copy message timeout, remove the route activation
*         status judgment.
* Cause: Bugfix.
********************************************************************************
* Version: 3.19
* Author/Date: LiuZY/2022.12.29
* Change: Copy TP data, the packet length is less than or equal to the length
*         of the read data, and reset the flag.
* Cause: Bugfix.
********************************************************************************
* Version: 3.20
* Author/Date: LiuZY/2023.02.06
* Change: Modify the returned NACK value when the data length field does not 
          match the actual value.
* Cause: Optimization.
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "eth/include/DoIP/DoIP.h"
#include "eth/include/Dcm/Dcm_Cbk.h"
#include "eth/include/Dcm/Dcm.h"
#include "pthread.h"
#include <signal.h>
//#include "DoIP_Lcfg.h"
//#include "DoIP_Cbk.h"

//#include "SoAd.h"
//#include "PduR_DoIP.h"

#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
//#include "Det.h"
#endif  /* DOIP_DEV_ERROR_DETECT == STD_ON */

//#include "SchM_DoIP.h"

/*
*******************************************************************************
*    Local Macros
*******************************************************************************
*/
#ifndef DOIP_LOCAL
#define DOIP_LOCAL static
#endif

#ifndef DOIP_LOCAL_INLINE
#define DOIP_LOCAL_INLINE LOCAL_INLINE
#endif

#define DOIP_LOCAL_DEBUG         STD_OFF
#define DOIP_TCP_TP_OPTIMZED     STD_OFF

#define DOIP_ENTER_CRITICAL0     SchM_Enter_DoIP_DOIP_EXCLUSIVE_AREA_0
#define DOIP_EXIT_CRITICAL0      SchM_Exit_DoIP_DOIP_EXCLUSIVE_AREA_0

/*
*******************************************************************************
*    Local Types
*******************************************************************************
*/
#if ( DOIP_LOCAL_DEBUG == STD_ON )
typedef struct
{
    uint16_t txStateError;
    uint16_t txLenError;
    uint16_t txQueEmpty;
    uint16_t txBufReqFail;
} DoIP_DebugTcpTxCount_st;

typedef struct
{
    uint16_t rxTimeout;
    uint16_t rxStateError;
    uint16_t rxLenError;
    uint16_t rxRouteActBusy;
    uint16_t rxAckPending;
    uint16_t rxInvalidVer;
    uint16 rxMissRouteAct;
} DoIP_DebugTcpRxCount_st;
#endif

/*
*******************************************************************************
*    Local Variables
*******************************************************************************
*/
#define DOIP_START_SEC_VAR_INIT
//#include "DoIP_MemMap.h"
DOIP_LOCAL DoIP_StateType DoIP_State = DOIP_STATE_UNINIT;

#if ( DOIP_LOCAL_DEBUG == STD_ON )
DOIP_LOCAL VAR(DoIP_DebugTcpTxCount_st, DOIP_VAR_INIT) DoIP_DebugTxCnt[DOIP_CONNECTION_TCP_TOTAL] = {{0}};
DOIP_LOCAL VAR(DoIP_DebugTcpRxCount_st, DOIP_VAR_INIT) DoIP_DebugRxCnt[DOIP_CONNECTION_TCP_TOTAL] = {{0}};
#endif

#define DOIP_STOP_SEC_VAR_INIT
//#include "DoIP_MemMap.h"


#define DOIP_START_SEC_VAR_NO_INIT
//#include "DoIP_MemMap.h"

DOIP_LOCAL VAR(DoIP_ActivationLineLocalType, DOIP_VAR_NO_INIT) DoIP_ActivationLineLocalState;
DOIP_LOCAL VAR(boolean, DOIP_VAR_NO_INIT) DoIP_GidInSync;
DOIP_LOCAL VAR(uint16, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxMsgWaitCnt[DOIP_CONNECTION_TOTAL];
#define DOIP_STOP_SEC_VAR_NO_INIT
#include "../../include/DoIP/DoIP_MemMap.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
*******************************************************************************
*    Local Constants
*******************************************************************************
*/
#ifndef DOIP_UDP_MAX_RETRY_CNT
/* depending on MainFunction cycle */
#define DOIP_UDP_MAX_RETRY_CNT               (6000U)
#endif /* ifndef DOIP_UDP_MAX_RETRY_CNT */

/*
*******************************************************************************
*    Local Functions
*******************************************************************************
*/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetTesterIdxByTesterAddr
(
    uint16 testerAddr,
    P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) testerIdx
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_GetConnectionOfTesterAddr
(
    uint16 testerAddr,
    P2VAR(PduIdType, AUTOMATIC, DOIP_APPL_DATA)connection
);

DOIP_LOCAL_INLINE FUNC(uint16, DOIP_CODE) DoIP_FindChannelBySAAndTA
(
    uint16 sourceAddr,
    uint16 targetAddr
);
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(PduIdType, DOIP_CODE) DoIP_FindForwardConnection
(
    uint16 sourceAddr,
    uint16 targetAddr
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ForwardRouteActiveReq
(
    uint8 routActIdx,
    uint16 sourceAddr,
    PduIdType fwConnection
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TriggerSendRouteActiveReq
(
    PduIdType connection,
    SoAd_SoConModeType mode
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleRelatedClientTcpCon
(
    PduIdType connection,
    SoAd_SoConModeType mode
);
#endif
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ActivateConnectionAtChannel
(
    uint8 routActIdx,
    PduIdType connection,
    uint16 testerAddr
);

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_PerformAuthConfAndActivateRouting(PduIdType id);
DOIP_LOCAL FUNC(PduIdType, DOIP_CODE) DoIP_GetAvailableSockNum(PduIdType id, uint8 localAddrIdx);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpFinishTransmit(PduIdType connection);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Det_ErrorReport(uint8 apiId, uint8 errorId);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_FillGenHdr
(
    uint16 hdrType,
    uint32 hdrLen,
    P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA)tgtBufferPtr
);
DOIP_LOCAL FUNC(uint8, DOIP_CODE) DoIP_GetFreeIdxInTcpTxQueue
(
    PduIdType connection
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_GenNackTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveAckTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    uint16 param2,
    uint32 param3
);
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveReqTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    uint16 param2,
    uint32 param3,
    VAR(SduDataPtrType, AUTOMATIC)dataPtr
);
#endif
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_AliveCheckReqTxHandler
(
    uint8 elementIdx,
    PduIdType connection
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) SchM_Enter_DoIP_DOIP_EXCLUSIVE_AREA_0(void)
{
    //SuspendAllInterrupts();
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) SchM_Exit_DoIP_DOIP_EXCLUSIVE_AREA_0(void)
{
    //ResumeAllInterrupts();
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagReqTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    PduLengthType param3,
    VAR(SduDataPtrType, AUTOMATIC)dataPtr
);

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagAckTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagNackTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    uint16 param2,
    uint32 param3
);
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TcpTxQueueAddElement
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param1,
    uint16 param2,
    uint32 param3,
    VAR(SduDataPtrType, AUTOMATIC)dataPtr
);
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TcpTxQueueSend(PduIdType connection);

DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_UdpTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param,
    boolean closeSocket
);
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_UdpSingleTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RemoveAliveCheckFromRoutActHandler
(
    PduIdType connection
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveReqRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
);
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveAckRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
);
#endif
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_AliveCheckAckRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HeaderAndDataCopy
(
    PduIdType id,
    PduLengthType expectLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
);
#if( DOIP_NACK_APPEND_REQ == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagNAckAppendReqCopy
(
    PduIdType id,
    PduLengthType dataLen,
    PduLengthType readDataLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info
);
#endif
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpPreTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param1,
    uint16 param2,
    uint8 param3,
    boolean closeSocket
);
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ClientDiagReqRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
);
#endif
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ServerDiagReqRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
);
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_ClientCopyTpRxDataHandler
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) continueFlag
);
#endif
DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_ServerCopyTpRxDataHandler
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) continueFlag
);
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpClientCopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr
);
#endif
DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpServerCopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_CloseSoCon(PduIdType connection);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_CloseSoConUDP(PduIdType connection);
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TcpTxQueueCopyDiagReqData
(
    boolean headerCopied,
    PduIdType connection,
    uint32 txMgtQueIdx,
    P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_DATA) pduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) availableDataPtr
);
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TcpTxQueueCopyDiagNAckData
(
    boolean headerCopied,
    PduIdType connection,
    uint32 txMgtQueIdx,
    P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_DATA) pduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) availableDataPtr
);
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TcpTxQueueCopyElement
(
    PduIdType connection,
    P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_DATA)pduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA)availableDataPtr
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpTxQueueRemoveElement
(
    PduIdType connection,
    Std_ReturnType result
);
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetConnectionBySoConId
(
    SoAd_SoConIdType SoConId,
    P2VAR(PduIdType, AUTOMATIC, DOIP_APPL_DATA)connection
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_SoAdIfRxDataOfHdrTyp
(
    PduIdType RxPduId,
    uint16 srcHdrType,
    uint32 srcHdrLen,
    uint32 dataOffset,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)PduInfoPtr,
    boolean closeSocket
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_OpenSockConInitially(PduIdType connection);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RefreshDhcpHostName(SoAd_SoConIdType soConId);
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_ASCIICompare
(
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST)refervalue,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST)comparevalue,
    uint8 length
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_CopyData
(
    P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA)destinAddr,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST)sourceAddr,
    uint8 length
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ActLineToActive(void);

#if( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ActLineToInactive(void);
#endif

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleSockConStates(void);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleGidSync(void);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleAuthConf(PduIdType id);

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleCloseSocketInUdpTxList(uint16 udpTxListIdx);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleUdpTxList(void);
void DoIP_HandleUDPSocketState();
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpRx_HandleAliveCheckTimeouts(PduIdType id);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleTcpTxQueue(void);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Tcp_HandleRxMsgTimeouts(void);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TerminateCurrTcpRx
(
    PduIdType connection
);
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpRx_HandleInactivityTimeouts(void);

extern FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetSoConIdByConId
(
    uint16 connection,
    SoAd_SoConIdType* soConIdPtr
);

INLINE int getResultFromSystemCall(const char* pCmd, uint8* pResult, int size);
INLINE Std_ReturnType SoAd_ReadDhcpHostNameOption
(
    SoAd_SoConIdType SoConId,
    uint8* length,
    uint8* data
);

/*
*******************************************************************************
*    Global Variables
*******************************************************************************
*/
#define DOIP_START_SEC_VAR_INIT
//#include "DoIP_MemMap.h"

VAR(DoIP_ActivationLineType, DOIP_VAR_NO_INIT) DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_INACTIVE;
VAR(boolean, DOIP_VAR_NO_INIT) DoIP_VehicleAnncSendFlag = TRUE;

uint8 sockCon = SOAD_INV_SO_CON_ID;

boolean FlagIsconnect = FALSE;
#define DOIP_STOP_SEC_VAR_INIT
//#include "DoIP_MemMap.h"

/*
*******************************************************************************
*    Global Constants
*******************************************************************************
*/
/*
*******************************************************************************
*    Local Function
*******************************************************************************
*/
#define DOIP_START_SEC_CODE
//#include "DoIP_MemMap.h"
/*
*******************************************************************************
* Function Name: DoIP_GetTesterIdxByTesterAddr
*
* Explanation: Function to get tester index by tester address.
*
* param: testerAddr: Tester address.
*        testerIdx: Tester index.
*
* retval: DOIP_E_OK: Getting is sucessful.
*         DOIP_E_NOT_OK: Getting is unsucessful.
*******************************************************************************
*/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetTesterIdxByTesterAddr
(
    uint16 testerAddr,
    P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) testerIdx
)
{
    Std_ReturnType retVal = DOIP_E_NOT_OK;
    uint8 currIdx = DOIP_TESTER_TOTAL+1U;

    if( testerIdx != NULL_PTR )
    {
        *testerIdx = DOIP_INV_TESTER_IDX;
        while( currIdx >= DOIP_ZERO && currIdx <= (DOIP_TESTER_TOTAL+1U))
        {
            if( DoIP_Tester[currIdx].testerAddr == testerAddr )
            {
                *testerIdx = currIdx;
                retVal = DOIP_E_OK;
                break;
            }
            currIdx--;
        }
    }

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_GetConnectionOfTesterAddr
*
* Explanation: Function to get connection of tester address.
*
* param: testerAddr: Tester address.
*        connection: Connection index.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_GetConnectionOfTesterAddr
(
    uint16 testerAddr,
    P2VAR(PduIdType, AUTOMATIC, DOIP_APPL_DATA) connection
)
{
    PduIdType idx;

    if( NULL_PTR != connection )
    {
        *connection = DOIP_INV_PDU_ID;
        for( idx = 0u; idx < DOIP_CONNECTION_TOTAL; idx++ )
        {
          if( DoIP_TcpCon2ActivMgt[idx].testerAddr == testerAddr )
          {
            *connection = idx;
            break;
          }
        }
    }
}

DOIP_LOCAL_INLINE FUNC(uint16, DOIP_CODE) DoIP_FindChannelBySAAndTA
(
    uint16 sourceAddr,
    uint16 targetAddr
)
{
    uint16 channel = DOIP_INV_PDU_ID;
    uint16 loopIdx;
    for( loopIdx = DOIP_ZERO; loopIdx < DOIP_CHANNELS_TOTAL; loopIdx++ )
    {
        // if( (DoIP_Channel2EcuAddr[loopIdx] == targetAddr) && (DoIP_Channel2SourceAddr[loopIdx] == sourceAddr) )
        // {
        //     channel = loopIdx;
        //     break;
        // }
        if(DoIP_Channel2EcuAddr[loopIdx] == targetAddr)
        {
            for( loopIdx = DOIP_ZERO; loopIdx < DOIP_CHANNELS_TOTAL; loopIdx++ )
            {
                if(DoIP_Channel2SourceAddr[loopIdx] == sourceAddr)
                {
                    channel = loopIdx;
                }
            }

        }
    }
    return channel;
}

#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(PduIdType, DOIP_CODE) DoIP_FindForwardConnection
(
    uint16 sourceAddr,
    uint16 targetAddr
)
{
    uint16 connection = DOIP_CONNECTION_TCP_TOTAL;
    uint16 loopIdx;
    for( loopIdx = DOIP_ZERO; loopIdx < DOIP_CHANNELS_TOTAL; loopIdx++ )
    {
        if( (DoIP_Channel2EcuAddr[loopIdx] == sourceAddr) && (DoIP_Channel2SourceAddr[loopIdx] == targetAddr) )
        {
            /* Find tcp client connection. */
            if( DoIP_Channel2DefaultTcpCon[loopIdx] != DOIP_INV_PDU_ID )
            {
                connection = DoIP_Channel2DefaultTcpCon[loopIdx];
                break;
            }
        }
    }
    return connection;
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ForwardRouteActiveReq
(
    uint8 routActIdx,
    uint16 sourceAddr,
    PduIdType fwConnection
)
{
    if( fwConnection < DOIP_CONNECTION_TCP_TOTAL )
    {
        if( (sourceAddr == DoIP_TcpCon2ActivMgt[fwConnection].testerAddr) &&
            (DoIP_TcpCon2ActivMgt[fwConnection].activState != DOIP_ROUT_ACTIV_STATE_NONE) )
        {
            /* Nothing to do */
        }
        else
        {
            DoIP_TcpCon2ActivMgt[fwConnection].testerAddr = sourceAddr;
            DoIP_TcpCon2ActivMgt[fwConnection].actType = DoIP_RoutingActivations[routActIdx].routingActivationNum;
            DoIP_TcpCon2ActivMgt[fwConnection].oemSpecUsed = DoIP_RoutActivHandler[fwConnection].oemSpecUsed;
            DoIP_TcpCon2ActivMgt[fwConnection].oemSpecReq[DOIP_ZERO] = DoIP_RoutActivHandler[fwConnection].oemSpecReq[DOIP_ZERO];
            DoIP_TcpCon2ActivMgt[fwConnection].oemSpecReq[DOIP_ONE] = DoIP_RoutActivHandler[fwConnection].oemSpecReq[DOIP_ONE];
            DoIP_TcpCon2ActivMgt[fwConnection].oemSpecReq[DOIP_TWO] = DoIP_RoutActivHandler[fwConnection].oemSpecReq[DOIP_TWO];
            DoIP_TcpCon2ActivMgt[fwConnection].oemSpecReq[DOIP_THREE] = DoIP_RoutActivHandler[fwConnection].oemSpecReq[DOIP_THREE];

            if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[fwConnection] )
            {
                (void)DoIP_TcpTransmit(fwConnection, DOIP_HDR_TYPE_ROUT_ACTIV_REQ,
                                       sourceAddr,
                                       DoIP_TcpCon2ActivMgt[fwConnection].actType,
                                       DoIP_TcpCon2ActivMgt[fwConnection].oemSpecUsed,
                                       DoIP_TcpCon2ActivMgt[fwConnection].oemSpecReq,
                                       FALSE);
                DoIP_TcpCon2ActivMgt[fwConnection].activState = DOIP_ROUT_ACTIV_STATE_ACTIVATING;
            }
            else
            {
                //(void)SoAd_OpenSoCon(DoIP_Con2SoConId[fwConnection]);
                DoIP_TcpCon2ActivMgt[fwConnection].activState = DOIP_ROUT_ACTIV_STATE_TOACTIVATE;
            }
        }

    }
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TriggerSendRouteActiveReq
(
    PduIdType connection,
    SoAd_SoConModeType mode
)
{
    if( (DOIP_CONNECTION_TCP_TOTAL > connection) && (SOAD_SOCON_ONLINE == mode) )
    {
        if( (TRUE == DoIP_IsTcpClientConnection[connection]) &&
            (DOIP_ROUT_ACTIV_STATE_TOACTIVATE == DoIP_TcpCon2ActivMgt[connection].activState) )
        {
            (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_REQ,
                                   DoIP_TcpCon2ActivMgt[connection].testerAddr,
                                   DoIP_TcpCon2ActivMgt[connection].actType,
                                   DoIP_TcpCon2ActivMgt[connection].oemSpecUsed,
                                   DoIP_TcpCon2ActivMgt[connection].oemSpecReq,
                                   FALSE);
            DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_ACTIVATING;
        }
    }
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleRelatedClientTcpCon
(
    PduIdType connection,
    SoAd_SoConModeType mode
)
{
    PduIdType loopIdx;
    if( (DOIP_CONNECTION_TCP_TOTAL > connection) && (SOAD_SOCON_ONLINE != mode) )
    {
        if( (FALSE == DoIP_IsTcpClientConnection[connection]) &&
            (DOIP_ROUT_ACTIV_STATE_ACTIVATED == DoIP_TcpCon2ActivMgt[connection].activState) )
        {
            for( loopIdx = DOIP_CONNECTION_TCP_SERVER_TOTAL; loopIdx < DOIP_CONNECTION_TCP_TOTAL; loopIdx++ )
            {
                if( DoIP_TcpCon2ActivMgt[loopIdx].testerAddr == DoIP_TcpCon2ActivMgt[connection].testerAddr )
                {
                    DoIP_Con2SoConClosing[loopIdx] = TRUE;
                    DoIP_CloseSoCon(loopIdx);
                }
            }
        }
    }
}
#endif

/*
*******************************************************************************
* Function Name: DoIP_ActivateConnectionAtChannel
*
* Explanation: Function to activate connection at channel.
*
* param: routActIdx: Routing actived index.
*        connection: Connection index.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ActivateConnectionAtChannel
(
    uint8 routActIdx,
    PduIdType connection,
    uint16 testerAddr
)
{
    uint8 channelNum = DoIP_RoutingActivations[routActIdx].channelNum;

    /* Set connection active on all corresponding channels */
    while( DOIP_ZERO < channelNum )
    {
        PduIdType channel;
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
        PduIdType fwConnection;
#endif
        channelNum--;

        if( NULL_PTR != DoIP_RoutingActivations[routActIdx].targetAddrPtr )
        {
            channel = DoIP_FindChannelBySAAndTA(testerAddr, DoIP_RoutingActivations[routActIdx].targetAddrPtr[channelNum]);
            if( channel < DOIP_CHANNELS_TOTAL )
            {
                DoIP_Channel2TcpCon[channel] = connection;
            }
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
            fwConnection = DoIP_FindForwardConnection(testerAddr, DoIP_RoutingActivations[routActIdx].targetAddrPtr[channelNum]);
            DoIP_ForwardRouteActiveReq(routActIdx, testerAddr, fwConnection);
#endif
        }
    }
}

/*
*******************************************************************************
* Function Name: DoIP_PerformAuthConfAndActivateRouting
*
* Explanation: Function to perform authentication confirmation and activate routing.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_PerformAuthConfAndActivateRouting
(
    PduIdType id
)
{
    uint8 routActIdx = DoIP_RoutActivHandler[id].routActIdx;
    uint8 offsetReq = DOIP_ZERO;
    uint8 offsetRes = DOIP_ZERO;
    boolean authentified = FALSE;
    boolean confirmed = FALSE;
    Std_ReturnType retVal = DOIP_E_OK;

    uint16 testerAddr = DoIP_RoutActivHandler[id].testerAddr;
    PduIdType connection = DoIP_RoutActivHandler[id].tcpCon;
    uint32 testerIdx = DoIP_RoutActivHandler[id].testerIdx;;




    //skip AuthConfAndActivateRouting
    DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
    DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
    DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;

    /* Set mapping for connection and channels. */
    DoIP_ActivateConnectionAtChannel(routActIdx, connection, testerAddr);

    /* Routing activated. */
    DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_ACTIVATED;

    /* Reset inactivity counter. */
    DoIP_TcpCon2InactivCnt[connection] = DOIP_ZERO;
    (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                       DOIP_ROUT_ACTIV_RES_CODE_SUCCESS, testerIdx, NULL_PTR, FALSE);

    /* Check OEM part. */
    /******
    if( ((boolean)FALSE == DoIP_RoutActivHandler.oemSpecUsed) &&
         ((DOIP_ZERO != DoIP_RoutingActivations[routActIdx].authReqLength) ||
          (DOIP_ZERO != DoIP_RoutingActivations[routActIdx].confReqLength)) )
    {
        /* Routing activation requires OEM specific part. 
        DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;

        (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                               DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);
    }
    else
    {
        /* Call authentication callback. 
        if( NULL_PTR != DoIP_RoutingActivations[routActIdx].authFuncPtr )
        {
            retVal = DoIP_RoutingActivations[routActIdx].authFuncPtr(&authentified,
                               DoIP_RoutActivHandler.oemSpecReq, DoIP_RoutActivHandler.oemSpecRes);

            if( (Std_ReturnType)E_NOT_OK == retVal )
            {
                /* Authentication failed. 
                /* Register tester. 
                DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
                DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
                DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;
                DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;

                (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                       DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);

                retVal = DOIP_E_NOT_OK;
            }
            else if( DOIP_E_PENDING == retVal )
            {
                /* Authentication pending. 
                /* Register tester. 
                DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
                DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
                DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;
                DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_AUTH_PENDING;

                retVal = DOIP_E_NOT_OK;
            }
            else
            {
                /* Authentication successful (callback return value) 
                if( (boolean)TRUE != authentified )
                {
                    /* Authentication failed 
                    /* Register tester 
                    DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
                    DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
                    DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;
                    DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;

                    (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                           DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);

                    retVal = DOIP_E_NOT_OK;
                }
            }
        }
        if( (Std_ReturnType)DOIP_E_OK == retVal )
        {
            /* Call confirmation callback. 
            if( NULL_PTR != DoIP_RoutingActivations[routActIdx].confFuncPtr )
            {
                if( DOIP_ZERO < DoIP_RoutingActivations[routActIdx].confReqLength )
                {
                    offsetReq = (uint8)(DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE - DoIP_RoutingActivations[routActIdx].confReqLength);
                }
                if( DOIP_ZERO < DoIP_RoutingActivations[routActIdx].confResLength )
                {
                    offsetRes = (uint8)(DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE - DoIP_RoutingActivations[routActIdx].confResLength);
                }

                retVal = DoIP_RoutingActivations[routActIdx].confFuncPtr(&confirmed,
                                                  &DoIP_RoutActivHandler.oemSpecReq[offsetReq],
                                                  &DoIP_RoutActivHandler.oemSpecRes[offsetRes]);
                if( (Std_ReturnType)E_NOT_OK == retVal )
                {
                    /* Confirmation failed. 
                    /* Register tester. 
                    DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
                    DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
                    DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;
                    DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;

                    (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                           DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED, testerIdx, NULL_PTR, TRUE);
                    retVal = DOIP_E_NOT_OK;
                }
                else if( DOIP_E_PENDING == retVal )
                {
                    /* Confirmation pending. *
                    /* Register tester. *
                    DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
                    DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
                    DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;
                    DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_CONF_PENDING;

                    /* SWS_DoIP_00114 *
                    (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                           DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REQUIRED, testerIdx, NULL_PTR, FALSE);
                    retVal = DOIP_E_NOT_OK;
                }
                else
                {
                    /* Confirmation successful (callback return value). *
                    if( (boolean)TRUE != confirmed )
                    {
                        /* Confirmation failed. *
                        /* Register tester. *
                        DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
                        DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
                        DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;
                        DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;

                        (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                               DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED, testerIdx, NULL_PTR, TRUE);
                        retVal = DOIP_E_NOT_OK;
                    }
                }
            }

            if( (Std_ReturnType)DOIP_E_OK == retVal )
            {
                /* Register tester. *
                DoIP_TcpCon2ActivMgt[connection].testerIdx = testerIdx;
                DoIP_TcpCon2ActivMgt[connection].testerAddr = testerAddr;
                DoIP_TcpCon2ActivMgt[connection].routActIdx = routActIdx;

                /* Set mapping for connection and channels. *
                DoIP_ActivateConnectionAtChannel(routActIdx, connection, testerAddr);

                /* Routing activated. *
                DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_ACTIVATED;

                /* Reset inactivity counter. *
                DoIP_TcpCon2InactivCnt[connection] = DOIP_ZERO;

                /* [SWS_DoIP_00220] *
                (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                       DOIP_ROUT_ACTIV_RES_CODE_SUCCESS, testerIdx, NULL_PTR, FALSE);
            }
        }
    }
****/

}

/*
*******************************************************************************
* Function Name: DoIP_GetAvailableSockNum
*
* Explanation: Function to get available sock number.
*
* param: localAddrIdx: Local address index.
*
* retval: availableSockNum: Current available socket number.
*******************************************************************************
*/
DOIP_LOCAL FUNC(PduIdType, DOIP_CODE) DoIP_GetAvailableSockNum
(
    PduIdType connection,
    uint8 localAddrIdx
)
{
    PduIdType localSoAdRxPduId = DOIP_TESTER_TOTAL;
    PduIdType routActivNum = DOIP_ZERO;
    PduIdType connectionNum = DOIP_ZERO;
    PduIdType availableSockIndex = DOIP_ZERO;

    while( DOIP_ZERO <= localSoAdRxPduId &&  localSoAdRxPduId <= DOIP_TESTER_TOTAL)
    {
    
        if( DoIP_Con2LocalAddrIdx[localSoAdRxPduId] == localAddrIdx )
        {
            /* Local address index match. */
            connectionNum++;
            if( DOIP_INV_TESTER_IDX != DoIP_TcpCon2ActivMgt[localSoAdRxPduId].testerIdx )
            {
                /* Tester connected. */
                routActivNum++;
            }
        }
        localSoAdRxPduId--;
    }

    if( (connectionNum - routActivNum) > DOIP_ONE )
    {
        availableSockIndex = (uint8)(connectionNum - routActivNum - DOIP_ONE);
    }
    return availableSockIndex;
}

/*
*******************************************************************************
* Function Name: DoIP_TcpFinishTransmit
*
* Explanation: Function to transmit the tcp messages.
*
* param: connection: Current connection index.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpFinishTransmit
(
    PduIdType connection
)
{
    if( DOIP_HDR_TYPE_INVALID != DoIP_TcpCon2TpPreTransMgt[connection].hdrType )
    {
        /* PrepareTransmit function called before. */
        /* Call transmit function to send message. */
        (void)DoIP_TcpTransmit(connection,
                              DoIP_TcpCon2TpPreTransMgt[connection].hdrType,
                              DoIP_TcpCon2TpPreTransMgt[connection].param1,
                              DoIP_TcpCon2TpPreTransMgt[connection].param2,
                              DoIP_TcpCon2TpPreTransMgt[connection].param3,
                              NULL_PTR,
                              DoIP_TcpCon2TpPreTransMgt[connection].closeSocket);
                              //DoIP_TcpCon2TpPreTransMgt[connection].closeSocket);
        DoIP_TcpCon2TpPreTransMgt[connection].hdrType = DOIP_HDR_TYPE_INVALID;
    }
}

/*
*******************************************************************************
* Function Name: DoIP_Det_ErrorReport
*
* Explanation: Function to report Error to Det.
*
* param: apiId: Unique Api ID of DoIP manager service.
*        errorId: Det Error ID of DoIP manager.
*
* retval: None
*******************************************************************************
*/
void DoIP_Det_ErrorReport
(
    uint8 apiId,
    uint8 errorId
)
{

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_E_NO_ERROR != errorId )  /* Error detected is on. */
    {
        /* Report error to Det. */
        printf("apiId:%d,errorId:",apiId,errorId);
        //(void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID_DET, apiId, errorId);
    }
#else
    {
        /* Dummy. */
        DOIP_DUMMY_STATEMENT(apiId);
        DOIP_DUMMY_STATEMENT(errorId);
    }
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_FillGenHdr
*
* Explanation: Function to report Error to Det.
*
* param: hdrType: Header type.
*        hdrLen: Header length.
*        TgtBufferPtr: Target buffer pointer.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_FillGenHdr
(
    uint16 hdrType,
    uint32 hdrLen,
    uint8* tgtBufferPtr
)
{
    if( tgtBufferPtr != NULL_PTR )
    {
        /* Header version. */
        tgtBufferPtr[DOIP_ZERO] = DOIP_PROTOCOL_VERSION;
        /* Inverse header version */
        tgtBufferPtr[DOIP_ONE] = (uint8)(~tgtBufferPtr[DOIP_ZERO]);
        /* Header type. */
        tgtBufferPtr[DOIP_TWO] = (uint8)(hdrType >> DOIP_EIGHT);
        tgtBufferPtr[DOIP_THREE] = (uint8)(hdrType);
        /* Header length. */
        tgtBufferPtr[DOIP_FOUR] = (uint8)(hdrLen >> DOIP_TWENTYFOUR);
        tgtBufferPtr[DOIP_FIVE] = (uint8)(hdrLen >> DOIP_SIXTEEN);
        tgtBufferPtr[DOIP_SIX] = (uint8)(hdrLen >> DOIP_EIGHT);
        tgtBufferPtr[DOIP_SEVEN] = (uint8)(hdrLen);
    }
}

DOIP_LOCAL FUNC(uint8, DOIP_CODE) DoIP_GetFreeIdxInTcpTxQueue
(
    PduIdType connection
)
{
    uint8 elementIdx = DOIP_ZERO;

    if( (DoIP_TcpCon2TxMgtQueIdx[connection] + DoIP_TcpCon2TxMgtQueLvl[connection]) >= DOIP_TCP_TX_MGT_QUEUE_SIZE )
    {
        /* Wrap around necessary. */
        if( (DOIP_TCP_TX_MGT_QUEUE_SIZE > DoIP_TcpCon2TxMgtQueIdx[connection]) &&
            (DoIP_TcpCon2TxMgtQueLvl[connection] > (DOIP_TCP_TX_MGT_QUEUE_SIZE - DoIP_TcpCon2TxMgtQueIdx[connection])) )
        {
            elementIdx = (uint8)(DoIP_TcpCon2TxMgtQueLvl[connection] - (DOIP_TCP_TX_MGT_QUEUE_SIZE - DoIP_TcpCon2TxMgtQueIdx[connection]));
        }
    }
    else
    {
        /* No wrap around necessary. */
        elementIdx = (uint8)(DoIP_TcpCon2TxMgtQueIdx[connection] + DoIP_TcpCon2TxMgtQueLvl[connection]);
    }
    return elementIdx;
}


DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_GenNackTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1
)
{
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
    if( FALSE == DoIP_IsTcpClientConnection[connection] )
#endif
    {
        uint8 nackCode = (uint8)param1;
        /* Fill DoIP header in Tx buffer. */
        /* Generic header. */
        DoIP_FillGenHdr(DOIP_HDR_TYPE_GEN_NACK,
                        DOIP_GEN_HDR_NACK_CODE_LEN_BYTE,
                        &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);

        /* NACK Code. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_GEN_HDR_LEN_BYTE];
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ZERO] = nackCode;

        /* set txMgt struct */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen = DOIP_GEN_HDR_LEN_BYTE + DOIP_GEN_HDR_NACK_CODE_LEN_BYTE;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength = DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO];
        DoIP_TcpCon2TxMgtQueLvl[connection]++;
    }
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveAckTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    uint16 param2,
    uint32 param3
)
{
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
    if( FALSE == DoIP_IsTcpClientConnection[connection] )
#endif
    {
        uint8 ackCode = (uint8)param2;
        uint16 testAddr = param1;
        uint16 entityAddr = DOIP_ADDR;
        PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;
        uint32 testerIdx = param3;
        uint8* oemSpecPtr;

        /* Fill DoIP header in Tx buffer. */
        /* Routing activation response. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_GEN_HDR_LEN_BYTE];
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ZERO] = (uint8)(testAddr >> DOIP_EIGHT);
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ONE] = (uint8)(testAddr);
        bufIdx++;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TWO] = (uint8)(entityAddr >> DOIP_EIGHT);
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_THREE] = (uint8)(entityAddr);
        bufIdx++;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_FOUR] = ackCode;
        bufIdx++;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_FIVE] = DOIP_ZERO;
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_SIX] = DOIP_ZERO;
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_SEVEN] = DOIP_ZERO;
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_EIGHT] = DOIP_ZERO;
        bufIdx++;

        /* Identify tester. */
        if( DOIP_INV_ADDR_IDX == testerIdx )
        {
            /* Unknown tester. */
            /* Generic header. */
            DoIP_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_ACK, DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE,
                           &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
        }
        else
        {
            /* Check if OEM specific data shall be added. */
            if( DOIP_INV_ROUT_ACT_IDX != DoIP_TcpCon2ActivMgt[connection].routActIdx )
            {
                /* Routing activation determined. */
                if( ((DOIP_ZERO == DoIP_RoutingActivations[DoIP_TcpCon2ActivMgt[connection].routActIdx].authResLength) &&
                     (DOIP_ZERO == DoIP_RoutingActivations[DoIP_TcpCon2ActivMgt[connection].routActIdx].confResLength)) ||
                     (DOIP_ROUT_ACTIV_STATE_ACTIVATED != DoIP_TcpCon2ActivMgt[connection].activState) )
                {
                    /* No OEM specific data. */
                    DoIP_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_ACK, DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE,
                                   &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
                }
                else
                {
                    /* Add OEM specific data. */
                    oemSpecPtr = DoIP_RoutActivHandler[connection].oemSpecRes;

                    /* Generic header. */
                    DoIP_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_ACK, DOIP_ROUT_ACTIV_ACK_MAX_LEN_BYTE,
                                   &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);

                    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_NINE] = oemSpecPtr[DOIP_ZERO];
                    bufIdx++;
                    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TEN] = oemSpecPtr[DOIP_ONE];
                    bufIdx++;
                    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ELEVEN] = oemSpecPtr[DOIP_TWO];
                    bufIdx++;
                    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TWELVE] = oemSpecPtr[DOIP_THREE];
                    bufIdx++;
                }
            }
            else
            {
                /* Not routing activation determined. */
                /* No OEM specific data. */
                DoIP_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_ACK, DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE,
                               &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
            }
        }

        /* Set txMgt struct. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen    = bufIdx;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength  = bufIdx;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO];
        DoIP_TcpCon2TxMgtQueLvl[connection]++;
    }
}

#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveReqTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    uint16 param2,
    uint32 param3,
    VAR(SduDataPtrType, AUTOMATIC)dataPtr
)
{
    if( TRUE == DoIP_IsTcpClientConnection[connection] )
    {
        uint8 activeType = (uint8)param2;
        uint16 testAddr = param1;
        PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;
        boolean oemSpecUsed = (boolean)param3;
        uint8* oemSpecPtr;

        /* Fill DoIP header in Tx buffer. */
        /* Routing activation response. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_GEN_HDR_LEN_BYTE];
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ZERO] = (uint8)(testAddr >> DOIP_EIGHT);
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ONE] = (uint8)(testAddr);
        bufIdx++;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TWO] = activeType;
        bufIdx++;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_THREE] = DOIP_ZERO;
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_FOUR] = DOIP_ZERO;
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_FIVE] = DOIP_ZERO;
        bufIdx++;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_SIX] = DOIP_ZERO;
        bufIdx++;

        /* Identify tester. */
        if( (TRUE == oemSpecUsed) && (dataPtr != NULL_PTR) )
        {
            /* Add OEM specific data. */
            oemSpecPtr = dataPtr;

            /* Generic header. */
            DoIP_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_REQ, DOIP_ROUT_ACTIV_REQ_MAX_LEN_BYTE,
                            &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);

            DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_SEVEN] = oemSpecPtr[DOIP_ZERO];
            bufIdx++;
            DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_EIGHT] = oemSpecPtr[DOIP_ONE];
            bufIdx++;
            DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_NINE] = oemSpecPtr[DOIP_TWO];
            bufIdx++;
            DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TEN] = oemSpecPtr[DOIP_THREE];
            bufIdx++;
        }
        else
        {
            DoIP_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_REQ, DOIP_ROUT_ACTIV_REQ_MIN_LEN_BYTE,
                            &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
        }

        /* Set txMgt struct. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen    = bufIdx;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength  = bufIdx;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO];
        DoIP_TcpCon2TxMgtQueLvl[connection]++;
    }
}
#endif

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_AliveCheckReqTxHandler
(
    uint8 elementIdx,
    PduIdType connection
)
{
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
    if( FALSE == DoIP_IsTcpClientConnection[connection] )
#endif
    {
        /* Fill DoIP header in Tx buffer. */
        /* Generic header. [SWS_DoIP_00139]*/
        DoIP_FillGenHdr(DOIP_HDR_TYPE_ALIVE_CHECK_REQ, DOIP_ZERO, &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);

        /* Set txMgt struct. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen    = DOIP_GEN_HDR_LEN_BYTE;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength  = DOIP_GEN_HDR_LEN_BYTE;
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO];
        DoIP_TcpCon2TxMgtQueLvl[connection]++;
    }
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagReqTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    PduLengthType param3,
    VAR(SduDataPtrType, AUTOMATIC)dataPtr
)
{
    PduIdType channel = (PduIdType)param1;
    PduLengthType length = (PduLengthType)param3;
    PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;

    /* Fill DoIP header in Tx buffer. */
    /* Generic header. */
    DoIP_FillGenHdr(DOIP_HDR_TYPE_DIAG_REQ, (DOIP_DIAG_HDR_LEN_BYTE + length),
                   &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);

    /* Diagnostic message. */
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_GEN_HDR_LEN_BYTE];
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ZERO] = (uint8)(DoIP_Channel2EcuAddr[channel] >> DOIP_EIGHT);
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ONE] = (uint8)DoIP_Channel2EcuAddr[channel];
    bufIdx += DOIP_ADDR_LEN_BYTE;
#if 0
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TWO] =
                            (uint8)(DoIP_Tester[DoIP_TcpCon2ActivMgt[connection].testerIdx].testerAddr >> DOIP_EIGHT);
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_THREE] =
                            (uint8)DoIP_Tester[DoIP_TcpCon2ActivMgt[connection].testerIdx].testerAddr;
#endif
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TWO] = (uint8)(DoIP_Channel2SourceAddr[channel] >> DOIP_EIGHT);
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_THREE] = (uint8)DoIP_Channel2SourceAddr[channel];
    bufIdx += DOIP_ADDR_LEN_BYTE;

    /* Set txMgt struct. */
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].channel = channel;
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen = bufIdx;
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength = bufIdx + length;
    /* Standard diagnostic message. */
    DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO];
    memcpy(&DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr[DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_HDR_LEN_BYTE],dataPtr,param3);
    //DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = dataPtr;
    DOIP_DUMMY_STATEMENT(dataPtr);
    DoIP_TcpCon2TxMgtQueLvl[connection]++;
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagAckTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1
)
{
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
    if( FALSE == DoIP_IsTcpClientConnection[connection] )
#endif
    {
        uint8 testerIdx = DoIP_TcpCon2ActivMgt[connection].testerIdx;
        uint16 ecuAddr = param1;
        PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;

        /* Fill DoIP header in Tx buffer. */
        /* Generic header. */
#if( DOIP_NACK_APPEND_REQ == STD_ON )
        DoIP_FillGenHdr(DOIP_HDR_TYPE_DIAG_ACK, DOIP_DIAG_MSG_ACK_LEN_BYTE + DoIP_Tester2DiagNAckOffset[testerIdx],
                        &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
#else
        DoIP_FillGenHdr(DOIP_HDR_TYPE_DIAG_ACK, DOIP_DIAG_MSG_ACK_LEN_BYTE,
                        &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
#endif /* STD_ON == DOIP_NACK_APPEND_REQ */

        /* Diagnostic message positive ack. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_GEN_HDR_LEN_BYTE];

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ZERO] = (uint8)(ecuAddr >> DOIP_EIGHT);
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ONE] = (uint8)ecuAddr;
        bufIdx += DOIP_ADDR_LEN_BYTE;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TWO] = (uint8)(DoIP_Tester[testerIdx].testerAddr >> DOIP_EIGHT);
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_THREE] = (uint8)DoIP_Tester[testerIdx].testerAddr;
        bufIdx += DOIP_ADDR_LEN_BYTE;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_FOUR] = DOIP_DIAG_MSG_RES_CODE_ACK;
        bufIdx++;

        /* Set txMgt struct. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen = bufIdx;
#if( DOIP_NACK_APPEND_REQ == STD_ON )
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength = (PduLengthType)(bufIdx + DoIP_Tester2DiagNAckOffset[testerIdx]);
#else
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength  = bufIdx;
#endif /* (DOIP_NACK_APPEND_REQ == STD_ON) */

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO];
        DoIP_TcpCon2TxMgtQueLvl[connection]++;
    }
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagNackTxHandler
(
    uint8 elementIdx,
    PduIdType connection,
    uint16 param1,
    uint16 param2,
    uint32 param3
)
{
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
    if( FALSE == DoIP_IsTcpClientConnection[connection] )
#endif
    {
        uint8 ackCode = (uint8)param3;
#if( DOIP_NACK_APPEND_REQ == STD_ON )
        uint8 testerIdx = DoIP_TcpCon2ActivMgt[connection].testerIdx;
#endif
        uint16 ecuAddr = param1;
        uint16 testAddr = param2;
        PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;

        /* Fill DoIP header in Tx buffer. */
        /* Generic header. */
#if( DOIP_NACK_APPEND_REQ == STD_ON )
        if( testerIdx !=  DOIP_INV_TESTER_IDX )
        {
           /* Tester known. */
           /* Send diagnostic message negative ack with configured amount of user data */
           DoIP_FillGenHdr(DOIP_HDR_TYPE_DIAG_NACK, DOIP_DIAG_MSG_NACK_LEN_BYTE + DoIP_Tester2DiagNAckOffset[testerIdx],
                           &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
        }
        else
#endif /* STD_ON == DOIP_NACK_APPEND_REQ */
        {
           /* Unknown tester. */
           /* Send diagnostic message negative ack without user data. */
           DoIP_FillGenHdr(DOIP_HDR_TYPE_DIAG_NACK, DOIP_DIAG_MSG_NACK_LEN_BYTE,
                           &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO]);
        }

        /* Diagnostic message negative ack. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_GEN_HDR_LEN_BYTE];
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ZERO] = (uint8)(ecuAddr >> DOIP_EIGHT);
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_ONE] = (uint8)ecuAddr;
        bufIdx += DOIP_ADDR_LEN_BYTE;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_TWO] = (uint8)(testAddr >> DOIP_EIGHT);
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_THREE] = (uint8)testAddr;
        bufIdx += DOIP_ADDR_LEN_BYTE;

        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txData[DOIP_FOUR] = ackCode;
        bufIdx += DOIP_ONE;

        /* Set txMgt struct. */
        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHdrBufLen = bufIdx;

        if( testerIdx !=  DOIP_INV_TESTER_IDX )
        {
           /* Tester known. */
           /* Send diagnostic message negative ack with configured amount of user data */
           DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength = (PduLengthType)(bufIdx + DoIP_Tester2DiagNAckOffset[testerIdx]);
        }
        else
        {
            DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduLength  = bufIdx;
        }


        DoIP_TcpCon2TcpTxMgt[connection][elementIdx].msg.SduDataPtr = &DoIP_TcpCon2TcpTxMgt[connection][elementIdx].txHeader[DOIP_ZERO];
        DoIP_TcpCon2TxMgtQueLvl[connection]++;
    }
}

/*
*******************************************************************************
* Function Name: DoIP_TcpTxQueueAddElement   tcp send function
*
* Explanation: Add element to Tcp tx queue.
*
* param: connection: Connection index.
*        hdrType: Header type.
*        param1: Parameter 1.
*        param2: Parameter 2.
*        param3: Parameter 3.
*        dataPtr: Data pointer.
*
* retval: DOIP_E_OK: Add element to tcp Tx queue successfully.
*         DOIP_E_NOT_OK: Add element to tcp Tx queue unsuccessfully.
*******************************************************************************
*/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TcpTxQueueAddElement
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param1,
    uint16 param2,
    uint32 param3,
    SduDataPtrType dataPtr
)
{
    uint8 elementIdx;
    Std_ReturnType retVal = DOIP_E_NOT_OK;
    /* Check if Tx Queue can handle this request. */
    if( DoIP_TcpCon2TxMgtQueLvl[connection] < DOIP_TCP_TX_MGT_QUEUE_SIZE )
    {
        /* Find next free entry in Tx Queue. */
        elementIdx = DoIP_GetFreeIdxInTcpTxQueue(connection);
        switch( hdrType )
        {
            case DOIP_HDR_TYPE_GEN_NACK:
            {
                DoIP_GenNackTxHandler(elementIdx, connection, param1);
                break;
            }
            /* [SWS_DoIP_00220] */
            case DOIP_HDR_TYPE_ROUT_ACTIV_ACK:
            {
                DoIP_RouteActiveAckTxHandler(elementIdx, connection, param1, param2, param3);
                break;
            }
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
            case DOIP_HDR_TYPE_ROUT_ACTIV_REQ:
            {
                DoIP_RouteActiveReqTxHandler(elementIdx, connection, param1, param2, param3, dataPtr);
                break;
            }
#endif
            case DOIP_HDR_TYPE_ALIVE_CHECK_REQ:
            {
                DoIP_AliveCheckReqTxHandler(elementIdx, connection);
                break;
            }
            case DOIP_HDR_TYPE_DIAG_REQ:
            {
                DoIP_DiagReqTxHandler(elementIdx, connection, param1, param3, dataPtr);
                break;
            }
            case DOIP_HDR_TYPE_DIAG_ACK:
            {
                DoIP_DiagAckTxHandler(elementIdx, connection, param1);
                break;
            }
            case DOIP_HDR_TYPE_DIAG_NACK:
            {
                DoIP_DiagNackTxHandler(elementIdx, connection, param1, param2, param3);
                break;
            }
            default:
            {
                /* Nothing to do. */
                break;
            }
        }

        /* Update Tx Queue. */
        /* DoIP_TcpCon2TxMgtQueLvl[connection]++; */

        retVal = E_OK;
    }

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_TcpTxQueueSend
*
* Explanation: Queue send function of the Tcp.
*
* param: connection: Current Tcp connection.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpTxQueueSend
(
    PduIdType connection
)
{
    PduInfoType txMgtMsg = {NULL_PTR, DOIP_ZERO};
    uint32 txMgtQueIdx;
    DOIP_ENTER_CRITICAL0();
    if( (boolean)FALSE == DoIP_TcpCon2TxTpSessionActive[connection] )
    {
        /* No transmission is requested for this socket connection. */
        /* Lock since this function can be called reentrant. */
        DoIP_TcpCon2TxTpSessionActive[connection] = TRUE;

        if( DOIP_ZERO < DoIP_TcpCon2TxMgtQueLvl[connection] )
        {
            txMgtQueIdx = DoIP_TcpCon2TxMgtQueIdx[connection];
            txMgtMsg.SduDataPtr = DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].msg.SduDataPtr;
            txMgtMsg.SduLength = DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].msg.SduLength;
            DOIP_EXIT_CRITICAL0();
            /* Request transmission at SoAd. */
            Std_ReturnType ret = E_NOT_OK;
            ret = sendMsg(DoIP_Con2SoConId[connection], &txMgtMsg);


            if((Std_ReturnType)E_OK == ret)
           // if( (Std_ReturnType)E_OK == SoAd_TpTransmit(DoIP_Con2SoAdTxPduId[connection], &txMgtMsg) )
            {
                /* Transmission request succeeded. */
                /* Nothing to do. */
            }
            else if(ret == 2)
            {
                /* Transmission request failed. */
                DoIP_CloseSoCon(connection);
            }
            else
            {
                DoIP_TcpCon2TxTpSessionActive[connection] = FALSE;
            }
        }
        else
        {
            /* Queue is empty. */
            DoIP_TcpCon2TxTpSessionActive[connection] = FALSE;
            DOIP_EXIT_CRITICAL0();
        }
    }
    else
    {
        DOIP_EXIT_CRITICAL0();
    }
}

/*
*******************************************************************************
* Function Name: DoIP_TcpTransmit
*
* Explanation: Function to transfer data from the PduRouter to the SoAd.
*
* param: connection: Current Tcp connection index.
*        hdrType: header type.
*        param1: Parameter 1.
*        param2: Parameter 2.
*        param3: Parameter 3.
*        dataPtr: Data pointer.
*        closeSocket: current socket state.
*
* retval: DOIP_E_OK: Tcp transmint sucessfully.
          DOIP_E_NOT_OK: Tcp transmint unsucessfully.
*******************************************************************************
*/



FUNC(Std_ReturnType, DOIP_CODE) DoIP_TcpTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param1,
    uint16 param2,
    uint32 param3,
    SduDataPtrType dataPtr,
    boolean closeSocket
)
{
    Std_ReturnType retVal = DOIP_E_NOT_OK;
    DOIP_ENTER_CRITICAL0();
    /* Check socket connection state. */
    if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[connection] )
    {
        /* Socket connection online. [SWS_DoIP_00130] */
        if( (uint8)TRUE != DoIP_Con2SoConClosing[connection] )
        {
            /* Socket is not requested to be closed by a prevoius transmission request. */
            /* Add element to Tx Queue. */
            //printf("dataPtr = %x,%x \n",dataPtr[0],dataPtr[1]);
            retVal = DoIP_TcpTxQueueAddElement(connection, hdrType, param1, param2, param3, dataPtr);

            if( (Std_ReturnType)DOIP_E_OK == retVal )
            {
               
                //DOIP_EXIT_CRITICAL0();
                /* Start transmission of Tx Queue. */
                DoIP_TcpTxQueueSend(connection);
                if( (boolean)TRUE == closeSocket )
                {
                    /* Socket shall be closed after sending this message. [SWS_DoIP_00058] */
                    DoIP_CloseSoCon(connection);
                    ActiveConfig_Init(connection);
                }
                Std_ReturnType result = E_OK;
                DoIP_TcpTxQueueRemoveElement(connection,result);
            }
            else
            {
                DOIP_EXIT_CRITICAL0();
                /* No memory in TxQueue available. */
                DoIP_Det_ErrorReport(DOIP_API_ID_TCP_TRANSMIT, DOIP_E_NOBUFS);
            }
           
        }
        else
        {
            DOIP_EXIT_CRITICAL0();
        }
    }
    else
    {
        DOIP_EXIT_CRITICAL0();
    }

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_UdpTransmit
*
* Explanation: Function to transfer data from the PduRouter to the SoAd on UDP.
*
* param: connection: Current Udp connection index.
*        hdrType: header type.
*        param: Parameter.
*        closeSocket: current socket state.
*
* retval: DOIP_E_OK: Udp transmint sucessfully.
          DOIP_E_NOT_OK: Udp transmint unsucessfully.
*******************************************************************************
*/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_UdpTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param,
    boolean closeSocket
)
{
    boolean otherEntryFound = FALSE;
    Std_ReturnType retVal = DOIP_E_NOT_OK;
    uint16 msgIdx = DOIP_UDP_TX_MGT_LIST_SIZE;

   if( DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT != hdrType )
    {
        /* No Vehicle Announcement. */
        /* Try to send message immediately. */
        retVal = DoIP_UdpSingleTransmit(connection, hdrType, param);
    }

    if( (Std_ReturnType)DOIP_E_OK == retVal )
    {
        /* Check if response is pending for this socket connection. */
        while( DOIP_ZERO < msgIdx )
        {
            msgIdx--;
            if( connection == DoIP_UdpTxMgtList[msgIdx].udpCon )
            {
                /* Response pending. */
                otherEntryFound = TRUE;
                break;
            }
        }

        if( (boolean)FALSE == otherEntryFound )
        {
            /* Close socket connection directly (abort flag set to FALSE). */
            if( (boolean)TRUE == closeSocket )
            {
                //DoIP_CloseSoCon(connection);
                DoIP_CloseSoConUDP(connection);
            }
        }
        else
        {
            /* Close socket connection after list does not contain elements for this connection anymore. */
            DoIP_Con2SoConClosing[connection] |= closeSocket;
        }
    }
    else
    {
        /* Message has not been sent immediately. */
        /* Try to find an empty list element. */
        msgIdx = DOIP_UDP_TX_MGT_LIST_SIZE;
        while( DOIP_ZERO < msgIdx )
        {
            msgIdx--;
            if( DOIP_INV_PDU_ID == DoIP_UdpTxMgtList[msgIdx].udpCon )
            {
                /* Element is not used. */
                /* Write element. */
                DoIP_UdpTxMgtList[msgIdx].udpCon = connection;
                DoIP_UdpTxMgtList[msgIdx].hdrType = hdrType;
                DoIP_UdpTxMgtList[msgIdx].retryAttempt = DOIP_UDP_MAX_RETRY_CNT;
                /* Write message specific parameter */
                if( DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT == hdrType )
                {
                    /* Vehicle Announcement/Vehicle Identification Response timer. */
                    DoIP_UdpTxMgtList[msgIdx].param1 = DOIP_ANNOUNCE_WAIT;
                }
                /* Number of announcements, nack code, power mode, OEM specific header type. */
                DoIP_UdpTxMgtList[msgIdx].param2 = param;

                DoIP_Con2SoConClosing[connection] |= closeSocket;

                retVal = DOIP_E_OK;
                break;
            }
        }
    }
    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_UdpSingleTransmit
*
* Explanation: Function to transfer data on UDP.
*
* param: connection: Current Udp connection index.
*        hdrType: header type.
*        param: Parameter.
*
* retval: DOIP_E_OK: Udp transmint sucessfully.
*         DOIP_E_NOT_OK: Udp transmint unsucessfully.
*******************************************************************************
*/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_UdpSingleTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param
)
{
    Std_ReturnType retVal = DOIP_E_NOT_OK;
    Std_ReturnType vinRetVal;
    uint8 vinIdx = DOIP_VIN_LEN_BYTE;
#if( DOIP_GID_AVAILABLE == STD_OFF )
    uint8 gidIdx = DOIP_GID_LEN_BYTE;
#endif
#if( DOIP_TESTER_WITH_CEN_SEC_AVAILABLE == STD_ON )
    uint8 routActIdx = DOIP_ACTIVE_CONNECTION_SIZE;
#endif
    DoIP_FurtherActionByteType furActByte = DOIP_ZERO;

#if( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
    uint8 physAddrBuf[DOIP_HWID_LEN_BYTE];
#endif /* ( STD_ON == DOIP_VUSE_MAC_ADDR_FOR_IDENT ) */

    uint16 logAddr;
    uint16 ackIdx = DOIP_GEN_HDR_LEN_BYTE;
    /* [SWS_DoIP_00197] */
    /* Generic header negative acknowledge */
    DoIP_HdrNackType_st msgHdrNack = {DOIP_ZERO};
    PduInfoType msgStruct = {NULL_PTR, DOIP_ZERO};
    PduIdType tmpSoAdRxPduId = DOIP_CONNECTION_TCP_SERVER_TOTAL;
    /* Diagnostic power mode information acknowledge */
    DoIP_PowerModeAckType_st msgPowerMode = {DOIP_ZERO};
    /* DoIP entity status response */
    DoIP_EntityStateAckType_st msgEntityState = {DOIP_ZERO};


#if( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON )
    uint32 maxDataSize = DOIP_MAX_REQUEST_BYTES;
#endif /* ( STD_ON == DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE ) */

    uint8 data[DOIP_GEN_HDR_LEN_BYTE + DOIP_ACK_VEHICLE_IDENT_LEN_BYTE] = {DOIP_ZERO};
    uint8 vinGidBuf[DOIP_VIN_LEN_BYTE] = {DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO,
                                          DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO,
                                          DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO,
                                          DOIP_ZERO, DOIP_ZERO};
    switch( hdrType )
    {
        case DOIP_HDR_TYPE_GEN_NACK:
        {
            /* Build Nack message */
            msgHdrNack.genHdr.ver    = DOIP_PROTOCOL_VERSION;
            msgHdrNack.genHdr.invVer = (uint8)(~msgHdrNack.genHdr.ver);

            msgHdrNack.genHdr.type[DOIP_ZERO] = (uint8)(hdrType >> DOIP_EIGHT);  /* [SWS_DoIP_00007] */
            msgHdrNack.genHdr.type[DOIP_ONE] = (uint8)(hdrType);

            msgHdrNack.genHdr.lenByte[DOIP_ZERO] = DOIP_ZERO;
            msgHdrNack.genHdr.lenByte[DOIP_ONE] = DOIP_ZERO;
            msgHdrNack.genHdr.lenByte[DOIP_TWO] = DOIP_ZERO;
            msgHdrNack.genHdr.lenByte[DOIP_THREE] = DOIP_ONE;

            msgHdrNack.nackCode = (uint8)param;

            /* Build message struct for request */
            msgStruct.SduDataPtr = &msgHdrNack.genHdr.ver;
            msgStruct.SduLength = DOIP_GEN_HDR_LEN_BYTE + DOIP_ONE; /* [SWS_DoIP_00013] */

            /* Send message [SWS_DoIP_00198] */
            retVal = SoAd_IfTransmit(connection, &msgStruct);
            break;
        }
        case DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT:
        {
            /* Fill VIN. [SWS_DoIP_00072] */
            vinRetVal = DoIP_GetVinFun(vinGidBuf);
            if( (Std_ReturnType)DOIP_E_OK == vinRetVal )
            {
                /* VIN successfully retrieved */
                DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)vinGidBuf, (uint32)DOIP_VIN_LEN_BYTE);
            }
            else
            {
                while( DOIP_ZERO < vinIdx )
                {
                    vinIdx--;
                    data[ackIdx + vinIdx] = DOIP_VIN_INV_PATTERN;
                }
            }
            ackIdx += DOIP_VIN_LEN_BYTE;

            /* Fill Addr. [SWS_DoIP_00073] */
            logAddr = DOIP_ADDR;
            data[ackIdx] = (uint8)(logAddr >> DOIP_EIGHT);
            ackIdx++;
            data[ackIdx] = (uint8)(logAddr);
            ackIdx++;

#if( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
            /* [SWS_DoIP_00074] */
            DoIP_Memcpy((uint8*)&data[ackIdx], DoIP_Eid, (uint32)DOIP_HWID_LEN_BYTE);
            // if( E_OK == SoAd_GetPhysAddr(DoIP_Con2SoConId[connection], &physAddrBuf[DOIP_ZERO]) )
            // {
            //     //DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)&physAddrBuf[DOIP_ZERO], (uint32)DOIP_HWID_LEN_BYTE);
            // }
            // else
            // {
            //     break;
            // }
#else
            /* SWS_DoIP_00075 */
            DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)DoIP_Eid, (uint32)DOIP_HWID_LEN_BYTE);  /* [SWS_DoIP_00075] */
#endif /* ( STD_ON == DOIP_USE_MAC_ADDR_FOR_IDENT ) */

            ackIdx += DOIP_EID_LEN_BYTE;

#if( DOIP_VIN_GID_MASTER == STD_ON )/* Fill GID. [SWS_DoIP_00078] [SWS_DoIP_00077] [SWS_DoIP_00079] [SWS_DoIP_00080 [SWS_DoIP_00081] ]*/

#if( DOIP_USE_EID_AS_GID == STD_ON )
#if( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
            DoIP_Memcpy((uint8*)&data[ackIdx], DoIP_Gid, (uint32)DOIP_HWID_LEN_BYTE);
            // if( DOIP_E_OK == SoAd_GetPhysAddr(DoIP_Con2SoConId[connection], &physAddrBuf[DOIP_ZERO]) )
            // {
            //     DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)physAddrBuf, (uint32)DOIP_HWID_LEN_BYTE);
            // }
            // else
            // {
            //     break;
            // }
#else /* DOIP_USE_MAC_ADDR_FOR_IDENT == STD_OFF */
            DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)DoIP_Eid, (uint32)DOIP_HWID_LEN_BYTE);
#endif /* ( STD_ON == DOIP_USE_MAC_ADDR_FOR_IDENT ) */

#else /* DOIP_USE_EID_AS_GID == STD_OFF */

#if( DOIP_GID_AVAILABLE == STD_ON )
            /* Use DoIP GID. */
            DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)DoIP_Gid, (uint32)DOIP_GID_LEN_BYTE);
#else
                /* SWS_DoIP_00079 */
#ifdef DOIP_CALL_GET_GID_DIRECT
                /* Use DOIP_CALL_GET_GID_DIRECT or invalidity value. */
                if( DOIP_E_OK == DOIP_CALL_GET_GID_DIRECT(vinGidBuf) )
                {
                    /* GID successfully retrieved */
                    DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)vinGidBuf, (uint32)DOIP_GID_LEN_BYTE);
                }
                else
#endif
                {
                    while( DOIP_ZERO < gidIdx )
                    {
                        gidIdx--;
                        data[ackIdx + gidIdx] = DOIP_GID_INV_PATTERN;
                    }
                }
#endif /* ( STD_ON == DOIP_GID_AVAILABLE ) */
#endif /* ( STD_ON == DOIP_USE_EID_AS_GID ) */

#else
            /* SWS_DoIP_00080 */
#if( DOIP_GID_AVAILABLE == STD_ON )
            /* use DoIP GID. */
            DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)DoIP_Gid, (uint32)DOIP_GID_LEN_BYTE);
#else
            /* SWS_DoIP_00081 */
#ifdef DOIP_CALL_GET_GID_DIRECT
            /* Use DOIP_CALL_GET_GID_DIRECT or invalidity value. */
            if( E_OK == DOIP_CALL_GET_GID_DIRECT(vinGidBuf) )
            {
                /* GID successfully retrieved. */
                DoIP_Memcpy((uint8*)&data[ackIdx], (const uint8*)vinGidBuf, (uint32)DOIP_GID_LEN_BYTE);
            }
            else
#endif
            {
                while( DOIP_ZERO < gidIdx )
                {
                    gidIdx--;
                    data[ackIdx + gidIdx] = DOIP_GID_INV_PATTERN;
                }
            }

#endif /* ( STD_ON == DOIP_GID_AVAILABLE ) */
#endif /* ( STD_ON == DOIP_VIN_GID_MASTER ) */

            ackIdx += DOIP_GID_LEN_BYTE;

            data[ackIdx] = DOIP_ZERO;
#ifdef DOIP_FURTHER_ACTION_BYTE_DIRECT
            /* Fill FurtherAction. [SWS_DoIP_00291] */
            if( (Std_ReturnType)DOIP_E_OK  == DOIP_FURTHER_ACTION_BYTE_DIRECT(&furActByte) )
            {
                data[ackIdx] = furActByte;
            }
            else
#endif
            {
#if( DOIP_TESTER_WITH_CEN_SEC_AVAILABLE == STD_ON )
                while( DOIP_ZERO < routActIdx )
                {
                    routActIdx--;
                    if( DoIP_RoutingActivations[routActIdx].routingActivationNum == DOIP_ROUTACTV_VALIDNUM )
                    {
                        tmpSoAdRxPduId = DOIP_CONNECTION_TCP_SERVER_TOTAL;
                        while( DOIP_ZERO < tmpSoAdRxPduId )
                        {
                            tmpSoAdRxPduId--;
                            if( (DOIP_ROUT_ACTIV_STATE_ACTIVATED == DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].activState) &&
                                (DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].routActIdx == routActIdx) )
                            {
                                break;
                            }
                        }
                        if( DOIP_ZERO == tmpSoAdRxPduId )
                        {
                            /* SWS_DoIP_00082 */
                            data[ackIdx] = DOIP_PATTEN;
                            break;
                        }
                    }
                }
#endif /* ( STD_ON == DOIP_TESTER_WITH_CEN_SEC_AVAILABLE ) */
            }

#if( DOIP_VIN_GID_SYNC == STD_ON )
            ackIdx++;
            /* Fill VinGidSync. [SWS_DoIP_00071] [SWS_DoIP_00072] [SWS_DoIP_00086] [SWS_DoIP_00087] */
            data[ackIdx] = DOIP_ZERO;

#if( DOIP_GID_SYNC_ENABLED == STD_ON )
            if( ((Std_ReturnType)E_OK != vinRetVal) && ((Std_ReturnType)TRUE != DoIP_GidInSync) )
            {
                /* VIN/GID sync not succcessful. [SWS_DoIP_00088] */
                data[ackIdx] = DOIP_PATTEN;
            }
            if( ((Std_ReturnType)E_OK != vinRetVal) && ((Std_ReturnType)TRUE == DoIP_GidInSync) )
            {
                /* VIN/GID sync succcessful. [SWS_DoIP_00089] */
                data[ackIdx] = DOIP_ZERO;
            }
#endif /* ( STD_ON == DOIP_GID_SYNC_ENABLED ) */

#endif /* ( STD_ON == DOIP_VIN_GID_SYNC ) */

            /* Fill generic header. */
            DoIP_FillGenHdr(DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_ACK_VEHICLE_IDENT_LEN_BYTE, data);

            /* Prepare msg struct for sending. */
            msgStruct.SduDataPtr = data;
            msgStruct.SduLength  = DOIP_GEN_HDR_LEN_BYTE + DOIP_ACK_VEHICLE_IDENT_LEN_BYTE;

            /* Send message */
            retVal = SoAd_IfTransmit(connection, &msgStruct);
            break;
        }
        case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK:
        {
            /* Build power mode information message. */
            msgPowerMode.genHdr.ver = DOIP_PROTOCOL_VERSION;
            msgPowerMode.genHdr.invVer = (uint8)(~msgPowerMode.genHdr.ver);
            msgPowerMode.genHdr.type[DOIP_ZERO] = (uint8)(DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK >> DOIP_EIGHT);    /* [SWS_DoIP_00007] */
            msgPowerMode.genHdr.type[DOIP_ONE] = (uint8)(DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK & DOIP_FF);
            msgPowerMode.genHdr.lenByte[DOIP_ZERO] = DOIP_ZERO;
            msgPowerMode.genHdr.lenByte[DOIP_ONE] = DOIP_ZERO;
            msgPowerMode.genHdr.lenByte[DOIP_TWO] = DOIP_ZERO;
            msgPowerMode.genHdr.lenByte[DOIP_THREE] = DOIP_ONE;

            msgPowerMode.diagPowerMode = (uint8)param;

            /* Build message struct for request. [SWS_DoIP_00010]*/
            msgStruct.SduDataPtr = &msgPowerMode.genHdr.ver;
            msgStruct.SduLength  = DOIP_GEN_HDR_LEN_BYTE + DOIP_ONE;

            /* Send message. */
            retVal = SoAd_IfTransmit(DoIP_Con2SoAdTxPduId[connection], &msgStruct);
            break;
        }
        case DOIP_HDR_TYPE_ENTITY_STATE_ACK:
        {
            /* build entity status response */
            msgEntityState.genHdr.ver = DOIP_PROTOCOL_VERSION;
            msgEntityState.genHdr.invVer = (uint8)(~msgEntityState.genHdr.ver);
            msgEntityState.genHdr.type[DOIP_ZERO] = (uint8)(DOIP_HDR_TYPE_ENTITY_STATE_ACK >> DOIP_EIGHT);
            msgEntityState.genHdr.type[DOIP_ONE] = (uint8)(DOIP_HDR_TYPE_ENTITY_STATE_ACK & DOIP_FF);
            msgEntityState.genHdr.lenByte[DOIP_ZERO] = DOIP_ZERO;
            msgEntityState.genHdr.lenByte[DOIP_ONE] = DOIP_ZERO;
            msgEntityState.genHdr.lenByte[DOIP_TWO] = DOIP_ZERO;
            msgEntityState.genHdr.lenByte[DOIP_THREE] = DOIP_ACK_ENTITY_STATE_LEN_BYTE;
            msgEntityState.nodeType = DOIP_NODE_TYPE;
            msgEntityState.maxTcpSockCnt = DOIP_MAX_TESTER_CONNECTIONS;   /* [SWS_DoIP_00098] */
            msgEntityState.tcpSockCnt = DOIP_ZERO;
            /* Count open TCP_DATA socket (of all addr). [SWS_DoIP_00099]*/
            while( DOIP_ZERO < tmpSoAdRxPduId )
            {
                tmpSoAdRxPduId--;

                if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[tmpSoAdRxPduId] )
                {
                     msgEntityState.tcpSockCnt++;
                }
            }
            /* [SWS_DoIP_00100] */
#if( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON )
            msgEntityState.maxDataSize[DOIP_ZERO] = (uint8)(maxDataSize >> DOIP_TWENTYFOUR);
            msgEntityState.maxDataSize[DOIP_ONE] = (uint8)(maxDataSize >> DOIP_SIXTEEN);
            msgEntityState.maxDataSize[DOIP_TWO] = (uint8)(maxDataSize >> DOIP_EIGHT);
            msgEntityState.maxDataSize[DOIP_THREE] = (uint8)(maxDataSize);
#endif /* ( STD_ON == DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE ) */

            /* Build message struct for request. */
            msgStruct.SduDataPtr = &msgEntityState.genHdr.ver;
            msgStruct.SduLength  = DOIP_GEN_HDR_LEN_BYTE + DOIP_ACK_ENTITY_STATE_LEN_BYTE;

            /* Send message. */
            retVal = SoAd_IfTransmit(connection, &msgStruct);
            break;
        }
        default:
        {
            /* Function does not support this header type. */
            DoIP_Det_ErrorReport(DOIP_API_ID_UDP_SINGLE_TRANSMIT, DOIP_E_INVALID_PARAMETER);
            break;
        }
    }

    return retVal;
}
Std_ReturnType SoAd_GetPhysAddr(uint16 sock,uint8 *mac) 
{   
    uint8 macAddr[18];
    //int nRtn =  get_mac(&sock,macAddr,sizeof(macAddr));
    //if(nRtn > 0)
    {
        memcpy(mac,DoIP_Eid,6);
        return E_OK;
    }
    // else
    // {
    //     return E_NOT_OK;
    // }
}
Std_ReturnType SoAd_IfTransmit(uint16 sock,const PduInfoType* msgStruct)
{
    Std_ReturnType retVal = DOIP_E_NOT_OK;

    uint8* msg = NULL;
    msg = msgStruct->SduDataPtr;
    int len = sizeof(servaddrUDP);
    uint16_t port = ntohs(servaddrUDP.sin_port);
    if(((port >= 49152) && (port <= 65535)) || (port == 13400))
    {
        if(sendto(sock,msgStruct->SduDataPtr,msgStruct->SduLength,0,(struct sockaddr*)&servaddrUDP,len) > 0)
        {
            printf("Send UDP Msg sucessfully,send Time:%ld\n",clock());
            retVal  = DOIP_E_OK;
        }
        else
        {
            retVal = DOIP_E_NOT_OK;
            printf("send msg error pthread: %s(errno: %d)\n", strerror(errno), errno);
        }
    }

        
    return retVal;
}
/*
*******************************************************************************
* Function Name: DoIP_RemoveAliveCheckFromRoutActHandler
*
* Explanation: Remove alive check from rout active handler.
*
* param: connection: Current connection index.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RemoveAliveCheckFromRoutActHandler
(
    PduIdType connection
)
{
    uint8 tmpListIdx = DOIP_MAX_CONS_PER_LOC_ADDR;

    while( DOIP_ZERO < tmpListIdx )
    {
        tmpListIdx--;

        /* Entry found. */
        if(DoIP_RoutActivHandler[connection].aliveCheckList[tmpListIdx]!= DOIP_INV_PDU_ID)
        //if( connection == DoIP_RoutActivHandler[connection].aliveCheckList[tmpListIdx] )
        {
            /* Remove it. */
            DoIP_RoutActivHandler[DoIP_RoutActivHandler[connection].aliveCheckList[tmpListIdx]].aliveCheckList[tmpListIdx] = DOIP_INV_PDU_ID;
            DoIP_RoutActivHandler[connection].aliveCheckList[tmpListIdx] = DOIP_INV_PDU_ID;
            DoIP_RoutActivHandler[connection].aliveCheckCnt[DOIP_ZERO] = DOIP_ZERO;
            DoIP_RoutActivHandler[connection].aliveCheckElemNum = DOIP_ZERO;
            
            /* Decrement size. */
            //DoIP_RoutActivHandler[DoIP_RoutActivHandler[connection].aliveCheckList[tmpListIdx]].aliveCheckElemNum--;
            break;
        }
    }
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveReqRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
)
{
    printf("DoIP_RouteActiveReqRxHandler:\n");
    uint8 routActColIdx = DOIP_ZERO;
    uint8 routActIdx = DOIP_ZERO;
    uint8 activType = DOIP_ZERO;
    uint8 testerIdx = DOIP_TESTER_TOTAL;
    uint8 locAddrIdx = DoIP_Con2LocalAddrIdx[id];
    uint16 testerAddr = DOIP_ZERO;
    PduIdType connection = DOIP_FFFF;

    DoIP_RoutActiveReqType_st* reqPtr = NULL_PTR;

    /* Check message length. */
    if( DOIP_MAX_REQUEST_BYTES < hdrLen )
    {
        /* [SWS_DoIP_00017] */
        /* Max length exceeded, discard the message. */
        DoIP_TcpCon2SkipRxMsg[id] = TRUE;
        (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE);
        return;
    }
    if( (DOIP_ROUT_ACTIV_REQ_MIN_LEN_BYTE != hdrLen) &&
        ((DOIP_ROUT_ACTIV_REQ_MIN_LEN_BYTE + DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE) != hdrLen) )
    {
        /* Length check failed. The according socket shall be closed. */
        /* [SWS_DoIP_00117] and [SWS_DoIP_00019] */
        //DoIP_TcpCon2SkipRxMsg[id] = TRUE;
        (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE);
        *readDataLen = info->SduLength;
        DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
        //*bufferSizePtr = DOIP_ZERO;
        //DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
        return;
    }

    if( DoIP_TcpCon2RxMsgOffset[id] < (hdrLen + DOIP_GEN_HDR_LEN_BYTE) )
    {
        DoIP_HeaderAndDataCopy(id, (hdrLen + DOIP_GEN_HDR_LEN_BYTE), info, readDataLen);
    }
    /* Check whether message is now copied completely. */
    if( (hdrLen + DOIP_GEN_HDR_LEN_BYTE) == DoIP_TcpCon2RxMsgOffset[id] )
    {
        uint8* addrData = ((uint8*)&DoIP_TcpCon2RxHdrBuf[id]) + DOIP_GEN_HDR_LEN_BYTE;
        reqPtr = (DoIP_RoutActiveReqType_st*)(addrData);

        /* finish message */
        DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;

        /* Lock routing activation handler. */
        DoIP_RoutActivHandler[id].tcpCon = id;

        /* Reset inactivity timer. */
        DoIP_TcpCon2InactivCnt[id] = DOIP_ZERO;

        DOIP_GET_UINT16(reqPtr->testAddr, DOIP_ZERO, testerAddr);

        /* Check if any tester with received tester address is configured. [SWS_DoIP_00102] */
        if( (Std_ReturnType)E_OK != DoIP_GetTesterIdxByTesterAddr(testerAddr, &testerIdx) )    //UNKNOWED ADDR
        {
            /* Tester address is not configured. [SWS_DoIP_00104] */
            (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                   DOIP_ROUT_ACTIV_RES_CODE_UNKNOWN_TESTER, testerIdx, NULL_PTR, TRUE);
            return;
        }
        DoIP_RoutActivHandler[id].testerIdx = testerIdx;
        DoIP_RoutActivHandler[id].testerAddr = testerAddr;

        /* Check if any routing activation is configured for this activation number/type. */
        activType = reqPtr->activType[DOIP_ZERO];
        while( DoIP_Tester[testerIdx].routActNum > routActColIdx )
        {
            routActIdx = DoIP_Tester[testerIdx].routActColPtr[routActColIdx];
            if( DoIP_RoutingActivations[routActIdx].routingActivationNum == activType )
            {
                /* Routing activation with corresponding activation number/type found. [SWS_DoIP_00108]*/
                break;
            }
            routActColIdx++;
        }
        /* Activation type check failed. [SWS_DoIP_00160]*/
        if( DoIP_Tester[testerIdx].routActNum == routActColIdx )
        {
            (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                   DOIP_ROUT_ACTIV_RES_CODE_INV_ACTIV_TYPE, testerIdx, NULL_PTR, TRUE);
            return;
        }
        DoIP_RoutActivHandler[id].routActIdx = routActIdx;

        /* Get OEM specific part. */
        if( DOIP_ROUT_ACTIV_REQ_MAX_LEN_BYTE == hdrLen )
        {
            /* OEM specific part available. */
            /* Initalize OEM specific part for response. */
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_ZERO] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_ONE] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_TWO] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_THREE] = DOIP_ZERO;

            /* Store OEM specific part for request. */
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_ZERO] = reqPtr->oem[DOIP_ZERO];
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_ONE] = reqPtr->oem[DOIP_ONE];
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_TWO] = reqPtr->oem[DOIP_TWO];
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_THREE] = reqPtr->oem[DOIP_THREE];

            DoIP_RoutActivHandler[id].oemSpecUsed = TRUE;
        }
        else
        {
            DoIP_RoutActivHandler[id].oemSpecUsed = FALSE;
        }

        /* A tester is already assigned to this socket connection. [SWS_DoIP_00103]*/
        if( DOIP_INV_TESTER_IDX != DoIP_TcpCon2ActivMgt[id].testerIdx )
        {
            if( testerIdx != DoIP_TcpCon2ActivMgt[id].testerIdx )
            {
                /* Other TesterAddr is already active on this socket connection -> tx nack and close socket. [SWS_DoIP_00106]*/
                (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                       DOIP_ROUT_ACTIV_RES_CODE_DIFFERENT_TESTER, testerIdx, NULL_PTR, TRUE);
                return;
            }
            else
            {
                /* Tester address is already active on this socket. */
                /* Nothing to do here. */
            }
         }
        else /* Current socket connection has no registered tester */
        {
            DoIP_GetConnectionOfTesterAddr(testerAddr, &connection);
            if( DOIP_INV_PDU_ID != connection )
            {
                /* TesterAddr is already assigned to another socket -> issue single alive check on this socket. [SWS_DoIP_00105] */
                if( (Std_ReturnType)E_OK == DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ALIVE_CHECK_REQ,
                                                             DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE) )
                {
                    DoIP_RoutActivHandler[id].aliveCheckList[DOIP_ZERO] = connection;
                    DoIP_RoutActivHandler[connection].aliveCheckList[DOIP_ZERO] = id;
                    DoIP_RoutActivHandler[id].aliveCheckElemNum = DOIP_ONE;
                    /* load alive check timer */
                    DoIP_RoutActivHandler[id].aliveCheckCnt[DOIP_ZERO] = DOIP_ALIVE_CHECK_WAIT;
                }
                else
                {
                    DoIP_Det_ErrorReport(DOIP_API_ID_TP_COPY_RX_DATA, DOIP_E_NOBUFS);
                }
                return;
            }
            else if( DOIP_ZERO == DoIP_GetAvailableSockNum(id,locAddrIdx) )
            {
                /* All sockets but max one are in use -> issue alive check on all active sockets. */
                //connection = DOIP_CONNECTION_TOTAL;
                connection = DOIP_ZERO;
                while( connection < DOIP_CONNECTION_TOTAL )
                {
                    /* Filter local address. */
                    if ( DoIP_Con2LocalAddrIdx[connection] == DoIP_Con2LocalAddrIdx[id] )
                    {
                        if ( DOIP_INV_TESTER_IDX != DoIP_TcpCon2ActivMgt[connection].testerIdx )
                        {
                            /* Valid socket found -> issue alive check. */
                            if ( (Std_ReturnType)E_OK == DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ALIVE_CHECK_REQ,
                                                                          DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE) )
                            {
                                DoIP_RoutActivHandler[connection].aliveCheckCnt[DOIP_ZERO] = DOIP_ALIVE_CHECK_WAIT;
                                DoIP_RoutActivHandler[id].aliveCheckCnt[DOIP_ZERO] = (DOIP_ALIVE_CHECK_WAIT + 10);
                                DoIP_RoutActivHandler[connection].aliveCheckElemNum++;
                                //DoIP_RoutActivHandler[id].aliveCheckElemNum++;
                                DoIP_RoutActivHandler[connection].aliveCheckList[DOIP_ZERO] = id;
                                DoIP_RoutActivHandler[id].aliveCheckList[DOIP_ZERO] = DOIP_INV_PDU_ID;

                              /**  DoIP_RoutActivHandler[id].aliveCheckList[DOIP_ZERO] = id;
                                DoIP_RoutActivHandler[connection].aliveCheckList[DOIP_ZERO] = id;
                                DoIP_RoutActivHandler[id].aliveCheckElemNum = DOIP_ONE;
                                /* Load alive check timer. 
                                DoIP_RoutActivHandler[id].aliveCheckCnt[connection] = DOIP_ALIVE_CHECK_WAIT;
                                //DoIP_RoutActivHandler[id].aliveCheckList[DoIP_RoutActivHandler[id].aliveCheckElemNum] = connection;
                                //DoIP_RoutActivHandler[id].aliveCheckElemNum++;*/
                            }
                            else
                            {
                                DoIP_Det_ErrorReport(DOIP_API_ID_TP_COPY_RX_DATA, DOIP_E_NOBUFS);
                            }
                        }
                    }
                    connection++;
                }
                
                return;
            }
            else
            {
                /* Tester is not active on a different socket and a TCP_DATA socket is available. */
            }
        }

        /* Tester already or not yet activated. */
        DoIP_PerformAuthConfAndActivateRouting(id);
    }
    else
    {
        /* Set bufferSize to length of pending message part. */
        *bufferSizePtr = (PduLengthType)((hdrLen + DOIP_GEN_HDR_LEN_BYTE) - DoIP_TcpCon2RxMsgOffset[id]);
        DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
    }
    
}

#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RouteActiveAckRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
)
{
    uint16 testerAddr = DOIP_ZERO;
    DoIP_RoutActiveAckType_st *ackPtr = NULL_PTR;

    /* Check message length. */
    if( DoIP_TcpCon2ActivMgt[id].activState != DOIP_ROUT_ACTIV_STATE_ACTIVATING )
    {
        DoIP_TcpCon2SkipRxMsg[id] = TRUE;
    }
    else if( (DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE != hdrLen) && (DOIP_ROUT_ACTIV_ACK_MAX_LEN_BYTE != hdrLen) )
    {
        DoIP_TcpCon2SkipRxMsg[id] = TRUE;
    }
    else
    {
        if( DoIP_TcpCon2RxMsgOffset[id] < (hdrLen + DOIP_GEN_HDR_LEN_BYTE) )
        {
            DoIP_HeaderAndDataCopy(id, (hdrLen + DOIP_GEN_HDR_LEN_BYTE), info, readDataLen);
        }
        /* Check whether message is now copied completely. */
        if( (hdrLen + DOIP_GEN_HDR_LEN_BYTE) == DoIP_TcpCon2RxMsgOffset[id] )
        {
            /* Finish message. */
            DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
            /* Reset inactivity timer. */
            DoIP_TcpCon2InactivCnt[id] = DOIP_ZERO;
            ackPtr = (DoIP_RoutActiveAckType_st*)(((uint8*)&DoIP_TcpCon2RxHdrBuf[id]) + DOIP_GEN_HDR_LEN_BYTE);
            DOIP_GET_UINT16(ackPtr->testAddr, DOIP_ZERO, testerAddr);
            if( testerAddr == DoIP_TcpCon2ActivMgt[id].testerAddr)
            {
                if( DOIP_ROUT_ACTIV_RES_CODE_SUCCESS == ackPtr->ackCode )
                {
                    DoIP_TcpCon2ActivMgt[id].activState = DOIP_ROUT_ACTIV_STATE_ACTIVATED;
                }
                else
                {
                    DoIP_TcpCon2ActivMgt[id].activState = DOIP_ROUT_ACTIV_STATE_NONE;
                }
            }
        }
        else
        {
            /* Set bufferSize to length of pending message part. */
            *bufferSizePtr = (PduLengthType)((hdrLen + DOIP_GEN_HDR_LEN_BYTE) - DoIP_TcpCon2RxMsgOffset[id]);
            DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
        }
    }
}
#endif

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_AliveCheckAckRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
)
{
    uint16 testerAddr = DOIP_ZERO;
    /* Check message length */
    if( DOIP_MAX_REQUEST_BYTES < hdrLen )
    {
        /* Max length exceeded */
        DoIP_TcpCon2SkipRxMsg[id] = TRUE;
        (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE);
        return;
    }
    if( DOIP_ADDR_LEN_BYTE != hdrLen )
    {
        /* Length check failed */
        (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE);
        readDataLen = info->SduLength;
        DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
        *bufferSizePtr = DOIP_ZERO;
        DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
        return;
    }

    if( DoIP_TcpCon2RxMsgOffset[id] < (hdrLen + DOIP_GEN_HDR_LEN_BYTE) )
    {
        DoIP_HeaderAndDataCopy(id, (hdrLen + DOIP_GEN_HDR_LEN_BYTE), info, readDataLen);
    }

    /* Check whether message is now copied completely. */
    if( (hdrLen + DOIP_GEN_HDR_LEN_BYTE) == DoIP_TcpCon2RxMsgOffset[id] )
    {
        if( DOIP_INV_TESTER_IDX != DoIP_TcpCon2ActivMgt[id].testerIdx )
        {
            DOIP_GET_UINT16((uint8*)(&DoIP_TcpCon2RxHdrBuf[id]), DOIP_GEN_HDR_LEN_BYTE, testerAddr);
            if( testerAddr == DoIP_Tester[DoIP_TcpCon2ActivMgt[id].testerIdx].testerAddr)
            {
                /* Alive check response with expected tester address. [SWS_DoIP_00141] */
                DoIP_RemoveAliveCheckFromRoutActHandler(id);
            }
            else
            {
                /* Alive check response with unexpected tester address. */
                /* Close socket. */
                //DoIP_Con2SoConClosing[id] = TRUE;
                DoIP_CloseSoCon(id);
                ActiveConfig_Init(id);
            }
        }
        /* Finish message. */
        DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
    }
    else
    {
        /* Set bufferSize to length of pending message part. */
        *bufferSizePtr = (PduLengthType)((hdrLen + DOIP_GEN_HDR_LEN_BYTE) - DoIP_TcpCon2RxMsgOffset[id]);
        DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
    }
}

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HeaderAndDataCopy
(
    PduIdType id,
    PduLengthType expectLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,           //send message length and data
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
)
{
    PduLengthType bytesToCopy = (PduLengthType)(expectLen - DoIP_TcpCon2RxMsgOffset[id]);
    if( bytesToCopy > ((PduLengthType)(info->SduLength - (*readDataLen))) )
    {
        bytesToCopy = (PduLengthType)(info->SduLength - (*readDataLen));
    }
    if( bytesToCopy > DOIP_ZERO )
    {
        /* message not copied completely */
        /* copy data to header buffer */
        DoIP_Memcpy(((uint8*)(&DoIP_TcpCon2RxHdrBuf[id]) + DoIP_TcpCon2RxMsgOffset[id]),
                    (const uint8*)(&info->SduDataPtr[*readDataLen]),
                    (uint32)bytesToCopy);
        (*readDataLen) += bytesToCopy;
        DoIP_TcpCon2RxMsgOffset[id] += bytesToCopy;
    }
}

#if( DOIP_NACK_APPEND_REQ == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_DiagNAckAppendReqCopy
(
    PduIdType id,
    PduLengthType dataLen,
    PduLengthType readDataLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info
)
{
    uint8 testerIdx = DoIP_TcpCon2ActivMgt[id].testerIdx;
    PduLengthType bytesToCopy = DOIP_ZERO;

    if( (testerIdx != DOIP_INV_TESTER_IDX) &&
        (DoIP_Tester[testerIdx].diagAckNackNumByte > DOIP_ZERO) &&
        (DoIP_Tester[testerIdx].diagAckNackNumByte > DoIP_Tester2DiagNAckOffset[testerIdx]) )
    {
        /* diagnostic message acknowledge shall contain user data */
        bytesToCopy = (PduLengthType)(DoIP_Tester[testerIdx].diagAckNackNumByte - DoIP_Tester2DiagNAckOffset[testerIdx]);
        if( bytesToCopy > dataLen )
        {
            bytesToCopy = dataLen;
        }
        if ( bytesToCopy > DOIP_ZERO )
        {
            /* Copy data to DiagNAck buffer */
            DoIP_Memcpy(((uint8*)(&DoIP_Tester[testerIdx].diagAckNackBufPtr[DOIP_ZERO]) + DoIP_Tester2DiagNAckOffset[testerIdx]),
                        (const uint8*)(&info->SduDataPtr[readDataLen]),
                        (uint32)bytesToCopy);
            DoIP_Tester2DiagNAckOffset[testerIdx] += bytesToCopy;
        }
    }
}
#endif

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpPreTransmit
(
    PduIdType connection,
    uint16 hdrType,
    uint16 param1,
    uint16 param2,
    uint8 param3,
    boolean closeSocket
)
{
    if( DOIP_HDR_TYPE_INVALID == DoIP_TcpCon2TpPreTransMgt[connection].hdrType )
    {
        /* no pending prepare transmit request */
        /* store transmission parameter */
        DoIP_TcpCon2TpPreTransMgt[connection].hdrType     = hdrType;
        DoIP_TcpCon2TpPreTransMgt[connection].param1      = param1;
        DoIP_TcpCon2TpPreTransMgt[connection].param2      = param2;
        DoIP_TcpCon2TpPreTransMgt[connection].param3      = param3;
        DoIP_TcpCon2TpPreTransMgt[connection].closeSocket = closeSocket;
        // (void)DoIP_TcpTransmit(connection,hdrType,param1,param2,param3,NULL_PTR,FALSE);
    }
    // else
    // {
    //     (void)DoIP_TcpTransmit(connection,hdrType,param1,param2,param3,NULL_PTR,FALSE);
    // }
}

#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ClientDiagReqRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
)
{
    boolean continueFlag = FALSE;
    uint16 srcAddr = DOIP_ZERO;
    uint16 tgtAddr = DOIP_ZERO;
    PduIdType channel = DOIP_INV_PDU_ID;
    PduLengthType diagReqHdrLen = DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE;
    PduLengthType bytesLeft = DOIP_ZERO;
    uint32 diagMsgLength  = DOIP_ZERO;
    PduInfoType localPduInfoPtr = {NULL_PTR, DOIP_ZERO};
    DoIP_DiagReqType_st* diagReqPtr = NULL_PTR;

    /* Check message length. */
    if( DOIP_MAX_REQUEST_BYTES < hdrLen )
    {
        /* Max length exceeded. */
        DoIP_TcpCon2SkipRxMsg[id] = TRUE;
        /* (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE); */
    }
    else if( DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE >= hdrLen )
    {
        /* Length check failed. */
        /* SWS_DoIP_00122 */
        /* (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE); */
#if( DOIP_LOCAL_DEBUG == STD_ON )
        DoIP_DebugRxCnt[id].rxLenError++;
#endif
        DoIP_Con2SoConClosing[id] = TRUE;
        DoIP_CloseSoCon(id);
    }
    else if( DoIP_TcpCon2RxMsgOffset[id] < diagReqHdrLen )
    {
        /* diagnostic message header was not copied completely to header buffer */
        DoIP_HeaderAndDataCopy(id, diagReqHdrLen, info, readDataLen);

        if( DoIP_TcpCon2RxMsgOffset[id] < diagReqHdrLen )
        {
            *bufferSizePtr = diagReqHdrLen - DoIP_TcpCon2RxMsgOffset[id];
            DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
        }
        else /* DoIP_TcpCon2RxMsgOffset[id] == diagReqHdrLen */
        {
            /* Message header was copied completely. */
            diagMsgLength  = (uint32)(hdrLen - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE);
            diagReqPtr = (DoIP_DiagReqType_st*)(((uint8*)&DoIP_TcpCon2RxHdrBuf[id]) + DOIP_GEN_HDR_LEN_BYTE);

            DOIP_GET_UINT16(diagReqPtr->srcAddr, DOIP_ZERO, srcAddr);
            DOIP_GET_UINT16(diagReqPtr->tgtAddr, DOIP_ZERO, tgtAddr);

            DoIP_TcpCon2SkipRxMsg[id] = TRUE;

            /* Check whether routing is active. */
            if( DOIP_ROUT_ACTIV_STATE_ACTIVATED != DoIP_TcpCon2ActivMgt[id].activState )
            {

                /* Missing routing activation. */
                /* SWS_DoIP_00123 */
                /* DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR, TRUE); */
                DoIP_Con2SoConClosing[id] = TRUE;
                DoIP_CloseSoCon(id);
#if( DOIP_LOCAL_DEBUG == STD_ON )
                DoIP_DebugRxCnt[id].rxMissRouteAct++;
#endif

            }
            else
            {
                channel = DoIP_FindChannelBySAAndTA(srcAddr, tgtAddr);

                if( DOIP_INV_PDU_ID == channel )
                {
#if 0
                    /* SWS_DoIP_00124 */
                    /* The target address is not configured at all. */
                    uint32 param3 = DOIP_DIAG_MSG_RES_CODE_UNKNOWN_TGT_ADDR;
                    DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, param3, FALSE);
#endif
                }
                else if( diagMsgLength > (DOIP_MAX_REQUEST_BYTES - DOIP_FOUR) )
                {
#if 0
                    /* Max length of target Transport Protocol exceeded. */
                    /* SWS_DoIP_00125 */
                    DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, DOIP_DIAG_MSG_RES_CODE_MSG_TOO_LARGE, FALSE);
#endif
                }
                else
                {
                    /* Call start of reception at PduR. [SWS_DoIP_00212] [SWS_PduR_00507] */
                    if( BUFREQ_OK != PduR_DoIPTpStartOfReception(DoIP_Channel2PduRRxPduId[channel], NULL_PTR,
                                                                 (PduLengthType)(hdrLen - DOIP_DIAG_HDR_LEN_BYTE), bufferSizePtr))
                    {
#if 0
                        DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, DOIP_DIAG_MSG_RES_CODE_OUT_OF_MEMORY, FALSE);
#endif
                    }
                    else
                    {
                        /* Start of reception successful. */
                        DoIP_TcpCon2SkipRxMsg[id] = FALSE;
                        DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;

                        /* Set active channel for this socket connection. */
                        DoIP_TcpCon2RxChannelActive[id] = channel;
                        DoIP_TcpCon2LastRxTgtAddr[id] = tgtAddr;
                        /* Set flag to query PduR buffer in next step. */
                        localPduInfoPtr.SduLength  = DOIP_ZERO;
                        /* set pointer to dummy data */
                        localPduInfoPtr.SduDataPtr = NULL_PTR;
                        continueFlag = TRUE;
                    }
                }
            }
        }
    }
    else
    {
        localPduInfoPtr.SduLength  = (PduLengthType)(info->SduLength - (*readDataLen));
        localPduInfoPtr.SduDataPtr = &info->SduDataPtr[*readDataLen];
        continueFlag = TRUE;
    }

    if( TRUE == continueFlag )
    {
        /* Call CopyRxData of PduR. */
        if( BUFREQ_OK != PduR_DoIPTpCopyRxData(DoIP_Channel2PduRRxPduId[DoIP_TcpCon2RxChannelActive[id]], &localPduInfoPtr, bufferSizePtr) )
        {
 #if 0
            entityAddr = DoIP_TcpCon2LastRxTgtAddr[id];
            /* Get tester address. */
            testerAddr = DoIP_Tester[DoIP_TcpCon2ActivMgt[id].testerIdx].testerAddr;
            /* Send diagnostic message negative acknowledge. [SWS_DoIP_00174] */
            DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, entityAddr, testerAddr, DOIP_DIAG_MSG_RES_CODE_NETWORK_TRANSPROT, FALSE);
#endif
            /* Call PduR. */
            /* SWS_DoIP_00217 */
            PduR_DoIPTpRxIndication(DoIP_Channel2PduRRxPduId[DoIP_TcpCon2RxChannelActive[id]], E_NOT_OK);
            /* Reset active channel */
            DoIP_TcpCon2RxChannelActive[id] = DOIP_INV_PDU_ID;
            /* Skip message */
            DoIP_TcpCon2SkipRxMsg[id] = TRUE;
        }
        else
        {
            bytesLeft = (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - (DoIP_TcpCon2RxMsgOffset[id] + localPduInfoPtr.SduLength));
            if( bytesLeft < (*bufferSizePtr) )
            { /* upper layer has more buffer than expected */
              //*bufferSizePtr = bytesLeft;
            }
            DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;

            if ( DOIP_ZERO == bytesLeft )
            {
                /* Entire message is processed */
                /* Send diagnostic message positive acknowledge */
                /* (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_DIAG_ACK, DoIP_TcpCon2LastRxTgtAddr[id], DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE); */
                /* Call PduR. */
                /* SWS_DoIP_00221 */
                PduR_DoIPTpRxIndication(DoIP_Channel2PduRRxPduId[DoIP_TcpCon2RxChannelActive[id]], E_OK);
                lastMsgInfo = localPduInfoPtr;
                /* Finish message */
                DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;

                /* reset active channel */
                DoIP_TcpCon2RxChannelActive[id] = DOIP_INV_PDU_ID;
            }
            else
            {
                /* Another part of the message is received */
                /* increment offset */
                DoIP_TcpCon2RxMsgOffset[id] += localPduInfoPtr.SduLength;
            }
        }
        (*readDataLen) += localPduInfoPtr.SduLength;
    }
}
#endif

DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ServerDiagReqRxHandler
(
    PduIdType id,
    uint32 hdrLen,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) readDataLen
)
{
    printf("DoIP_ServerDiagReqRxHandler:\n");
    uint8 routActIdx = DOIP_ZERO;
    boolean continueFlag = FALSE;
    uint16 testerAddr = DOIP_ZERO;
    uint16 entityAddr = DOIP_FFFF;
    uint16 srcAddr = DOIP_ZERO;
    uint16 tgtAddr = DOIP_ZERO;
    PduIdType tmpChannel = DOIP_ZERO;
    PduIdType channel = DOIP_INV_PDU_ID;
    PduLengthType diagReqHdrLen = DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE;
    PduLengthType bytesLeft = DOIP_ZERO;
    uint32 diagMsgLength  = DOIP_ZERO;
    uint32 channelNum = DOIP_ZERO;
    PduInfoType localPduInfoPtr = {NULL_PTR, DOIP_ZERO};
    DoIP_DiagReqType_st* diagReqPtr = NULL_PTR;
    uint32 lenssss = info->SduLength;
    /* Check message length. */

    if( DOIP_MAX_REQUEST_BYTES < hdrLen )
    {
        /* Max length exceeded. */
        DoIP_TcpCon2SkipRxMsg[id] = TRUE;
        (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE);
    }
    else if(( DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE >= hdrLen) || (info->SduLength != (hdrLen + DOIP_GEN_HDR_LEN_BYTE)))
    {
        /* Length check failed. */
        /* SWS_DoIP_00122 */
        (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE);
    }
    else if( DoIP_TcpCon2RxMsgOffset[id] < diagReqHdrLen )
    {
        /* diagnostic message header was not copied completely to header buffer */
        DoIP_HeaderAndDataCopy(id, diagReqHdrLen, info, readDataLen);

        if( DoIP_TcpCon2RxMsgOffset[id] < diagReqHdrLen )
        {
            *bufferSizePtr = diagReqHdrLen - DoIP_TcpCon2RxMsgOffset[id];
            DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
        }
        else /* DoIP_TcpCon2RxMsgOffset[id] == diagReqHdrLen */
        {
            /* Message header was copied completely. */
            diagMsgLength  = (uint32)(hdrLen - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE);
            diagReqPtr = (DoIP_DiagReqType_st*)(((uint8*)&DoIP_TcpCon2RxHdrBuf[id]) + DOIP_GEN_HDR_LEN_BYTE);

            DOIP_GET_UINT16(diagReqPtr->srcAddr, DOIP_ZERO, srcAddr);
            DOIP_GET_UINT16(diagReqPtr->tgtAddr, DOIP_ZERO, tgtAddr);

            DoIP_TcpCon2SkipRxMsg[id] = TRUE;

            /* Check whether routing is active. */
            if( DOIP_ROUT_ACTIV_STATE_ACTIVATED != DoIP_TcpCon2ActivMgt[id].activState )
            {
                /* Missing routing activation. */
                /* SWS_DoIP_00123 */
                DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR, TRUE);
            }
            else if( srcAddr != DoIP_Tester[DoIP_TcpCon2ActivMgt[id].testerIdx].testerAddr )
            {
                /* Invalid tester address. */
                /* SWS_DoIP_00123 */
                DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR, TRUE);
            }
            else
            {
                routActIdx = DoIP_TcpCon2ActivMgt[id].routActIdx;
                channelNum = DoIP_RoutingActivations[routActIdx].channelNum;

                while( DOIP_ZERO < channelNum )
                {
                    channelNum--;
                    if( NULL_PTR != DoIP_RoutingActivations[routActIdx].targetAddrPtr)
                    {
                        if( tgtAddr == DoIP_RoutingActivations[routActIdx].targetAddrPtr[channelNum] )
                        {
                            channel = DoIP_FindChannelBySAAndTA(srcAddr, tgtAddr);
                            break;
                        }
                    }
                }
                if( DOIP_INV_PDU_ID == channel )
                {
                    /* SWS_DoIP_00124 */
                    /* The target address is not configured at all. */
                    uint32 param3 = DOIP_DIAG_MSG_RES_CODE_UNKNOWN_TGT_ADDR;
                    tmpChannel = DOIP_CHANNELS_TOTAL;
                    while( DOIP_ZERO < tmpChannel )
                    {
                        tmpChannel--;
                        if( DoIP_Channel2EcuAddr[tmpChannel] == tgtAddr )
                        {
                            /* Target address is configured for reception but not for active routing activation. */
                            /* SWS_DoIP_00127 */
                            param3 = DOIP_DIAG_MSG_RES_CODE_TGT_UNREACHABLE;
                            break;
                        }
                    }
                    DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, param3, FALSE);
                }
                else if( diagMsgLength > (DOIP_MAX_REQUEST_BYTES - DOIP_FOUR) )
                {
                    /* Max length of target Transport Protocol exceeded. */
                    /* SWS_DoIP_00125 */
                    DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, DOIP_DIAG_MSG_RES_CODE_MSG_TOO_LARGE, FALSE);
                }
                else
                {
                    /* Call start of reception at PduR. [SWS_DoIP_00212] [SWS_PduR_00507] */
                    BufReq_ReturnType  returnBufreEQ = BUFREQ_OK;
                    // if(!Flag_DcmStartofReception)
                    // {
                    //     returnBufreEQ = Dcm_StartOfReception(0, NULL_PTR, (PduLengthType)(hdrLen - DOIP_DIAG_HDR_LEN_BYTE), bufferSizePtr);
                    // }
                    if( BUFREQ_OK != Dcm_StartOfReception(0, NULL_PTR, (PduLengthType)(hdrLen - DOIP_DIAG_HDR_LEN_BYTE), bufferSizePtr))
                    {
                        DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr, DOIP_DIAG_MSG_RES_CODE_OUT_OF_MEMORY, FALSE);
                        printf("OUTOFMEM\n");
                    }
                    else
                    {
                        Flag_DcmStartofReception = TRUE;
                        /* Start of reception successful. */
                        DoIP_TcpCon2SkipRxMsg[id] = FALSE;
                        DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;

                        /* Set active channel for this socket connection. */
                        DoIP_TcpCon2RxChannelActive[id] = channel;
                        DoIP_TcpCon2LastRxTgtAddr[id] = tgtAddr;
                        /* Set flag to query PduR buffer in next step. */
                        localPduInfoPtr.SduLength  = DOIP_ZERO;
                        /* set pointer to dummy data */
                        localPduInfoPtr.SduDataPtr = NULL_PTR;
                        continueFlag = TRUE;
                    }
                }
            }
        }
    }
    else
    {
        localPduInfoPtr.SduLength  = (PduLengthType)(info->SduLength - (*readDataLen));
        localPduInfoPtr.SduDataPtr = &info->SduDataPtr[*readDataLen];
        continueFlag = TRUE;
    }

    if( TRUE == continueFlag )
    {
#if( DOIP_NACK_APPEND_REQ == STD_ON )
        if( localPduInfoPtr.SduLength > DOIP_ZERO )
        {
            DoIP_DiagNAckAppendReqCopy(id, localPduInfoPtr.SduLength, (*readDataLen), info);
        }
#endif
        /* Call CopyRxData of PduR. */
        if( BUFREQ_OK != Dcm_CopyRxData(0, &localPduInfoPtr, bufferSizePtr) )
        {
            printf("localPduInfoPtr.SduLength = %d\n",localPduInfoPtr.SduLength);
            entityAddr = DoIP_TcpCon2LastRxTgtAddr[id];
            /* Get tester address. */
            testerAddr = DoIP_Tester[DoIP_TcpCon2ActivMgt[id].testerIdx].testerAddr;
            /* Send diagnostic message negative acknowledge. [SWS_DoIP_00174] */
            DoIP_TcpPreTransmit(id, DOIP_HDR_TYPE_DIAG_NACK, entityAddr, testerAddr, DOIP_DIAG_MSG_RES_CODE_NETWORK_TRANSPROT, FALSE);
            /* Call PduR. */
            /* SWS_DoIP_00217 */
            Dcm_TpRxIndication(0, E_NOT_OK);
            /* Reset active channel */
            DoIP_TcpCon2RxChannelActive[id] = DOIP_INV_PDU_ID;
            /* Skip message */
            DoIP_TcpCon2SkipRxMsg[id] = TRUE;
        }
        else
        {
            bytesLeft = (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - (DoIP_TcpCon2RxMsgOffset[id] + localPduInfoPtr.SduLength));
            if( bytesLeft < (*bufferSizePtr) )
            { /* upper layer has more buffer than expected */
              *bufferSizePtr = bytesLeft;
            }
            DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;

            if ( DOIP_ZERO == bytesLeft )
            {
                /* Entire message is processed */
                /* Send diagnostic message positive acknowledge */
                (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_DIAG_ACK, DoIP_TcpCon2LastRxTgtAddr[id], DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE);
                /* Call PduR. */
                /* SWS_DoIP_00221 */
                connectionPDUID = id;
                Dcm_TpRxIndication(0, E_OK);
      
                /* Finish message */
                DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;

                /* reset active channel */
                DoIP_TcpCon2RxChannelActive[id] = DOIP_INV_PDU_ID;
            }
            else
            {
                /* Another part of the message is received */
                /* increment offset */
                DoIP_TcpCon2RxMsgOffset[id] += localPduInfoPtr.SduLength;
            }
        }
        (*readDataLen) += localPduInfoPtr.SduLength;
    }
}

#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_ClientCopyTpRxDataHandler
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) continueFlag
)
{
    BufReq_ReturnType retVal = BUFREQ_OK;
    uint16 hdrType = DOIP_ZERO;
    PduLengthType readDataLen = DOIP_ZERO;
    uint32 hdrLen = DOIP_ZERO;
    DoIP_HdrType_st* hdrPtr = NULL_PTR;

    do
    {
        if( DOIP_GEN_HDR_LEN_BYTE > DoIP_TcpCon2RxMsgOffset[id] )
        {
            /* Generic header was not received completely. */
            DoIP_HeaderAndDataCopy(id, DOIP_GEN_HDR_LEN_BYTE, info, &readDataLen);
        }
        /* Generic header was received completely */
        if( DOIP_GEN_HDR_LEN_BYTE <= DoIP_TcpCon2RxMsgOffset[id] )
        {
            hdrPtr = (DoIP_HdrType_st*)&DoIP_TcpCon2RxHdrBuf[id];  /* Get the header pointer. */

            if( (DOIP_PROTOCOL_VERSION != (uint8)hdrPtr->ver) || (DOIP_PROTOCOL_VERSION != (uint8)(~hdrPtr->invVer)) )
            {
                /* Invalid header pattern */
                /* (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_FORMAT, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE); */
#if( DOIP_LOCAL_DEBUG == STD_ON )
                DoIP_DebugRxCnt[id].rxInvalidVer++;
#endif
                DoIP_Con2SoConClosing[id] = TRUE;
                DoIP_CloseSoCon(id);
                *continueFlag = FALSE;
                break;
            }
            DOIP_GET_UINT16(hdrPtr->type, DOIP_ZERO, hdrType);  /* Get the header type. */
            DOIP_GET_UINT32(hdrPtr->lenByte, DOIP_ZERO, hdrLen);/* Get the header length. */

            /* Check whether message shall be skipped. */
            /* Message shall be skipped. */
            if( TRUE == DoIP_TcpCon2SkipRxMsg[id] )
            {
                if( (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - DoIP_TcpCon2RxMsgOffset[id]) > ((PduLengthType)(info->SduLength - readDataLen)) )
                {
                    /* Message to be skipped is not received completely */
                    DoIP_TcpCon2RxMsgOffset[id] += (info->SduLength - readDataLen);
                    *bufferSizePtr = (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - DoIP_TcpCon2RxMsgOffset[id]);
                    DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
                }
                else
                {
                    /* Message to be skipped is received completely */
                    /* Finish message */
                    DoIP_TcpFinishTransmit(id);
                    *bufferSizePtr = DOIP_ZERO;
                    DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
                    DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
                    DoIP_TcpCon2SkipRxMsg[id] = FALSE;
                }
                *continueFlag = FALSE;
                break;
             }

            /* Further handling depends on message type. */
            switch( hdrType )
            {
                case DOIP_HDR_TYPE_DIAG_REQ:
                {
                    DoIP_ClientDiagReqRxHandler(id, hdrLen, info, bufferSizePtr, &readDataLen);
                    break;
                }
                case DOIP_HDR_TYPE_ROUT_ACTIV_ACK:
                {
                    DoIP_RouteActiveAckRxHandler(id, hdrLen, info, bufferSizePtr, &readDataLen);
                    break;
                }
                case DOIP_HDR_TYPE_ALIVE_CHECK_ACK:
                case DOIP_HDR_TYPE_ROUT_ACTIV_REQ:
                case DOIP_HDR_TYPE_GEN_NACK:
                case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ:
                case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_EID:
                case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN:
                case DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT:
                case DOIP_HDR_TYPE_ALIVE_CHECK_REQ:
                case DOIP_HDR_TYPE_ENTITY_STATE_REQ:
                case DOIP_HDR_TYPE_ENTITY_STATE_ACK:
                case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_REQ:
                case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK:
                case DOIP_HDR_TYPE_DIAG_ACK:
                case DOIP_HDR_TYPE_DIAG_NACK:
                {
                    /* Not relevant payload type. */
                    DoIP_TcpCon2SkipRxMsg[id] = TRUE;
                    break;
                }
                default:
                {
                    /* Unknown payload type. */
                    DoIP_TcpCon2SkipRxMsg[id] = TRUE;
                    /* (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE); */
                    break;
                }
            }

            if( (boolean)TRUE == DoIP_TcpCon2SkipRxMsg[id] )
            {
                /* Message shall be skipped. */
                /* Set buffer size to receive entire message in next function call. */
                if( (DOIP_GEN_HDR_LEN_BYTE + hdrLen) > DoIP_TcpCon2RxMsgOffset[id] )
                {
                    *bufferSizePtr = (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - DoIP_TcpCon2RxMsgOffset[id]);
                    DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
                }
            }
        }
        else
        {
            *bufferSizePtr = DOIP_GEN_HDR_LEN_BYTE - DoIP_TcpCon2RxMsgOffset[id];
            DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
        }
    }while( info->SduLength > readDataLen );
    return retVal;
}
#endif

/*
********************************************************************************
* Function Name: DoIP_ServerCopyTpRxDataHandler
*
* Explanation: Copy the Tp data.
*
* param: id: Current connection index.
*        info: Information buffer.
*        bufferSizePtr: Available buffer size.
*
* retval: None
********************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_ServerCopyTpRxDataHandler
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr,
    P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) continueFlag
)
{
    BufReq_ReturnType retVal = BUFREQ_OK;
    uint16 hdrType = DOIP_ZERO;
    PduLengthType readDataLen = DOIP_ZERO;
    uint32 hdrLen = DOIP_ZERO;
    DoIP_HdrType_st* hdrPtr = NULL_PTR;

   
    DoIP_HdrType_st* currentHdrTypr ;
    currentHdrTypr = (DoIP_HdrType_st*)malloc(sizeof(DoIP_HdrType_st));

    currentHdrTypr->ver =  info->SduDataPtr[0];
    currentHdrTypr->invVer =info->SduDataPtr[1];
    memcpy(currentHdrTypr->type,&info->SduDataPtr[2],2);
    memcpy(currentHdrTypr->lenByte,&info->SduDataPtr[4],4);
    memcpy(currentHdrTypr->data,&info->SduDataPtr[8],info->SduLength - 8);
    DoIP_TcpCon2RxHdrBuf[id] = *currentHdrTypr;
    free(currentHdrTypr);
    do
    {
        if( DOIP_GEN_HDR_LEN_BYTE > DoIP_TcpCon2RxMsgOffset[id] )
        {
            /* Generic header was not received completely. */
            DoIP_HeaderAndDataCopy(id, DOIP_GEN_HDR_LEN_BYTE, info, &readDataLen);
        }
        /* Generic header was received completely */
        if( DOIP_GEN_HDR_LEN_BYTE <= DoIP_TcpCon2RxMsgOffset[id] )
        {
            
            hdrPtr = (DoIP_HdrType_st*)&DoIP_TcpCon2RxHdrBuf[id];  /* Get the header pointer. */
            
            if( (DOIP_PROTOCOL_VERSION != (uint8)hdrPtr->ver) || (DOIP_PROTOCOL_VERSION != (uint8)(~hdrPtr->invVer)) )
            {
                /* Invalid header pattern */
                (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_FORMAT, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE);
                /* return BUFREQ_OK; */
                *continueFlag = FALSE;
                break;
            }
            DOIP_GET_UINT16(hdrPtr->type, DOIP_ZERO, hdrType);  /* Get the header type. */
            DOIP_GET_UINT32(hdrPtr->lenByte, DOIP_ZERO, hdrLen);/* Get the header length. */

//             if( ( DOIP_HDR_TYPE_ROUT_ACTIV_REQ == hdrType ) && ( DOIP_INV_PDU_ID != DoIP_RoutActivHandler[id].tcpCon ) )
//             {
//                 /* Routing activation handler is busy. */
//                 /* Handle routing activation later. */
//                 *bufferSizePtr = DOIP_ZERO;
//                 DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
//                 /* Modified on 2022-2-12 */
//                 /* Discard received headers. */
//                 DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
// #if( DOIP_LOCAL_DEBUG == STD_ON )
//                 DoIP_DebugRxCnt[id].rxRouteActBusy++;
// #endif
//                 break;
//             }

            /* Check whether message shall be skipped. */
            /* Message shall be skipped. */
            if( (boolean)TRUE == DoIP_TcpCon2SkipRxMsg[id] )
            {
#if( DOIP_NACK_APPEND_REQ == STD_ON )
                if( (DOIP_HDR_TYPE_DIAG_REQ == hdrType) &&
                    (DOIP_HDR_TYPE_DIAG_NACK == DoIP_TcpCon2TpPreTransMgt[id].hdrType) )
                {
                    /* Diagnostic message negative acknowledge shall be sent. */
                    DoIP_DiagNAckAppendReqCopy(id, (info->SduLength - readDataLen), readDataLen, info);
                }
#endif
                if( (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - DoIP_TcpCon2RxMsgOffset[id]) > ((PduLengthType)(info->SduLength - readDataLen)) )
                {
                    /* Message to be skipped is not received completely */
                    DoIP_TcpCon2RxMsgOffset[id] += (info->SduLength - readDataLen);
                    *bufferSizePtr = (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - DoIP_TcpCon2RxMsgOffset[id]);
                    DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
                }
                else
                {
                    /* Message to be skipped is received completely */
                    /* Finish message */
                    DoIP_TcpFinishTransmit(id);
                    *bufferSizePtr = DOIP_ZERO;
                    DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
                    DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
                    DoIP_TcpCon2SkipRxMsg[id] = FALSE;
                }
                /* return BUFREQ_OK; */
                *continueFlag = FALSE;
                break;
             }

            /* Further handling depends on message type. */
            switch( hdrType )
            {
                case DOIP_HDR_TYPE_ROUT_ACTIV_REQ:
                {
                    DoIP_RouteActiveReqRxHandler(id, hdrLen, info, bufferSizePtr, &readDataLen);
                    //DoIP_RoutActivHandler.tcpCon = DOIP_INV_PDU_ID;
                    break;
                }
                case DOIP_HDR_TYPE_ALIVE_CHECK_ACK:
                {
                    DoIP_AliveCheckAckRxHandler(id, hdrLen, info, bufferSizePtr, &readDataLen);
                    break;
                }
                case DOIP_HDR_TYPE_DIAG_REQ:
                {
                    DoIP_ServerDiagReqRxHandler(id, hdrLen , info, bufferSizePtr, &readDataLen);
                    break;
                }
                case DOIP_HDR_TYPE_ROUT_ACTIV_ACK:
                case DOIP_HDR_TYPE_GEN_NACK:
                case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ:
                case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_EID:
                case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN:
                case DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT:
                case DOIP_HDR_TYPE_ALIVE_CHECK_REQ:
                case DOIP_HDR_TYPE_ENTITY_STATE_REQ:
                case DOIP_HDR_TYPE_ENTITY_STATE_ACK:
                case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_REQ:
                case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK:
                case DOIP_HDR_TYPE_DIAG_ACK:
                case DOIP_HDR_TYPE_DIAG_NACK:
                {
                    /* Not relevant payload type. */
                    DoIP_TcpCon2SkipRxMsg[id] = TRUE;
                    break;
                }
                default:
                {
                    /* Unknown payload type. */
                    DoIP_TcpCon2SkipRxMsg[id] = TRUE;
                    (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE);
                    break;
                }
            }

            if( (boolean)TRUE == DoIP_TcpCon2SkipRxMsg[id] )
            {
                /* Message shall be skipped. */
                /* Set buffer size to receive entire message in next function call. */
                if( (DOIP_GEN_HDR_LEN_BYTE + hdrLen) >= DoIP_TcpCon2RxMsgOffset[id] )
                {
                    *bufferSizePtr = (PduLengthType)((DOIP_GEN_HDR_LEN_BYTE + hdrLen) - DoIP_TcpCon2RxMsgOffset[id]);
                    DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
                    if( (DOIP_GEN_HDR_LEN_BYTE + hdrLen) == DoIP_TcpCon2RxMsgOffset[id] )
                    {
                        DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
                        DoIP_TcpCon2SkipRxMsg[id] = FALSE;
                    }
                }
            }
        }
        else
        {
            *bufferSizePtr = DOIP_GEN_HDR_LEN_BYTE - DoIP_TcpCon2RxMsgOffset[id];
            DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
        }
    }while( info->SduLength > readDataLen );
    return retVal;
}

#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpClientCopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr
)
{
    boolean continueFlag = TRUE;
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

    if( (DOIP_ACTIVATION_LINE_LOCAL_ACTIVE != DoIP_ActivationLineLocalState) ||
        ((uint8)SOAD_SOCON_ONLINE != DoIP_Con2SoConState[id]) ||
        (FALSE == DoIP_TcpCon2RxTpSessionActive[id]) ||
        (TRUE == DoIP_TcpCon2RxTpCancelRequested[id]) )
    {
        /* Socket connection is not online.*/
        /* TP session is not active. */
        /* TP cancellation is ongoing */
        /* Nothing to do here. */
        /* return BUFREQ_E_NOT_OK; */
#if( DOIP_LOCAL_DEBUG == STD_ON )
        DoIP_DebugRxCnt[id].rxStateError++;
#endif
    }
    else
    {
        /* Check whether socket connection is requested to be closed. */
        /* Socket connection closing is requested - do not handle more than pending rx data of message. */
        if( TRUE == DoIP_Con2SoConClosing[id] )
        {
            *bufferSizePtr = DOIP_ZERO;
            DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
            /* return BUFREQ_OK; */
            retVal = BUFREQ_OK;
        }
        else
        {
            /* Modified on 2022-2-12*/
            if( (DOIP_ZERO == info->SduLength) && (DoIP_TcpCon2LastRxBufSize[id] > DOIP_ZERO) )
            {
                /* SoAd queries the rx buffer every time it receives a TCP segment. */
                *bufferSizePtr = DoIP_TcpCon2LastRxBufSize[id];
                return BUFREQ_OK;
            }
            /* SoAd queries Rx buffer size. [SWS_DoIP_00208] */
            if( (DOIP_ZERO == info->SduLength) && (DOIP_GEN_HDR_LEN_BYTE > DoIP_TcpCon2RxMsgOffset[id]) )
            {
                /* Generic header not received completely, only provide buffer for generic header. */
                *bufferSizePtr = DOIP_GEN_HDR_LEN_BYTE - DoIP_TcpCon2RxMsgOffset[id];
                DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
                retVal = BUFREQ_OK;
            }
            else if( info->SduLength > DoIP_TcpCon2LastRxBufSize[id] ) /* SoAd has Rx data. */
            {
                /* Check length. [SWS_DoIP_00210] */
                /* unexpected length. */
                /* (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_OUT_OF_MEM, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE); */
                /* return BUFREQ_E_NOT_OK; */
                retVal = BUFREQ_E_NOT_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
                DoIP_DebugRxCnt[id].rxLenError++;
#endif
            }
            else
            {
                if( DOIP_ROUT_ACTIV_STATE_ACTIVATED == DoIP_TcpCon2ActivMgt[id].activState )
                {
                    /* Routing activation active. */
                    /* Reset inactivity timer. */
                    DoIP_TcpCon2InactivCnt[id] = DOIP_ZERO;
                }
                retVal = DoIP_ClientCopyTpRxDataHandler(id, info, bufferSizePtr, &continueFlag);
                if( TRUE == continueFlag )
                {
                    if( (DOIP_ZERO == DoIP_TcpCon2RxMsgOffset[id]) ||
                        (DOIP_TCP_TX_QUEUE_GET_LEVEL(id) >= (DOIP_TCP_TX_MGT_QUEUE_SIZE - DOIP_ONE)) )
                    {
                        /* Message processed completely. */
                        /* High tx queue fill level - slow down rx path. */
                        /* Activation state is pending, and stop reception until state changes. */
                        *bufferSizePtr = DOIP_ZERO;
                        DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
                    }
                    else
                    {
                        /* Nothing to do here. */
                    }
                    retVal = BUFREQ_OK;
                }
            }
        }
    }

    return retVal;
}

#endif

DOIP_LOCAL_INLINE FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpServerCopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr
)
{
    boolean continueFlag = TRUE;
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

    if( (DOIP_ACTIVATION_LINE_LOCAL_ACTIVE != DoIP_ActivationLineLocalState) ||
        ((uint8)SOAD_SOCON_ONLINE != DoIP_Con2SoConState[id]) ||
        (FALSE == DoIP_TcpCon2RxTpSessionActive[id]) ||
        (TRUE == DoIP_TcpCon2RxTpCancelRequested[id]) )
    {
        /* Socket connection is not online.*/
        /* TP session is not active. */
        /* TP cancellation is ongoing */
        /* Nothing to do here. */
        /* return BUFREQ_E_NOT_OK; */
#if( DOIP_LOCAL_DEBUG == STD_ON )
        DoIP_DebugRxCnt[id].rxStateError++;
#endif
    }
    else
    {
        /* Check whether socket connection is requested to be closed. */
        /* Socket connection closing is requested - do not handle more than pending rx data of message. */
        if( TRUE == DoIP_Con2SoConClosing[id] )
        {
            *bufferSizePtr = DOIP_ZERO;
            DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
            /* return BUFREQ_OK; */
            retVal = BUFREQ_OK;
        }
#if( DOIP_NACK_APPEND_REQ == STD_ON )
        else if( (DoIP_TcpCon2ActivMgt[id].testerIdx != DOIP_INV_TESTER_IDX) &&
                 (DOIP_ZERO == DoIP_TcpCon2RxMsgOffset[id]) &&
                 (DoIP_Tester2DiagNAckOffset[DoIP_TcpCon2ActivMgt[id].testerIdx] > DOIP_ZERO) )
        {
            /* Diagnostic message acknowledge is pending - do not accept new data until acknowledge is sent. */
            *bufferSizePtr = DOIP_ZERO;
            DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
            /* return BUFREQ_OK; */
            retVal = BUFREQ_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
            DoIP_DebugRxCnt[id].rxAckPending++;
#endif
        }
#endif
        else
        {
            /* Modified on 2022-2-12*/
            if( (DOIP_ZERO == info->SduLength) && (DoIP_TcpCon2LastRxBufSize[id] > DOIP_ZERO) )
            {
                /* SoAd queries the rx buffer every time it receives a TCP segment. */
                *bufferSizePtr = DoIP_TcpCon2LastRxBufSize[id];
                return BUFREQ_OK;
            }
            /* SoAd queries Rx buffer size. [SWS_DoIP_00208] */
            if( (DOIP_ZERO == info->SduLength) && (DOIP_GEN_HDR_LEN_BYTE > DoIP_TcpCon2RxMsgOffset[id]) )
            {
                /* Generic header not received completely, only provide buffer for generic header. */
                *bufferSizePtr = DOIP_GEN_HDR_LEN_BYTE - DoIP_TcpCon2RxMsgOffset[id];
                DoIP_TcpCon2LastRxBufSize[id] = *bufferSizePtr;
                /* return BUFREQ_OK; */
                retVal = BUFREQ_OK;
            }
            else if( info->SduLength > DoIP_TcpCon2LastRxBufSize[id] ) /* SoAd has Rx data. */
            {
                /* Check length. [SWS_DoIP_00210] */
                /* unexpected length. */
                (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK,DOIP_GEN_NACK_OUT_OF_MEM , DOIP_ZERO, DOIP_ZERO, NULL_PTR, FALSE); 
                /* return BUFREQ_E_NOT_OK; */
                retVal = BUFREQ_E_NOT_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
                DoIP_DebugRxCnt[id].rxLenError++;
#endif
            }
            else
            {
                if( DOIP_ROUT_ACTIV_STATE_ACTIVATED == DoIP_TcpCon2ActivMgt[id].activState )
                {
                    /* Routing activation active. */
                    /* Reset inactivity timer. */
                    DoIP_TcpCon2InactivCnt[id] = DOIP_ZERO;
                }
                DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
                retVal = DoIP_ServerCopyTpRxDataHandler(id, info, bufferSizePtr, &continueFlag);
                if( TRUE == continueFlag )
                {
                    if( (DOIP_ZERO == DoIP_TcpCon2RxMsgOffset[id]) ||
                        (DOIP_TCP_TX_QUEUE_GET_LEVEL(id) >= (DOIP_TCP_TX_MGT_QUEUE_SIZE - DOIP_ONE)) ||
                        ((DOIP_ROUT_ACTIV_STATE_AUTH_PENDING == DoIP_TcpCon2ActivMgt[id].activState) ||
                         (DOIP_ROUT_ACTIV_STATE_CONF_PENDING == DoIP_TcpCon2ActivMgt[id].activState)) )
                    {
                        /* Message processed completely. */
                        /* High tx queue fill level - slow down rx path. */
                        /* Activation state is pending, and stop reception until state changes. */
                        *bufferSizePtr = DOIP_ZERO;
                        DoIP_TcpCon2LastRxBufSize[id] = DOIP_ZERO;
                        DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
                    }
                    else
                    {
                        DoIP_TcpCon2RxMsgOffset[id] = DOIP_ZERO;
                        /* Nothing to do here. */
                    }
                    retVal = BUFREQ_OK;
                }
                else
                {
                    retVal = BUFREQ_E_NOT_OK;
                }
            }
        }
    }

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_TcpTxQueueRemoveElement
*
* Explanation: Remove element from Tcp Tx queue.
*
* param: connection: Current connection index.
*        result: Result.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpTxQueueRemoveElement
(
    PduIdType connection,
    Std_ReturnType result
)
{
    uint8 queIdx;
    PduIdType channel;
    DOIP_ENTER_CRITICAL0();
    if( (connection < DOIP_CONNECTION_TOTAL) && (DoIP_TcpCon2TxMgtQueLvl[connection] > DOIP_ZERO) )
    {
        queIdx = DoIP_TcpCon2TxMgtQueIdx[connection];
        channel = DoIP_TcpCon2TcpTxMgt[connection][queIdx].channel;

        /* Reset TxMgt structs. */
        DoIP_TcpCon2TcpTxMgt[connection][queIdx].txHdrBufLen = DOIP_ZERO;

        /* Update Tx Queue. */
        DoIP_TcpCon2TxMgtQueLvl[connection]--;
        DoIP_TcpCon2TxMgtQueIdx[connection]++;
        if( DOIP_TCP_TX_MGT_QUEUE_SIZE == DoIP_TcpCon2TxMgtQueIdx[connection] )
        {
            /* Wrap around. */
            DoIP_TcpCon2TxMgtQueIdx[connection] = DOIP_ZERO;
        }

        /* Finish TP session. */
        DoIP_TcpCon2TxTpSessionActive[connection] = FALSE;
        /* Modified 2022-02-10 */
#if( DOIP_NACK_APPEND_REQ == STD_ON )
        if( DOIP_INV_TESTER_IDX != DoIP_TcpCon2ActivMgt[connection].testerIdx )
        {
            DoIP_Tester2DiagNAckOffset[DoIP_TcpCon2ActivMgt[connection].testerIdx] = DOIP_ZERO;
        }
#endif /* ( DOIP_NACK_APPEND_REQ == STD_ON ) */

        DoIP_TcpCon2TxBytesCopied[connection] = DOIP_ZERO;

        if( channel != DOIP_INV_PDU_ID )
        {
            DoIP_Channel2TxMsgLen[channel] = DOIP_ZERO;
            DoIP_TcpCon2TcpTxMgt[connection][queIdx].channel = DOIP_INV_PDU_ID;
            DOIP_EXIT_CRITICAL0();
            /* Forward TxConfirmation to upper layer */
            if( DOIP_IFPDU == DoIP_Channel2ApiType[channel] )
            {
                if( DOIP_INV_PDU_ID != DoIP_Channel2PduRTxConfPduId[channel] )
                {
                    /* TxConfirmation enabled */
                    //PduR_DoIPIfTxConfirmation(DoIP_Channel2PduRTxConfPduId[channel], result);
                }
            }
            else
            {
                //PduR_DoIPTpTxConfirmation(DoIP_Channel2PduRTxConfPduId[channel], result);
            }
        }
        else
        {
             DOIP_EXIT_CRITICAL0();
        }
    }
    else
    {
        DOIP_EXIT_CRITICAL0();
    }
}

Std_ReturnType PduR_DoIPTpCopyTxData(PduIdType DoIPPduId,PduInfoType *locPduInfoPtr,void* ptr,PduInfoType* availablDataPtr)
{
      //todo
} 
/*
*******************************************************************************
* Function Name: DoIP_CloseSoCon
*
* Explanation: Close socket connection.
*
* param: connection: Connection to be closed.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE)DoIP_CloseSoCon(PduIdType connection)
{
    pthread_mutex_lock(&mutex);
    printf("Server close socket:FIN\n");
    close(DoIP_Con2SoConId[connection]);
    ActiveConfig_Init(connection);
    DoIP_Con2SoConClosing[connection] = TRUE;
    DoIP_Con2SoConState[connection] = SOAD_SOCON_OFFLINE;
    DoIP_Con2IpAddrState[connection] = SOAD_IPADDR_STATE_ASSIGNED;
    DoIP_Con2SoConId[connection] = SOAD_INV_SO_CON_ID;
    FlagIsconnect = FALSE;
    DoIP_TcpCon2InactivCnt[connection] = DOIP_ZERO;
    pthread_mutex_unlock(&mutex);
}
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_CloseSoConUDP(PduIdType connection)
{
    close(connection);
    DoIP_Con2SoConUDPState[0] = SOAD_SOCON_OFFLINE;
}

DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TcpTxQueueCopyDiagReqData
(
    boolean headerCopied,
    PduIdType connection,
    uint32 txMgtQueIdx,
    PduInfoType* pduInfoPtr,
    PduLengthType* availableDataPtr
)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    PduIdType channel = DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].channel;
    PduInfoType *locPduInfoPtr = pduInfoPtr;
    PduInfoType locPduInfoStruct = { NULL_PTR, DOIP_ZERO };
    if( TRUE == headerCopied )
    {
        /* Query available upper layer buffer if header was copied successful. */
        /* Query Tx buffer size of upper layer. */
        locPduInfoPtr = &locPduInfoStruct;
    }

    /* Call upper layer CopyTxData function to query available buffer or copying. */
    retVal = PduR_DoIPTpCopyTxData(DoIP_Channel2PduRTxConfPduId[channel], locPduInfoPtr, NULL_PTR, availableDataPtr);
    if( DOIP_ZERO == DoIP_TcpCon2TxMgtQueLvl[connection] )
    {
        /* Check if Tx Queue has been modifed (e.g. connection closed) */
        retVal = BUFREQ_E_NOT_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
        DoIP_DebugTxCnt[connection].txQueEmpty++;
#endif
        /* return BUFREQ_E_NOT_OK */
    }
    else
    {
        if( BUFREQ_OK == retVal )
        {
            /* buffer request was sucessful */
            DoIP_TcpCon2LastTxBufSize[connection] = *availableDataPtr;
            if( (DOIP_ZERO == locPduInfoPtr->SduLength) && (pduInfoPtr->SduLength != DOIP_ZERO) )
            {
                /* available buffer of upper layer was requested by DoIP - do not forward return value of upper layer */
                /* return BUFREQ_OK; */
            }
            else
            {
                DoIP_TcpCon2TxBytesCopied[connection] += locPduInfoPtr->SduLength;
            }
        }
        else
        {
            /* buffer request failed */
            /* Close connection since generic header has already been sent. */
            //DoIP_Con2SoConClosing[connection] = TRUE;
            DoIP_CloseSoCon(connection);
            ActiveConfig_Init(connection);
            retVal = BUFREQ_E_NOT_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
            DoIP_DebugTxCnt[connection].txBufReqFail++;
#endif
        }
    }

    return retVal;
}

DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TcpTxQueueCopyDiagNAckData
(
    boolean headerCopied,
    PduIdType connection,
    uint32 txMgtQueIdx,
    PduInfoType* pduInfoPtr,
    PduLengthType* availableDataPtr
)
{
#if( DOIP_NACK_APPEND_REQ == STD_ON )
    uint8 testerIdx = DoIP_TcpCon2ActivMgt[connection].testerIdx;
    PduLengthType startPos = DoIP_TcpCon2TxBytesCopied[connection] - DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen;

    if( (pduInfoPtr->SduLength != DOIP_ZERO) && ( FALSE == headerCopied ) )
    {
        /* Copy data to target buffer */
        DoIP_Memcpy((uint8*)pduInfoPtr->SduDataPtr,
                    (const uint8*)(&DoIP_Tester[testerIdx].diagAckNackBufPtr[startPos]),
                    pduInfoPtr->SduLength);
        DoIP_TcpCon2TxBytesCopied[connection] += pduInfoPtr->SduLength;
        if( DoIP_TcpCon2TxBytesCopied[connection] == DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].msg.SduLength )
        {
            /* All data are copied to lower layer buffer */
            /* reset DiagNAck buffer offset to indicate that new data can be received (do not wait for TxConfirmation) */
            DoIP_Tester2DiagNAckOffset[testerIdx] = DOIP_ZERO;
        }
    }
    /* set available data length */
    *availableDataPtr = DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].msg.SduLength - DoIP_TcpCon2TxBytesCopied[connection];
    DoIP_TcpCon2LastTxBufSize[connection] = *availableDataPtr;
#else
    DOIP_DUMMY_STATEMENT(headerCopied);
    DOIP_DUMMY_STATEMENT(connection);
    DOIP_DUMMY_STATEMENT(txMgtQueIdx);
    DOIP_DUMMY_STATEMENT(pduInfoPtr);
    DOIP_DUMMY_STATEMENT(availableDataPtr);
#endif
    return BUFREQ_OK;
}

/*
*******************************************************************************
* Function Name: DoIP_TcpTxQueueCopyElement
*
* Explanation: Copy the element to Tcp tx quenue.
*
* param: connection: Socket connection.
*        pduInfoPtr: Pdu information pointer.
*        availableDataPtr: Available data pointer.
*
* retval: BUFREQ_OK: Data has been copied to the transmit buffer completely
*                    as requested.
*         BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
*******************************************************************************
*/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TcpTxQueueCopyElement
(
    PduIdType connection,
    PduInfoType* pduInfoPtr,
    PduLengthType* availableDataPtr
)
{
    boolean headerCopied = FALSE;
    BufReq_ReturnType retVal = BUFREQ_OK;
    uint16 hdrType;
    uint32 txMgtQueIdx;

    if( (DoIP_TcpCon2TxTpSessionActive[connection] != TRUE) ||
        (TRUE == DoIP_TcpCon2TxTpCancelRequested[connection]) )
    {
        /* Check whether TP session is online. */
        /* TP cancellation is ongoing */
        retVal = BUFREQ_E_NOT_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
        DoIP_DebugTxCnt[connection].txStateError++;
#endif
        /* return retVal; */
    }
    else
    {
        if( DOIP_ROUT_ACTIV_STATE_ACTIVATED == DoIP_TcpCon2ActivMgt[connection].activState )
        {
            /* Routing activation active. */
            /* Reset inactivity timer. */
            DoIP_TcpCon2InactivCnt[connection] = DOIP_ZERO;
        }
        txMgtQueIdx = DoIP_TcpCon2TxMgtQueIdx[connection];
        /* Extract message type. */
        DOIP_GET_UINT16(&DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHeader[DOIP_GEN_HDR_TYPE_IDX], DOIP_ZERO, hdrType);

        if( (pduInfoPtr->SduLength != DOIP_ZERO) && ( pduInfoPtr->SduLength > DoIP_TcpCon2LastTxBufSize[connection]) )
        {
            /* unexpected length */
            retVal = BUFREQ_E_NOT_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
            DoIP_DebugTxCnt[connection].txLenError++;
#endif
            /* return retVal; */
        }
        else
        {
            if( DoIP_TcpCon2TxBytesCopied[connection] < DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen )
            {
                /* Header is not yet copied. */
                if( pduInfoPtr->SduLength !=  DOIP_ZERO )
                {
                    /* Subsequent call - copy request */
                    /* Check requested length */
                    if( ((PduLengthType)DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen - DoIP_TcpCon2TxBytesCopied[connection]) >= pduInfoPtr->SduLength )
                    {
                        DoIP_Memcpy((uint8*)pduInfoPtr->SduDataPtr,
                                    (const uint8*)(&DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHeader[DoIP_TcpCon2TxBytesCopied[connection]]),
                                    pduInfoPtr->SduLength);
                        DoIP_TcpCon2TxBytesCopied[connection] += pduInfoPtr->SduLength;
                        if( DoIP_TcpCon2TxBytesCopied[connection] == DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen )
                        {
                            /* header copied completely */
                            headerCopied = TRUE;
                            if( (DOIP_HDR_TYPE_ROUT_ACTIV_ACK == hdrType) &&
                                (DoIP_TcpCon2ActivMgt[DoIP_RoutActivHandler[connection].tcpCon].activState != DOIP_ROUT_ACTIV_STATE_CONF_PENDING) )
                            {
                                /* Routing Activation Response */
                                /* In case of confirmation a Routing Activation Response might be sent even if Routing Activation
                                   is not finished. Release Routing Activation Handler in all other cases. */
                                DoIP_RoutActivHandler[connection].tcpCon = DOIP_INV_PDU_ID;
                            }
                        }
                        /* set available data length */
                        *availableDataPtr = DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen - DoIP_TcpCon2TxBytesCopied[connection];
                        DoIP_TcpCon2LastTxBufSize[connection] = *availableDataPtr;
                    }
                    else
                    {
                        /* invalid length */
                        retVal = BUFREQ_E_NOT_OK;
#if( DOIP_LOCAL_DEBUG == STD_ON )
                        DoIP_DebugTxCnt[connection].txLenError++;
#endif
                        /* return retVal; */
                    }
                }
                else
                {
                    /* set available data length */
                    *availableDataPtr = DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen - DoIP_TcpCon2TxBytesCopied[connection];
                    DoIP_TcpCon2LastTxBufSize[connection] = *availableDataPtr;
                }
            }
            if( (BUFREQ_OK == retVal) &&
                (DoIP_TcpCon2TxBytesCopied[connection] >= DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen) &&
                (DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].txHdrBufLen < DoIP_TcpCon2TcpTxMgt[connection][txMgtQueIdx].msg.SduLength) )
            {
                /* Header copied completely and more data are available. */
                switch( hdrType )
                {
                    case DOIP_HDR_TYPE_DIAG_REQ:
                    {
                        /* diagnostic message */
                        retVal = DoIP_TcpTxQueueCopyDiagReqData(headerCopied, connection, txMgtQueIdx, pduInfoPtr, availableDataPtr);
                        break;
                    }
                    case DOIP_HDR_TYPE_DIAG_ACK:
                    case DOIP_HDR_TYPE_DIAG_NACK:
                    {
                        /* Diagnostic message positive/negative acknowledge */
                        retVal = DoIP_TcpTxQueueCopyDiagNAckData(headerCopied, connection, txMgtQueIdx, pduInfoPtr, availableDataPtr);
                        break;
                    }
                    default:
                    {
                        /* Nothing to do. */
                        break;
                    }
                }
            }
        }
    }
    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_SoAdIfRxDataOfHdrTyp
*
* Explanation: Indication of a received I-PDU from a lower layer communication
*              interface module.
*
* param: RxPduId: ID of the received I-PDU.
*        srcHdrType: Header type of the source data.
*        dataOffset: Data offset.
*        PduInfoPtr: Contains the length (SduLength) of the received I-PDU
*                    and a pointer to a buffer (SduDataPtr) containing the I-PDU.
*        closeSocket: TRUE:Close socket,FALSE: Not close socket.
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00009] */
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_SoAdIfRxDataOfHdrTyp
(
    PduIdType RxPduId,
    uint16 srcHdrType,
    uint32 srcHdrLen,
    uint32 dataOffset,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)PduInfoPtr,
    boolean closeSocket
)
{
    uint8 identIdx;
    uint8 vinIdx = DOIP_VIN_LEN_BYTE;
    boolean identOk = TRUE;
    DoIP_PowerStateType diagPowerMode = DOIP_POWER_MODE_NOT_SUPPORTED;

#if ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
    uint8 physAddrBuf[DOIP_HWID_LEN_BYTE] = {DOIP_FF, DOIP_FF, DOIP_FF, DOIP_FF, DOIP_FF, DOIP_FF};
#endif    /* ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON ). */

    uint8 vin[DOIP_VIN_LEN_BYTE] = {DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO,
                                    DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO,
                                    DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO, DOIP_ZERO};
    /* Further handling depends on message type. */
    switch( srcHdrType )
    {
        /* Vehicle identification request. */
        case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ:
        {
            /* Max length exceeded. */
            if( DOIP_MAX_REQUEST_BYTES < srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, closeSocket);
                break;
            }
            /* Length check failed. */  /* [SWS_DoIP_00059] */
            if( DOIP_ZERO != srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, closeSocket);
            }
            else
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_IDENT_RES_NUM, closeSocket);
            }

            break;
        }
        /* Vehicle identification with VIN (check for our VIN). [SWS_DoIP_00069] */
        case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN:
        {
            /* Max length exceeded. */
            if( DOIP_MAX_REQUEST_BYTES < srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, closeSocket);
                break;
            }
            /* Length check failed. [SWS_DoIP_00068] */
            if( DOIP_VIN_LEN_BYTE != srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, closeSocket);
            }
            /* Length check ok. */
            else
            {
                /* VIN successfully retrieved. */
                /* Compare to retrieved VIN. [SWS_DoIP_00070] */
                if( (Std_ReturnType)E_OK == DoIP_GetVinFun(vin) )
                {
                    while( DOIP_ZERO < vinIdx )
                    {
                        vinIdx--;
                        if( PduInfoPtr->SduDataPtr[dataOffset + DOIP_GEN_HDR_LEN_BYTE + vinIdx] != vin[vinIdx] )
                        {
                          identOk = FALSE;
                          break;
                        }
                    }
                }
                /* VIN request failed. */
                /* Compare to invaliditiy pattern. */
                else
                {
                    while( DOIP_ZERO < vinIdx )
                    {
                        vinIdx--;
                        if( PduInfoPtr->SduDataPtr[dataOffset + DOIP_GEN_HDR_LEN_BYTE + vinIdx] != DOIP_VIN_INV_PATTERN )
                        {
                            identOk = FALSE;
                            break;
                        }
                    }
                }

                if( (boolean)TRUE == identOk )
                {
                    (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_IDENT_RES_NUM, closeSocket);
                }
            }
            break;
        }
        /* Vehicle identification with entity id (check for our physical address (MAC address)). [SWS_DoIP_00064] */
        case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_EID:
        {
            /* Max length exceeded. */
            if( DOIP_MAX_REQUEST_BYTES < srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, closeSocket);
                break;
            }
            /* Length check failed. [SWS_DoIP_00063] */
            if( DOIP_HWID_LEN_BYTE != srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, closeSocket);
            }
            /* Length check ok. */
            else
            {
                identOk  = TRUE;
                identIdx = DOIP_HWID_LEN_BYTE;

#if ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
                if( E_OK == SoAd_GetPhysAddr(DoIP_Con2SoConId[RxPduId], &physAddrBuf[DOIP_ZERO]) )   /* [SWS_DoIP_00065] */
                {
                    while( DOIP_ZERO < identIdx )
                    {
                        identIdx--;
                        if( PduInfoPtr->SduDataPtr[dataOffset + DOIP_GEN_HDR_LEN_BYTE + identIdx] != physAddrBuf[identIdx] )
                        {
                            identOk = FALSE;
                            break;
                        }
                    }
                }
                else
                {
                    identOk = FALSE;
                }
#else
                while( DOIP_ZERO < identIdx )
                {
                    identIdx--;
                    if( PduInfoPtr->SduDataPtr[dataOffset + DOIP_GEN_HDR_LEN_BYTE + identIdx] != (uint8)(DoIP_Eid[identIdx]) )  /* [SWS_DoIP_00066] */
                    {
                        identOk = FALSE;
                        break;
                    }
                }
#endif /* ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON ) */

                if( (boolean)TRUE == identOk )
                {
                    (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_IDENT_RES_NUM, closeSocket);
                }
            }
            break;
        }
        /* Diagnostic power mode request. */
        case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_REQ:
        {
            /* Max length exceeded. [SWS_DoIP_00017] */
            if( DOIP_MAX_REQUEST_BYTES < srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, closeSocket);
                break;
            }
            /* length check failed. [SWS_DoIP_00091] */
            if( DOIP_ZERO != srcHdrLen )
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, closeSocket);
            }
            else /* Length check ok. */
            {

#ifdef DOIP_CALL_GET_POWERMODE_DIRECT
                /* [SWS_DoIP_00093] */
                if( (Std_ReturnType)E_NOT_OK == DOIP_CALL_GET_POWERMODE_DIRECT(&diagPowerMode) )
                {
                    diagPowerMode = DOIP_POWER_MODE_NOT_READY;
                }
                /* [SWS_DoIP_00092] */
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK, diagPowerMode, closeSocket);
#endif

            }
            break;
        }
        case DOIP_HDR_TYPE_ENTITY_STATE_REQ:    /* Entity status request. */
        {
            if( DOIP_MAX_REQUEST_BYTES < srcHdrLen)    /* Max length exceeded. [SWS_DoIP_00017] */
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, closeSocket);
                break;
            }
            if( DOIP_ZERO != srcHdrLen )    /* Length check failed. [SWS_DoIP_00095] */
            {
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, closeSocket);
            }
            else    /* Length check ok. */
            {
                /* [SWS_DoIP_00096] */
                (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_ENTITY_STATE_ACK, DOIP_UNUSED_PARAM, closeSocket);
            }
            break;
        }
        /* [SWS_DoIP_00292] */
        case DOIP_HDR_TYPE_GEN_NACK:
        /* [SWS_DoIP_00293] */
        case DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT:
        case DOIP_HDR_TYPE_ROUT_ACTIV_REQ:
        case DOIP_HDR_TYPE_ROUT_ACTIV_ACK:
        case DOIP_HDR_TYPE_ALIVE_CHECK_REQ:
        case DOIP_HDR_TYPE_ALIVE_CHECK_ACK:
        case DOIP_HDR_TYPE_ENTITY_STATE_ACK:
        case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK:
        case DOIP_HDR_TYPE_DIAG_REQ:
        case DOIP_HDR_TYPE_DIAG_ACK:
        case DOIP_HDR_TYPE_DIAG_NACK:
        {
            /* Ignore not relevant header type. */
            break;
        }
        default:
        {
            /* TxNack: unknown header type. */
            (void)DoIP_UdpTransmit(RxPduId, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, closeSocket);  /* [SWS_DoIP_00016] */
            break;
        }
    }
}

/*
*******************************************************************************
* Function Name: DoIP_GetConnectionBySoConId
*
* Explanation: Get connection by Socket connection index.
*
* param: SoConId: Socket connection index.
*        connection: Connection index.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetConnectionBySoConId
(
    SoAd_SoConIdType SoConId,
    P2VAR(PduIdType, AUTOMATIC, DOIP_APPL_DATA)connection
)
{
    Std_ReturnType retVal = E_NOT_OK;
    PduIdType pduId = DOIP_CONNECTION_TOTAL;

    if( NULL_PTR != connection )
    {
        while( DOIP_ZERO < pduId )
        {
            pduId--;
            if( (DoIP_Con2SoConId[pduId] == SoConId) && (SOAD_INV_SO_CON_ID != SoConId) )
            {
                *connection = pduId;
                retVal = E_OK;
                break;
            }
        }
    }

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_OpenSockConInitially
*
* Explanation: Open sock con initially.
*
* param: connection: Connection index.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_OpenSockConInitially(PduIdType connection)
{
    if( (uint8)SOAD_SOCON_OFFLINE == DoIP_Con2SoConState[connection] )
    {
        /* Call SoAd to reopen socket connection. */
        /* Set state to reconnect to avoid multiple open requests. */
        setSocketcon(DoIP_Con2SoConId[connection]);
        while (connect(DoIP_Con2SoConId[connection], (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        {
             printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        }
        //(void)SoAd_OpenSoCon(DoIP_Con2SoConId[connection]);
    }
}
Std_ReturnType SoAd_WriteDhcpHostNameOption
(
    SoAd_SoConIdType SoConId,
    uint8 length,
    const uint8* data
)
{
    //todo
}
/*
*******************************************************************************
* Function Name: DoIP_RefreshDhcpHostName
*
* Explanation: This function is used to refresh DHCP host name.
*
* param: SoAd_SoConIdType: SoCon identifier type for unique identification of
*                           a SoAd socket connection.
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_RefreshDhcpHostName(SoAd_SoConIdType soConId)
{
    uint8 compareRetVal;
    /* define local Vin Buffer and length*/
    uint8 hostName[DOIP_MIN_HOST_NAME_SIZE + DOIP_VIN_PREFIX_LEN_BYTE + DOIP_VIN_LEN_BYTE] = {0};
    uint8 bufLen = (uint8)sizeof(hostName);

    /* [SWS_DoIP_00154] - call the function SoAd_ReadDhcpHostNameOption with the received SoConId to get the currently set host name option */
    if( (uint8)E_OK == (uint8)SoAd_ReadDhcpHostNameOption(soConId, &bufLen, hostName) )
    {
        /* 'D', 'o', 'I', 'P', '-', 'V', 'I', 'N' */
        /* uint8 doIPStr[DOIP_MIN_HOST_NAME_SIZE] = {0x44U, 0x6FU, 0x49U, 0x50U, 0x2DU}; */
        /* uint8 doIPVinStr[DOIP_EIGHT] = {0x44U, 0x6FU, 0x49U, 0x50U, 0x2DU, 0x56U, 0x49U, 0x4EU}; */
        uint8 doIPStr[DOIP_MIN_HOST_NAME_SIZE] = {'D', 'o', 'I', 'P', '-'};
        uint8 doIPVinStr[DOIP_EIGHT] = {'D', 'o', 'I', 'P', '-', 'V', 'I', 'N'};

        /* [SWS_DoIP_00154] - the returned Byte buffer shall be considered as ASCII buffer and shall start with "DoIP-" */
        compareRetVal = DoIP_ASCIICompare((const uint8*)hostName, (const uint8*)doIPStr, (uint8)sizeof(doIPStr));
        if( (uint8)E_OK != (uint8)compareRetVal )
        {
            /* the configuration parameter DoIPDhcpOptionVinUse is set */
#if( DOIP_DHCP_OPTION_VIN_USE_ENABLED == STD_OFF )
            /* [SWS_DoIP_00155] */
            /* DoIP_CopyData(hostName, doIPStr, (uint8)sizeof(doIPStr)); */
            (void)SoAd_WriteDhcpHostNameOption(soConId, DOIP_MIN_HOST_NAME_SIZE, doIPStr);
#else
            /* [SWS_DoIP_00156] - Fill up initial "DoIP-VIN" */
            DoIP_CopyData(hostName, doIPVinStr, (uint8)sizeof(doIPVinStr));
            /* [SWS_DoIP_00156] - Call CB_GETVIN to get VIN */
            DoIP_GetVinFun(&hostName[(uint8)sizeof(doIPVinStr)]);
            /* [SWS_DoIP_00156] - Call the SoAd_WriteDhcpHostNameOption with actual VIN */
            (void)SoAd_WriteDhcpHostNameOption(soConId, (uint8)sizeof(hostName), hostName);
#endif
        }
    }
}
/*
*******************************************************************************
* Function Name: SoAd_ReadDhcpHostNameOption
*
* Explanation: call the function SoAd_ReadDhcpHostNameOption with the received SoConId to 
               get the currently set host name option 
* param: SoConId : 套接字连接标识符
*        length: 数据长度
*        data:     读取到的主机名.
* retval: E_OK:     请求读取 DHCP 主机名被接受.
*         E_NOT_OK:  请求读取 DHCP 主机名未被接受.
*******************************************************************************
*/
int getResultFromSystemCall(const char* pCmd, uint8* pResult, int size)
{
   int fd[2];
   if(pipe(fd))   {
      printf("pipe error!\n");
      return -1;
   }
 
   //hide stdout
   int bak_fd = dup(STDOUT_FILENO);
   int new_fd = dup2(fd[1], STDOUT_FILENO);
 
   //the output of `pCmd` is write into fd[1]
   system(pCmd);
   read(fd[0], pResult, size-1);
   pResult[strlen(pResult)-1] = 0;
 
   //resume stdout
   dup2(bak_fd, new_fd);
 
   return 0;
}
Std_ReturnType SoAd_ReadDhcpHostNameOption
(
    SoAd_SoConIdType SoConId,
    uint8* length,
    uint8* data
)
{
    char* cmd = "hostname";
    if(getResultFromSystemCall(cmd,data,&length) == 0)
        return (Std_ReturnType)E_OK;
    else
        return (Std_ReturnType)E_NOT_OK;
}

/*
*******************************************************************************
* Function Name: DoIP_ASCIICompare
*
* Explanation: This function is used to compare data between refer value and
*              compared value.
* param: refervalue: refer value
*        comparevalue: compare value
*        length:     define data length which need to compare.
* retval: E_OK:      compare data has been completed.
*         E_NOT_OK:  compare data has been not completed.
*******************************************************************************
*/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_ASCIICompare
(
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST)refervalue,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST)comparevalue,
    uint8 length
)
{
    uint8 len = length;
    uint8 loop = DOIP_ZERO;
    uint8 retValue = E_OK;

    if( (refervalue == NULL_PTR) || (comparevalue == NULL_PTR) )
    {
        retValue = E_NOT_OK;
    }

    while( ((uint8)retValue == (uint8)E_OK) && ((uint8)len > (uint8)0) )
    {
        if( (uint8)(refervalue[loop]) != (uint8)(comparevalue[loop]) )
        {
            retValue = E_NOT_OK;
            break;
        }
        else
        {
            loop++;
            len--;
        }
    }

    return retValue;
}

/*
*******************************************************************************
* Function Name: DoIP_CopyData
*
* Explanation: This function is used to transfer data in source address to
*              destination.
* param: destinAddr: destination which data will be transfer to.
*        sourceAddr: source address in which data is store now.
*        length:     define data length which need to copy.
* retval: E_OK:      copy data has been completed.
*         E_NOT_OK:  copy data has been not completed.
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_CopyData
(
    P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA)destinAddr,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST)sourceAddr,
    uint8 length
)
{
    uint8 len = length;
    uint8 loop = 0;
    uint8 retValue = E_NOT_OK;

    if( (destinAddr != NULL_PTR) && (sourceAddr != NULL_PTR) )
    {
        retValue = E_OK;
    }

    while( ((uint8)retValue == (uint8)E_OK) && ((uint8)len > (uint8)0) )
    {
        destinAddr[loop] = sourceAddr[loop];
        loop++;
        len--;
    }
}

/*
*******************************************************************************
* Function Name: DoIP_ActivationLineStateTransitionToActive
*
* Explanation: ActivationLine state transition to active.
*
* param: None
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00204] */
void DoIP_ActLineToActive(void)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    Std_ReturnType retVal = E_OK;
    PduIdType connection;
    uint8 soConId = DOIP_ZERO;

    /* Initiate socket connection structs if not done before. */
    if(SOAD_INV_SO_CON_ID == sockCon)
    {
        retVal |= DoIP_GetSoConIdByConId(connection, &soConId);
        if( (Std_ReturnType)E_OK == retVal )
        {
            sockCon = soConId;
            //DoIP_Con2SoConId[connection] = soConId;
        }
        else
        {
            errorId = DOIP_E_SOAD_CALL_FAILED;
        }
    }
    if( E_OK == retVal )
    {
        /* Switch to active. */
        DoIP_ActivationLineLocalState = DOIP_ACTIVATION_LINE_LOCAL_ACTIVE;
        for( connection = DOIP_ZERO; connection < DOIP_CONNECTION_TOTAL; connection++ )
        {
            if( TRUE == DoIPRequestAddressAssignment[connection] )
            {
                /* [SWS_DoIP_00204] */
                DoIP_Con2IpAddrState[connection] = SOAD_IPADDR_STATE_ASSIGNED;
               // SoAd_RequestIpAddrAssignment(DoIP_Con2SoConId[connection], TCPIP_IPADDR_ASSIGNMENT_ALL, NULL_PTR, 0, NULL_PTR);
            }
            else
            {
                printf("OpenSoCon\n");
                //xiugai
                //SoAd_OpenSoCon(DoIP_Con2SoConId[connection]);
            }
        }
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_VACT_LINE_STATE_TRANS_TO_ACT, errorId);
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_ActivationLineStateTransitionToInactive
*
* Explanation: ActivationLine state transition to inactive.
*
* param: None
*
* retval: None
*******************************************************************************
*/
#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_ActLineToInactive(void)
{
    boolean soConsClosed = TRUE;
    uint8 localAddrIdx = DOIP_LOCAL_ADDR_TOTAL;
    uint8 localAddrUnassigned = DOIP_ZERO;
    PduIdType connection = DOIP_CONNECTION_TOTAL;

    while( DOIP_ZERO < connection )
    {
        connection--;
        /* [SWS_DoIP_00001] */
        if( (uint8)SOAD_SOCON_OFFLINE != DoIP_Con2SoConState[connection] )
        {
            /* Socket connection not closed yet. */
            soConsClosed = FALSE;
            if( (uint8)TRUE != DoIP_Con2SoConClosing[connection] )
            {
                /* Socket connection not requested to be closed. */
               // DoIP_Con2SoConClosing[connection] = TRUE;
                DoIP_CloseSoCon(connection);
                ActiveConfig_Init(connection);
            }
        }
    }

    if( FALSE != soConsClosed )
    {
        /* All socket connections closed. */
        /* Release IP address assignment on all local addresses. */
        while( DOIP_ZERO < localAddrIdx )
        {
            /* Iterate over all UdpConnections and release IP address assignment on one UdpConnection of each local address. */
            localAddrIdx--;

            if( (DOIP_IP_ADDR_REQ_STATE_NONE != DoIP_LocalAddrIdx2IpAddrReqState[localAddrIdx]) &&
                (DOIP_IP_ADDR_REQ_STATE_RELEASE != DoIP_LocalAddrIdx2IpAddrReqState[localAddrIdx]) )
            {
                if( DOIP_IPADDR_ASSIGN_TRIGGER_DISABLE == DoIP_LocalAddrIdx2AssignmentType[localAddrIdx] )
                {
                    localAddrUnassigned++;
                }
                else
                {
                    /* Local address not yet released on this local address. */
                    connection = DOIP_CONNECTION_TOTAL;
                    while( DOIP_ZERO < connection )
                    {
                        connection--;
                        if( (DoIP_Con2LocalAddrIdx[connection] == localAddrIdx) &&
                            (TRUE == DoIPRequestAddressAssignment[connection]) )
                        {
                            /* UdpConnection for current local address found. */
                            DoIP_LocalAddrIdx2IpAddrReqState[localAddrIdx] = DOIP_IP_ADDR_REQ_STATE_RELEASE;
                            /* Release IP address assignment. [SWS_DoIP_00235]*/
                            //xiugai
                            #if false
                            if( (Std_ReturnType)E_OK != SoAd_ReleaseIpAddrAssignment(DoIP_Con2SoConId[connection]) )
                            {
                                /* Release failed. */
                                /* No requirement specified. */
                                /* Perform retry in next MainFunction cycle. */
                                DoIP_LocalAddrIdx2IpAddrReqState[localAddrIdx] = DOIP_IP_ADDR_REQ_STATE_ASSIGNED;
                            }
                            else
                            {
                                DoIP_LocalAddrIdx2IpAddrReqState[localAddrIdx] = DOIP_IP_ADDR_REQ_STATE_NONE;
                            }
                            #endif
                            break;
                        }
                    }
                }
            }
            else if( DOIP_IP_ADDR_REQ_STATE_NONE == DoIP_LocalAddrIdx2IpAddrReqState[localAddrIdx] )
            {
                localAddrUnassigned++;
            }
            else
            {
                /* Nothing to do. */
            }
        }

        /* Check if all local addresses are unassigned. */
        if( DOIP_LOCAL_ADDR_TOTAL == localAddrUnassigned )    /* All local addresses unassigned. */
        {

#if( DOIP_GID_SYNC_ENABLED == STD_ON )
            /* Reset GID sync. */
            DoIP_GidInSync = FALSE;
#endif /* ( DOIP_VGID_SYNC_ENABLED == STD_ON ) */

            /* Switch to inactive. */
            DoIP_ActivationLineLocalState = DOIP_ACTIVATION_LINE_LOCAL_INACTIVE;
        }
    }
}
#endif

/*
*******************************************************************************
* Function Name: DoIP_HandleSockConStates
*
* Explanation: Handle sock connection states.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) 
DoIP_HandleSockConStates(void)
{
    PduIdType connection = DOIP_ZERO;
    fflush(stdout);
     int err=0;
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
   if( ((uint8)SOAD_SOCON_OFFLINE == DoIP_Con2SoConState[connection]) &&
        (SOAD_IPADDR_STATE_ASSIGNED == DoIP_Con2IpAddrState[connection]) &&
        (TRUE == DoIP_IsTcpClientConnection[DOIP_ZERO]) && sockCon != SOAD_INV_SO_CON_ID )
    {
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(13400);
        servaddr.sin_addr.s_addr=inet_addr(DoIPTestersetIP);
        int severlen = sizeof(servaddr);

        int ret = connect(sockCon,(struct sockaddr*)&servaddr,severlen);
        if(ret == 0)
        {
            DoIP_Con2SoConId[connection] = sockCon;
            DoIP_RoutActivHandler[connection].tcpCon = sockCon;
            DoIP_RoutActivHandler[connection].testerAddr = DoIP_Tester[0].testerAddr;
            DoIP_RoutActivHandler[connection].routActIdx = 0;
            DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_TOACTIVATE;
            DoIP_TcpCon2ActivMgt[connection].actType =  DoIP_RoutActivHandler[connection].routActIdx ;
            DoIP_TcpCon2ActivMgt[connection].testerAddr = DoIP_Tester[0].testerAddr;
            DoIP_SoConModeChg(connection,SOAD_SOCON_ONLINE);
            FlagIsconnect = TRUE;
            DoIP_Con2SoConClosing[connection] = FALSE;
        }
    }

#else


    nfds = epoll_wait(epfd,events,20,0);
    
    for(int i = 0;i < nfds;i++)
    {
        if(EPOLLIN == events[i].events)
        {
            if(events[i].data.fd == sockCon)
            {
                int acceptSocket = accept(sockCon,(struct sockaddr*)&clientAddr,&clientAddr);
                if(acceptSocket > 0)
                {
                     
                   err= fcntl(acceptSocket,F_SETFL,O_NONBLOCK);
                    struct epoll_event ev;
                    ev.events = EPOLLIN;
                    ev.data.fd = acceptSocket;
                    printf("Aceept the connection of ClientSocket:%d\n",acceptSocket);
                    epoll_ctl(epfd, EPOLL_CTL_ADD, acceptSocket, &ev);
                    for(;connection < DOIP_CONNECTION_TOTAL;)
                    {
                        if(DoIP_Con2SoConId[connection] == DOIP_INV_PDU_ID)
                        {
                            break;
                        }
                        connection++;
                    }
                    SoAd_SoConIdType* p = &DoIP_Con2SoConId[connection];
                    *p = acceptSocket;
                    DoIP_SoConModeChg(connection,SOAD_SOCON_ONLINE);
                    FlagIsconnect = TRUE;
                    DoIP_Con2SoConState[connection] = SOAD_SOCON_ONLINE;
                    DoIP_Con2SoConClosing[connection] = FALSE;
                }
            }
        }
    }
#endif

//     while( connection < DOIP_CONNECTION_TOTAL )
// #if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_OFF )  
//     {
       
//         if( ((uint8)SOAD_SOCON_OFFLINE == DoIP_Con2SoConState[connection]) &&
//             (SOAD_IPADDR_STATE_ASSIGNED == DoIP_Con2IpAddrState[connection]) &&
//             (FALSE == DoIP_IsTcpClientConnection[DOIP_ZERO]) && sockCon != SOAD_INV_SO_CON_ID )
//         {
//         //    printf("waiting for TCP Client....\n");
//         //    printf("DoIP_Con2SoConState[connection] = %d\n",DoIP_Con2SoConState[connection]);
//         //    printf("DoIP_Con2IpAddrState[connection] = %d\n",DoIP_Con2IpAddrState[connection]);
//         //    printf("DoIP_IsTcpClientConnection[connection] = %d\n",DoIP_IsTcpClientConnection[DOIP_ZERO]);

//             //DoIP_SoConModeChg(connection,SOAD_SOCON_ONLINE);
//             /* Call SoAd to reopen socket connection. */
            

//             int clientlen = sizeof(clientAddr);

          
//             pthread_mutex_lock(&mutex);
            
//             int acceptSocket = accept(sockCon,(struct sockaddr*)&clientAddr,&clientAddr);
//             //printf("error = %d,string = %s \n",errno,strerror(errno));
//             if(acceptSocket > 0)
//             {
//                 SoAd_SoConIdType* p = &DoIP_Con2SoConId[connection];
//                 *p = acceptSocket;
//                 //DoIP_Con2SoConId[connection] = acceptSocket;
//                 //DoIP_Con2SoConId = p;
//                 DoIP_SoConModeChg(connection,SOAD_SOCON_ONLINE);
//                 FlagIsconnect = TRUE;
//                 fflush(stdout);
//                 DoIP_Con2SoConState[connection] = SOAD_SOCON_ONLINE;
//                 DoIP_Con2SoConClosing[connection] = FALSE;
//             }
//             //DoIP_Con2SoConId[connection] = accept(sockCon,(struct sockaddr*)&clientAddr,&clientAddr);

            
//             pthread_mutex_unlock(&mutex);

//             // if (connect(DoIP_Con2SoConId[connection], (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
//             //     {
//             //         printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
//             //         close(DoIP_Con2SoConId[connection]);
//             //     }


//             //(void)SoAd_OpenSoCon(DoIP_Con2SoConId[connection]);
//             /* Set state to reconnect to avoid multiple open requests. */
//         }
//         connection++;
//     }
// #endif
}

/*
*******************************************************************************
* Function Name: DoIP_HandleGidSync
*
* Explanation: Handle gid synchronization.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleGidSync(void)
{
    uint8_least localAddrIdx;

    if( (boolean)TRUE != DoIP_GidInSync )
    {
        for( localAddrIdx = DOIP_ZERO; localAddrIdx < DOIP_LOCAL_ADDR_TOTAL; localAddrIdx++ )
        {
            /* [SWS_DoIP_00085] */
            if( DoIP_LocalAddrIdx2IpAddrReqState[localAddrIdx] == DOIP_IP_ADDR_REQ_STATE_ASSIGNED )
            {
#if ( DOIP_VIN_GID_MASTER == STD_ON )
#ifdef DoIP_CALL_TRIGGER_GID_SYNC 
                if( (Std_ReturnType)E_OK == DoIP_CALL_TRIGGER_GID_SYNC() )
                {
                    DoIP_GidInSync = TRUE;
                }
#endif
#endif
                break;
            }
        }
    }
}

/*
*******************************************************************************
* Function Name: DoIP_HandleAuthConf
*
* Explanation: Handle gid authentication and confirmation.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleAuthConf(PduIdType id)
{
    uint8 offsetReq = DOIP_ZERO;
    uint8 offsetRes = DOIP_ZERO;
    uint8 routActIdx = DoIP_RoutActivHandler[id].routActIdx;
    boolean authentified = FALSE;
    boolean confirmed = FALSE;
    Std_ReturnType retVal = DOIP_E_OK;
    uint16 testerAddr = DoIP_RoutActivHandler[id].testerAddr;
    PduIdType connection = DoIP_RoutActivHandler[id].tcpCon;
    uint32 testerIdx = DoIP_RoutActivHandler[id].testerIdx;
    DoIP_RoutActivStateType nextState = DOIP_ROUT_ACTIV_STATE_NONE;
    DoIP_RoutActivStateType lastState = DOIP_ROUT_ACTIV_STATE_NONE;
    for(int testerID = DOIP_ZERO;testerID < DOIP_TESTER_TOTAL;testerID++)
    {
        if( (DOIP_INV_PDU_ID != connection) && (DOIP_ZERO == DoIP_RoutActivHandler[id].aliveCheckCnt[testerID]) )
        {
            /* Routing activation but no alive check is pending. */
            lastState = DoIP_TcpCon2ActivMgt[connection].activState;
            /* Call authentication callback. */
            if( DOIP_ROUT_ACTIV_STATE_AUTH_PENDING == lastState )
            {
                /* [SWS_DoIP_00109] */
                if( NULL_PTR != DoIP_RoutingActivations[routActIdx].authFuncPtr )
                {
                    retVal = DoIP_RoutingActivations[routActIdx].authFuncPtr
                                  (&authentified, DoIP_RoutActivHandler[id].oemSpecReq, DoIP_RoutActivHandler[id].oemSpecRes);
                }
                if( (Std_ReturnType)DOIP_E_NOT_OK == retVal )
                {
                    /* [SWS_DoIP_00111] */
                    /* Authentication failed. */
                    DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;
    
                    (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                           DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);
                }
                else if( DOIP_E_PENDING == retVal )
                {
                    /* [SWS_DoIP_00110] */
                    /* Authentication pending */
                    /* Nothing to do here (rety in next MainFunction). */
                }
                else
                {
                    /* [SWS_DoIP_00161] */
                    /* Authentication successful (callback return value). */
                    if( (boolean)TRUE != authentified )
                    {
                        /* [SWS_DoIP_00111] */
                        /* Authentication failed. */
                        DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;
    
                        (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                               DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);
                    }
                    else
                    {
                        /* Authentication successful. */
                        nextState = DOIP_ROUT_ACTIV_STATE_ACTIVATED;
                    }
                }
            }
    
            /* Call confirmation callback. */
            if( (DOIP_ROUT_ACTIV_STATE_CONF_PENDING == lastState) ||
                ((DOIP_ROUT_ACTIV_STATE_ACTIVATED == nextState) && (NULL_PTR != DoIP_RoutingActivations[routActIdx].confFuncPtr)) )
            {
                if( DOIP_ZERO < DoIP_RoutingActivations[routActIdx].confReqLength )
                {
                    offsetReq = (uint8)(DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE - DoIP_RoutingActivations[routActIdx].confReqLength);
                }
                if( DOIP_ZERO < DoIP_RoutingActivations[routActIdx].confResLength )
                {
                    offsetRes = (uint8)(DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE - DoIP_RoutingActivations[routActIdx].confResLength);
                }
                /* [SWS_DoIP_00112] */
                retVal = DoIP_RoutingActivations[routActIdx].confFuncPtr
                             (&confirmed, &DoIP_RoutActivHandler[id].oemSpecReq[offsetReq], &DoIP_RoutActivHandler[id].oemSpecRes[offsetRes]);
    
                if( (Std_ReturnType)E_NOT_OK == retVal )
                {
                    /* [SWS_DoIP_00274] */
                    /* Confirmation failed. */
                    DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;
    
                    (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                           DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED, testerIdx, NULL_PTR, TRUE);
                }
                else if( DOIP_E_PENDING == retVal )
                {
                    /* Confirmation pending. */
                    if( DOIP_ROUT_ACTIV_STATE_ACTIVATED == nextState )
                    {
                        /* Authentication performed in same context - first pending returned for confirmation. */
                        DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_CONF_PENDING;
    
                        /* routing activation response has to be sent. */
                        (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                               DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REQUIRED, testerIdx, NULL_PTR, FALSE);
                    }
                }
                else
                {
                    /* Confirmation successful (callback return value). */
                    if( (boolean)TRUE != confirmed )
                    {
                        /* Confirmation failed. */
                        DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_NONE;
    
                        (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                               DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED, testerIdx, NULL_PTR, TRUE);
                    }
                    else
                    {
                        /* Confirmation successful. */
                        nextState = DOIP_ROUT_ACTIV_STATE_ACTIVATED;
                    }
                }
            }
    
            /* Routing activated. */
            if( DOIP_ROUT_ACTIV_STATE_ACTIVATED == nextState )
            {
                /* Routing activation successful. */
                /* Set mapping for connection and channels. */
                DoIP_ActivateConnectionAtChannel(routActIdx, connection, testerAddr);
    
                DoIP_TcpCon2ActivMgt[connection].activState = DOIP_ROUT_ACTIV_STATE_ACTIVATED;
    
                if( DOIP_ROUT_ACTIV_STATE_CONF_PENDING != lastState )
                {
                    /* [SWS_DoIP_00114] */
                    /* Not activated after confirmation was pending (i.e. response was already sent). */
                    /* Reset inactivity counter. */
                    DoIP_TcpCon2InactivCnt[connection] = DOIP_ZERO;
    
                    /* Send routing activation response. */
                    (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, testerAddr,
                                           DOIP_ROUT_ACTIV_RES_CODE_SUCCESS, testerIdx, NULL_PTR, FALSE);
                }
                else
                {
                    /* Activated after confirmation was pending (i.e. response was already sent). */
                    /* Release routing activation handler. */
                    DoIP_RoutActivHandler[id].tcpCon = DOIP_INV_PDU_ID;
                }
            }
        }
    }
    
}

/*
*******************************************************************************
* Function Name: DoIP_HandleCloseSocketInUdpTxList
*
* Explanation: Handle close socket in Udp Tx list.
*
* param: udpTxListIdx: udp Tx list idex.
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleCloseSocketInUdpTxList(uint16 udpTxListIdx)
{
    boolean otherEntryFound = FALSE;
    PduIdType connection = DoIP_UdpTxMgtList[udpTxListIdx].udpCon;
    PduIdType tmpListIdx = DOIP_UDP_TX_MGT_LIST_SIZE;

    /* Check if socket connection shall be closed. */
    if( (DOIP_INV_PDU_ID != connection) && ((uint8)TRUE == DoIP_Con2SoConClosing[connection]) )
    {
        /* Socket connection shall be closed. */
        /* Check if other entries for socket connection exists. */
        while( DOIP_ZERO < tmpListIdx )
        {
            tmpListIdx--;
            if( (udpTxListIdx != tmpListIdx) &&
                (DoIP_UdpTxMgtList[udpTxListIdx].udpCon == DoIP_UdpTxMgtList[tmpListIdx].udpCon) )
            {
                /* Found other entry. */
                /* Do not close socket connection. */
                otherEntryFound = TRUE;
                break;
            }
        }

        if( (boolean)FALSE == otherEntryFound )
        {
            /* No other entry found. */
            /* Close socket connection. */
            //DoIP_CloseSoCon(connection);
             DoIP_CloseSoConUDP(connection);
        }
    }
}

/*
*******************************************************************************
* Function Name: DoIP_HandleUdpTxList
*
* Explanation: Handle Udp Tx list.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleUdpTxList(void)
{
    boolean releaseListEntry;
    PduIdType connection;
    PduIdType listIdx = DOIP_UDP_TX_MGT_LIST_SIZE;

    while( DOIP_ZERO < listIdx )
    {
        listIdx--;
        connection = DoIP_UdpTxMgtList[listIdx].udpCon;
        if( DOIP_INV_PDU_ID != connection )
        {
            /* Pending UDP message. */
            releaseListEntry = FALSE;
            /* Socket connection is online. */
            if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConUDPState[connection] )
            {
                if( DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT == DoIP_UdpTxMgtList[listIdx].hdrType )
                {
                    /* Vehicle Announcement/Vehicle Identification Response. [SWS_DoIP_00071]*/
                    if( DOIP_ZERO < DoIP_UdpTxMgtList[listIdx].param1 )
                    {
                        DoIP_UdpTxMgtList[listIdx].param1--;
                    }
                    if( DOIP_ZERO == DoIP_UdpTxMgtList[listIdx].param1 )
                    {
                        /* Try to send message. */
                        while(DOIP_ZERO < DoIP_UdpTxMgtList[listIdx].param2 )
                        {
                            if( (Std_ReturnType)E_OK != DoIP_UdpSingleTransmit(connection, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_UNUSED_PARAM) )
                            {
                                /* Transmission not successful. */
                                /* Increment counter again to rety in next MainFunction. */
                                DoIP_UdpTxMgtList[listIdx].param1++;
                                /* decrement retry attempt counter. */
                                if( DOIP_ZERO < DoIP_UdpTxMgtList[listIdx].retryAttempt )
                                {
                                    DoIP_UdpTxMgtList[listIdx].retryAttempt--;
                                }
                                /* Too many retries. */
                                if( DOIP_ZERO == DoIP_UdpTxMgtList[listIdx].retryAttempt )
                                {
                                    /* Release list entry to avoid that ECU does not answer other requests anymore. */
                                    DoIP_UdpTxMgtList[listIdx].udpCon = DOIP_INV_PDU_ID;
                                }
                            }
                            else
                            {
                                /* Transmission successful. */
                                if( DOIP_ZERO < DoIP_UdpTxMgtList[listIdx].param2 )
                                {
                                    DoIP_UdpTxMgtList[listIdx].param2--;
                                }
                                if( DoIP_UdpTxMgtList[listIdx].param2 > DOIP_ZERO )
                                {
                                    /* Further Vehicle Announcement messages are pending. */
                                    /* Reload timer. */
                                    /* SWS_DoIP_00071 */
                                    DoIP_UdpTxMgtList[listIdx].param1 = DOIP_ANNOUNCE_INTERVAL;
                                    while(DoIP_UdpTxMgtList[listIdx].param1 * 1000 >0)
                                    {
                                        DoIP_UdpTxMgtList[listIdx].param1--;
                                    }
                                }
                                else
                                {
                                    /* All pending messages for this entry are sent. */
                                    if( DOIP_CONNECTION_TCP_UDP_TOTAL > connection )
                                    {
                                        DoIP_HandleCloseSocketInUdpTxList(listIdx);
                                    }
                                    /* Release list entry. */
                                    //DoIP_UdpTxMgtList[listIdx].udpCon = DOIP_INV_PDU_ID;
                                }
                            }
                        }
                        if(listIdx != DOIP_ZERO)
                        {
                            DoIP_UdpTxMgtList[listIdx].udpCon = DOIP_INV_PDU_ID;
                        }
                    }
                }
                else
                {
                    /* Entity State Status Response, Diagnostic Power Mode Response or Generic Negative Acknowledgement. */
                    /* Try to send message. */
                    if( (Std_ReturnType)E_OK != DoIP_UdpSingleTransmit(connection, DoIP_UdpTxMgtList[listIdx].hdrType, DoIP_UdpTxMgtList[listIdx].param2) )
                    {
                        /* Message not sent. */
                        /* Decrement retry attempt counter. */
                        if( DOIP_ZERO < DoIP_UdpTxMgtList[listIdx].retryAttempt )
                        {
                            DoIP_UdpTxMgtList[listIdx].retryAttempt--;
                        }
                        if( DOIP_ZERO == DoIP_UdpTxMgtList[listIdx].retryAttempt )
                        {
                            /* Too many retries. */
                            releaseListEntry = TRUE;
                        }
                    }
                    else
                    {
                        /* mMessage sent. */
                        releaseListEntry = TRUE;
                    }
                }
            }
            else
            {
                 /* Socket connection is not online anymore. */
                 releaseListEntry = TRUE;
            }
            if( (boolean)TRUE == releaseListEntry )
            {
                 DoIP_HandleCloseSocketInUdpTxList(listIdx);
                 /* Release list entry. */
                 DoIP_UdpTxMgtList[listIdx].udpCon = DOIP_INV_PDU_ID;
            }
        }
    }
}

void PduR_DoIPTpRxIndication(PduIdType PduID,Std_ReturnType revl)
{
    if(revl == E_OK)
    {
      
       
    }
        //todo
}
BufReq_ReturnType PduR_DoIPTpCopyRxData(   
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    //todo
    *bufferSizePtr = info->SduLength;
    retVal = BUFREQ_OK;
    return retVal;
}
BufReq_ReturnType PduR_DoIPTpStartOfReception(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)info,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA)bufferSizePtr)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    //todo
    retVal = BUFREQ_OK;
    return retVal;
}
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TerminateCurrTcpRx
(
    PduIdType connection
)
{
    /* Within the specified time, the data expected to be copied from the SoAd module is not received,
       and the message reception ends. */
    /* 1. During the process of copying diagnostic messages to PduR*/
    if( DOIP_INV_PDU_ID != DoIP_TcpCon2RxChannelActive[connection] )
    {
        Dcm_TpRxIndication(0, E_NOT_OK);
        DoIP_TcpCon2RxChannelActive[connection] = DOIP_INV_PDU_ID;
    }
    /* 2. Clear all flags */
    DoIP_TcpFinishTransmit(connection);
    DoIP_TcpCon2LastRxBufSize[connection] = DOIP_ZERO;
    DoIP_TcpCon2RxMsgOffset[connection] = DOIP_ZERO;
    DoIP_TcpCon2SkipRxMsg[connection] = FALSE;
    /* Modified 2022-02-12 */
#if( DOIP_NACK_APPEND_REQ == STD_ON )
    if( DOIP_INV_TESTER_IDX != DoIP_TcpCon2ActivMgt[connection].testerIdx )
    {
        DoIP_Tester2DiagNAckOffset[DoIP_TcpCon2ActivMgt[connection].testerIdx] = DOIP_ZERO;
    }
#endif /* ( DOIP_NACK_APPEND_REQ == STD_ON ) */
#if( DOIP_LOCAL_DEBUG == STD_ON )
    DoIP_DebugRxCnt[connection].rxTimeout++;
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_Tcp_HandleRxMsgTimeouts
*
* Explanation: Handle Tcp Rx Msg Timeouts.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Tcp_HandleRxMsgTimeouts(void)
{
    PduIdType connection = DOIP_CONNECTION_TOTAL;

    while( DOIP_ZERO < connection )
    {
        connection--;
        if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[connection] )
        {
            /* Initial inactivity timeout. */
            if( DoIP_TcpCon2RxMsgWaitCnt[connection] > DOIP_ZERO )
            {
                DoIP_TcpCon2RxMsgWaitCnt[connection]--;
                if( DOIP_ZERO == DoIP_TcpCon2RxMsgWaitCnt[connection] )
                {
                    /* Terminate this reception. */
                    DoIP_TerminateCurrTcpRx(connection);
                }
            }
        }
    }
}


/*
*******************************************************************************
* Function Name: DoIP_TcpRx_HandleInactivityTimeouts
*
* Explanation: Handle Tcp Rx Inactivity list.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpRx_HandleInactivityTimeouts(void)
{
    PduIdType connection = DOIP_CONNECTION_TOTAL;

    while( DOIP_ZERO < connection )
    {
        connection--;

        if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[connection] )
        {
            /* No routing active. [SWS_DoIP_00144] */
            if( DOIP_ROUT_ACTIV_STATE_ACTIVATED != DoIP_TcpCon2ActivMgt[connection].activState )
            {
                /* Initial inactivity timeout. */
                if( DOIP_INIT_INACTIV_WAIT == DoIP_TcpCon2InactivCnt[connection] )
                {
                    /* Close socket. */
                    DoIP_TcpCon2InactivCnt[connection] = DOIP_ZERO;
                    DoIP_CloseSoCon(connection);
                    ActiveConfig_Init(connection);
                }
            }
            else/* Routing activated. */
            {
                /* General inactivity timeout. [SWS_DoIP_00146] */
                if( DOIP_GEN_INACTIV_WAIT == DoIP_TcpCon2InactivCnt[connection] )
                {
                    /* Close socket. */
                    DoIP_TcpCon2InactivCnt[connection] = DOIP_ZERO;
                    DoIP_CloseSoCon(connection);
                    ActiveConfig_Init(connection);
                }
            }
            DoIP_TcpCon2InactivCnt[connection]++;   /* [SWS_DoIP_00143] [SWS_DoIP_00142] */
        }
    }
}


/*
*******************************************************************************
* Function Name: DoIP_TcpRx_HandleAliveCheckTimeouts
*
* Explanation: Handle timeout.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_TcpRx_HandleAliveCheckTimeouts
(
    PduIdType id
)
{
    PduIdType listIdx = DOIP_MAX_CONS_PER_LOC_ADDR;
    PduIdType connection = DoIP_RoutActivHandler[id].tcpCon;
    PduIdType tmpSoAdRxPduId = DOIP_INV_PDU_ID;
    int num = DOIP_ZERO;
    if( DOIP_INV_PDU_ID != connection )
    {
        /* Alive check. */
        //for(int num = DOIP_ZERO;num <= DOIP_ZERO;num++)
        {
            if( DOIP_ZERO < DoIP_RoutActivHandler[id].aliveCheckCnt[num] )
            {
                /* Handle alive check. */
                DoIP_RoutActivHandler[id].aliveCheckCnt[num]--;
                fflush(stdout);
                /* AliveCheck timer is time out. */
                if( DOIP_ZERO == DoIP_RoutActivHandler[id].aliveCheckCnt[num] )
                {
                    /* Clean up all timed-out socket connections. */
                    while( DOIP_ZERO < listIdx )
                    {
                        listIdx--;
                        if( DOIP_ZERO == DoIP_RoutActivHandler[id].aliveCheckElemNum )
                        {
                            /* All sockets closed or Alive Check Response received. */
                            break;
                        }
                        if( DOIP_INV_PDU_ID != DoIP_RoutActivHandler[id].aliveCheckList[listIdx] )
                        {
                            /* Alive check timeout -> close socket connection. [SWS_DoIP_00140]*/
                            DoIP_GetConnectionOfTesterAddr(DoIP_RoutActivHandler[id].testerAddr, &tmpSoAdRxPduId);
                 
                            //tmpSoAdRxPduId = DoIP_RoutActivHandler[id].aliveCheckList[listIdx];
    
                            DoIP_CloseSoCon(tmpSoAdRxPduId);
                            DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].testerIdx = DOIP_INV_TESTER_IDX;
                            DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].testerAddr = DOIP_ADDR_ANY;
                            DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].routActIdx = DOIP_INV_ROUT_ACT_IDX;
                            DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].activState = DOIP_ROUT_ACTIV_STATE_NONE;
    
                            DoIP_RoutActivHandler[id].aliveCheckList[listIdx] = DOIP_INV_PDU_ID;
                            DoIP_RoutActivHandler[id].aliveCheckElemNum--;
    
    
                            //return;
    
                            // tmpSoAdRxPduId = DoIP_RoutActivHandler[id].aliveCheckList[listIdx];
                            // DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].testerIdx = DOIP_INV_TESTER_IDX;
                            // DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].testerAddr = DOIP_ADDR_ANY;
                            // DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].routActIdx = DOIP_INV_ROUT_ACT_IDX;
                            // DoIP_TcpCon2ActivMgt[tmpSoAdRxPduId].activState = DOIP_ROUT_ACTIV_STATE_NONE;
    
                            // DoIP_RoutActivHandler[id].aliveCheckList[listIdx] = DOIP_INV_PDU_ID;
                            // DoIP_RoutActivHandler[id].aliveCheckElemNum--;
                        }
                    }
                    /* Socket connection with routing activation request is still online. */
                    if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[connection] )
                    {
                        /* Check if routing is (still) active on other socket. */
                        DoIP_GetConnectionOfTesterAddr(DoIP_RoutActivHandler[id].testerAddr, &tmpSoAdRxPduId);
    
                        if ( DOIP_INV_PDU_ID != tmpSoAdRxPduId )
                        {
                            /* Deny routing activation for active address on new socket connection. */
                            (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, DoIP_RoutActivHandler[id].testerAddr,
                                                   DOIP_ROUT_ACTIV_RES_CODE_ALREADY_ACTIV, 0U, NULL_PTR, TRUE);
                        }
                        else
                        {
                            /* Routing activation of new address. */
                            if ( DOIP_ZERO == DoIP_GetAvailableSockNum(connection,DoIP_Con2LocalAddrIdx[connection]) )
                            {
                                /* All sockets but max one are in use - deny RoutingActivation request. */
                                (void)DoIP_TcpTransmit(connection, DOIP_HDR_TYPE_ROUT_ACTIV_ACK, DoIP_RoutActivHandler[id].testerAddr,
                                                       DOIP_ROUT_ACTIV_RES_CODE_SOCKETS_IN_USE, DOIP_ZERO, NULL_PTR, TRUE);
                            }
                            else
                            {
                                /* Continue with received routing activation request. */
                                DoIP_PerformAuthConfAndActivateRouting(id);
                            }
                        }
                    }
                }
            }
    
        }
     }
}

/*
*******************************************************************************
* Function Name: DoIP_HandleTcpTxQueue
*
* Explanation: Handle Tcp Tx queue.
*
* param: None
*
* retval: None
*******************************************************************************
*/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_HandleTcpTxQueue(void)
{
    uint32 queLvl;
    PduIdType connection = DOIP_CONNECTION_TOTAL;
    //printf("DoIP_HandleTcpTxQueue(void) \n");
    while( DOIP_ZERO < connection )
    {
        connection--;
        /* Socket connection is online. */
        //printf("DoIP_HandleTcpTxQueue(void): DoIP_Con2SoConState[connection] = %d\n",DoIP_Con2SoConState[connection]);
        if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[connection] )
        {
            queLvl = DOIP_TCP_TX_QUEUE_GET_LEVEL(connection);
            //printf("DoIP_HandleTcpTxQueue(void): queLvl = %d\n",queLvl);
            if( DOIP_ZERO < queLvl )
            {
                DoIP_TcpTxQueueSend(connection);
            }
        }
    }
}

void ActiveConfig_Init
(
    PduIdType connnection
)
{
    DoIP_TcpCon2ActivMgt[connnection].testerAddr    = DOIP_ADDR_ANY;
    DoIP_TcpCon2ActivMgt[connnection].testerIdx     = DOIP_INV_TESTER_IDX;
    DoIP_TcpCon2ActivMgt[connnection].routActIdx    = DOIP_INV_ROUT_ACT_IDX;
    DoIP_TcpCon2ActivMgt[connnection].activState    = DOIP_ROUT_ACTIV_STATE_NONE;

    uint8 conIndx = DOIP_MAX_CONS_PER_LOC_ADDR;
    while( DOIP_ZERO < conIndx )
    {
        conIndx--;
        DoIP_RoutActivHandler[connnection].aliveCheckList[conIndx] = DOIP_INV_PDU_ID;
    }
    DoIP_RoutActivHandler[connnection].oemSpecReq[DOIP_ZERO] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecReq[DOIP_ONE] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecReq[DOIP_TWO] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecReq[DOIP_THREE] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecRes[DOIP_ZERO] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecRes[DOIP_ONE] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecRes[DOIP_TWO] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecRes[DOIP_THREE] = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].oemSpecUsed = FALSE;
    DoIP_RoutActivHandler[connnection].routActIdx = DOIP_INV_ROUT_ACT_IDX;
    DoIP_RoutActivHandler[connnection].testerAddr = DOIP_ADDR_ANY;
    DoIP_RoutActivHandler[connnection].testerIdx = DOIP_INV_ADDR_IDX;
    for(int conx = DOIP_ZERO;conx < DOIP_TESTER_TOTAL;conx++)
    {
        DoIP_RoutActivHandler[connnection].aliveCheckCnt[conx] = DOIP_ZERO;
    }
    DoIP_RoutActivHandler[connnection].aliveCheckElemNum = DOIP_ZERO;
    DoIP_RoutActivHandler[connnection].tcpCon = DOIP_INV_PDU_ID;

    DoIP_TcpCon2RxMsgOffset[connnection] = DOIP_ZERO;
}
/*
*******************************************************************************
* Function Name: DoIP_TpTransmit
* Explanation: This service is called to request the transfer data from the
*              PduRouter to the SoAd. It is used to indicate the transmission
*              which will be performed in the DoIP_Mainfunction.
* param: PduIdType DoIPPduRTxId: DoIP unique identifier of the PDU to be
*                                transmitted by the PduR.
*        PduInfoType DoIPPduRTxInfoPtr: Tx Pdu information structure which
*                                       contains the length of the DoIPTxMessage.
*
* retval: E_OK: The request has been accepted.
*         E_NOT_OK: The request has not been accepted, e.g. parameter check has
*                   failed or no resources are available for transmission.
*******************************************************************************
*/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpTransmit
(
   // PduIdType connection,
    PduIdType DoIPPduRTxId,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) DoIPPduRTxInfoPtr
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    uint8 retVal = E_NOT_OK;  /* [SWS_DoIP_00226] */
    PduIdType connection;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_INITSTATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( NULL_PTR == DoIPPduRTxInfoPtr )
    {
        printf("NULL_PTR == DoIPPduRTxInfoPtr ");
        errorId = DOIP_E_PARAM_POINTER;
    }
    else if( (DOIP_CHANNELS_TOTAL <= DoIPPduRTxId)
            || (DOIP_TPPDU != DoIP_Channel2ApiType[DoIPPduRTxId])
            || (DOIP_INV_PDU_ID == DoIP_Channel2PduRTxConfPduId[DoIPPduRTxId]) )
    {
        printf("OIP_CHANNELS_TOTAL <= DoIPPduRTxId\n");
        printf("DoIP_Channel2ApiType[0] = %d\n",DoIP_Channel2ApiType[0]);
        printf("DoIP_Channel2PduRTxConfPduId[0] = %d\n",DoIP_Channel2PduRTxConfPduId[0]);
            errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else if( DOIP_ZERO == DoIPPduRTxInfoPtr->SduLength )
    {
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
#endif
    {
        /* Get tester socket connection. */
        // connection = DoIP_Con2SoConId[0];
        printf("DoIP_TpTransmit\n");
        //printf("DoIPPduRTxInfoPtr->SduLength = %d \n",DoIPPduRTxInfoPtr->SduLength);
        //printf("DoIPPduRTxInfoPtr->SduLength = %x,%x \n",DoIPPduRTxInfoPtr->SduDataPtr[0],DoIPPduRTxInfoPtr->SduDataPtr[1]);
        //connection = DoIP_Channel2TcpCon[DoIPPduRTxId];
        connection = 0;
        /* Check whether TP session is active or requested for this channel. */
        if( DOIP_ZERO == DoIP_Channel2TxMsgLen[DoIPPduRTxId] )
        {
            /* Check whether tester is connected to channel. */
            if( DOIP_INV_PDU_ID != connectionPDUID )
            {
                /* Tester is connected. */
                DoIP_Channel2TxMsgLen[DoIPPduRTxId] = DoIPPduRTxInfoPtr->SduLength;
                retVal = DoIP_TcpTransmit(connectionPDUID, DOIP_HDR_TYPE_DIAG_REQ,
                                          (uint16)DoIPPduRTxId, DOIP_ZERO, DoIPPduRTxInfoPtr->SduLength,
                                          DoIPPduRTxInfoPtr->SduDataPtr, FALSE);
            }
            //02 FD 80 01 00 00 00 06 0e 01 10 01 10 01
            /* Transmit request is not successful. */
            if( (uint8)DOIP_E_OK != retVal )
            {
                /* Reset channel information. */
                DoIP_Channel2TxMsgLen[DoIPPduRTxId] = DOIP_ZERO;
            }
        }
    }

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_TP_TRANSMIT, errorId);  /* Det report. */
#endif

    return retVal;
}
Std_ReturnType SoAd_TpCancelTransmit(PduIdType DoIPPduRTxId)
{
    Std_ReturnType revl = E_NOT_OK;
    //todo
    return revl;
}
/*
*******************************************************************************
* Function Name: DoIP_TpCancelTransmit
*
* Explanation: This service primitive is used to cancel the transfer of pending
*              DoIPPduRTxIds.The connection is identified by DoIPPduRTxId. When
*              the function returns, no transmission is in progress anymore with
*              the given DoIPPduRTxId identifier.
*
* param: PduIdType DoIPPduRTxId: DoIP unique identifier of the PDU to be canceled
*                                by the PduR.
*
* retval: E_OK: Transmit cancellation request of the specified DoIPPduRTxId is
*               accepted.
*         E_NOT_OK: The transmit cancellation request of the DoIPPduRTxId has
*                   been rejected.
*******************************************************************************
*/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpCancelTransmit(PduIdType DoIPPduRTxId)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    uint8 retVal = E_NOT_OK;
    PduIdType connection;

    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( (DOIP_CHANNELS_TOTAL < DoIPPduRTxId) ||
             (DOIP_TPPDU != DoIP_Channel2ApiType[DoIPPduRTxId]) )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else
    {
        connection = DoIP_Channel2TcpCon[DoIPPduRTxId];
        /* Channel to connection mapping is available. */
        if( DOIP_INV_PDU_ID != connection )
        {
            /* TP session of the corresponding socket connection is active. */
            if( (boolean)TRUE == DoIP_TcpCon2TxTpSessionActive[connection] )
            {
                if( DOIP_ZERO != DoIP_Channel2TxMsgLen[DoIPPduRTxId] )
                {
                    /* Transmission of PDU is active. */
                    if( (Std_ReturnType)DOIP_E_OK == SoAd_TpCancelTransmit(DoIP_Con2SoAdTxPduId[connection]) )
                    {
                       /* Cancellation request successful. */
                       DoIP_TcpCon2TxTpCancelRequested[connection] = TRUE;
                       retVal = E_OK;
                    }
                }
            }
        }
    }

    DoIP_Det_ErrorReport(DOIP_API_ID_TP_CANCEL_TRANSMIT, errorId);

    return retVal;
}
/*
*******************************************************************************
* Function Name: DoIP_TpCancelReceive
*
* Explanation: By calling this API with the corresponding DoIPPduRRxId the
*              currently ongoing data reception is terminated immediately. When
*              the function returns, no reception is in progress anymore with
*              the given DoIPPduRRxId identifier.
*
* param: PduIdType DoIPPduRRxId: DoIP unique identifier of the PDU for which
*                                reception shall be canceled by the PduR.
*
* retval: E_OK: Reception was canceled successfully.
*         E_NOT_OK: Reception was not canceled.
*******************************************************************************
*/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpCancelReceive(PduIdType DoIPPduRRxId)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8 errorId = DOIP_E_NO_ERROR;
    PduIdType channel = DOIP_CHANNELS_TOTAL;
    PduIdType connection;

    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( (DOIP_CHANNELS_TOTAL < DoIPPduRRxId) ||
             (DOIP_TPPDU != DoIP_Channel2ApiType[DoIPPduRRxId]) )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else
    {
        /* Search for affected channel. */
        while( DOIP_ZERO < channel )
        {
            channel--;

                /* Found affected channel. */
                connection = DoIP_Channel2TcpCon[channel];

                if( DOIP_INV_PDU_ID != connection )
                {
                    /* Channel to connection mapping is available. */
                    if( DOIP_INV_PDU_ID != DoIP_TcpCon2RxChannelActive[connection] )
                    {
                        /* TP session of the corresponding socket connection is active */
                       // if( (Std_ReturnType)E_OK == SoAd_TpCancelReceive(DoIP_Con2SoAdRxCancelPduId[connection]) )
                        {
                            /* Cancellation request successful. */
                            DoIP_TcpCon2RxTpCancelRequested[connection] = TRUE;
                            retVal = E_OK;
                        }
                    }
                }
                break;
            }
    }

    DoIP_Det_ErrorReport(DOIP_API_ID_TP_CANCEL_RECEIVE, errorId);

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_IfTransmit
*
* Explanation: By calling this API with the corresponding DoIPPduRRxId the
*              currently ongoing data reception is terminated immediately. When
*              the function returns, no reception is in progress anymore with
*              the given DoIPPduRRxId identifier.
*
* param: PduIdType id: Identification of the I-PDU.
*        const PduInfoType* info: Length and pointer to the buffer of the I-PDU.
*
* retval: E_OK: Request is accepted by the destination module.
*         E_NOT_OK: Request is not accepted by the destination module.
*******************************************************************************
*/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_IfTransmit
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    Std_ReturnType retVal = E_NOT_OK;
    PduIdType connection;
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( (DOIP_CHANNELS_TOTAL <= id) || (DOIP_IFPDU != DoIP_Channel2ApiType[id]) )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else if( (NULL_PTR == info->SduDataPtr) || (info == NULL_PTR) )
    {
        errorId = DOIP_E_PARAM_POINTER;
    }
    else if( (DOIP_ZERO != info->SduLength) ||
             (DoIP_Channel2IfTxBuf[id].maxBufLen <= info->SduLength) )
    {
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
#endif
    {
        /* Check if previous transmission is pending. */
        if( DOIP_ZERO == DoIP_Channel2TxMsgLen[id] )
        {
            /* Get tester socket connection. */
            connection = DoIP_Channel2TcpCon[id];

            /* No transmission pending. */
            if( DOIP_INV_PDU_ID != connection )
            {
                /* Tester is connected. */
                 DoIP_Channel2TxMsgLen[id] = info->SduLength;

                 retVal = DoIP_TcpTransmit(connection,
                                           DOIP_HDR_TYPE_DIAG_REQ,
                                           (uint16)id,
                                           DOIP_ZERO,
                                           info->SduLength,
                                           info->SduDataPtr,
                                           FALSE);
            }
        }
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_IF_TRANSMIT, errorId);
#endif
    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_IfCancelTransmit
*
* Explanation: Requests cancellation of an ongoing transmission of an I-PDU in a
*              lower layer communication interface module.
*
* param: PduIdType id: Identification of the I-PDU to be cancelled.
*
* retval: E_OK: Cancellation was executed successfully by the destination module.
*         E_NOT_OK: Cancellation was rejected by the destination module.
*******************************************************************************
*/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_IfCancelTransmit(PduIdType id)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    Std_ReturnType retVal = E_NOT_OK;
    PduIdType connection;

    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( (DOIP_CHANNELS_TOTAL <= id) ||
             (DOIP_IFPDU != DoIP_Channel2ApiType[id]) )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else
    {
        connection = DoIP_Channel2TcpCon[id];
        if( DOIP_INV_PDU_ID != connection )
        {
            /* Channel to connection mapping is available. */
            if( (boolean)TRUE == DoIP_TcpCon2TxTpSessionActive[connection] )
            {
                /* TP session of the corresponding socket connection is active. */
                if( DOIP_ZERO != DoIP_Channel2TxMsgLen[id] )
                {
                    /* Transmission of PDU is active */
                    if( (Std_ReturnType)E_OK == SoAd_TpCancelTransmit(DoIP_Con2SoAdTxPduId[connection]) )
                    {
                        /* Cancellation request successful. */
                        DoIP_TcpCon2TxTpCancelRequested[connection] = TRUE;
                        retVal = E_OK;
                    }
                }
            }
        }
    }

    DoIP_Det_ErrorReport(DOIP_API_ID_IF_CANCEL_TRANSMIT, errorId);

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_Init
*
* Explanation: This service initializes all global variables of the DoIP module.
*              After return of this service the DoIP module is operational.
*
* param: const DoIP_ConfigType* DoIPConfigPtr: Pointer to the configuration data
*                                              of the DoIP module.
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00026] */
void DoIP_Init
(
    const DoIP_ConfigType* DoIPConfigPtr
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    uint8 conIndx;
    uint8 id;
    uint16 idxTcpTx;
    SoAd_SoConIdType soConId = SOAD_INV_SO_CON_ID;

    DOIP_DUMMY_STATEMENT(DoIPConfigPtr);

    if( DOIP_INITSTATE_INIT == DoIP_State )  /* Check init state. */
    {
        errorId = DOIP_E_INIT_FAILED;
    }
    else
    {
        /* Initialize TCP socket info. */
        conIndx = DOIP_ZERO;
        (void)DoIP_GetSoConIdByConId(conIndx, &soConId);
        sockCon = soConId;
        soConId = SOAD_INV_SO_CON_ID;
        while( conIndx < DOIP_CONNECTION_TOTAL )
        {
            if( TRUE == DoIPRequestAddressAssignment[conIndx] )
            {
                DoIP_LocalAddrIdx2AssignmentType[DoIP_Con2LocalAddrIdx[conIndx]] = (uint8)DOIP_IPADDR_ASSIGN_TRIGGER_ENABLE;
            }
            else
            {
                DoIP_LocalAddrIdx2AssignmentType[DoIP_Con2LocalAddrIdx[conIndx]] = (uint8)DOIP_IPADDR_ASSIGN_TRIGGER_DISABLE;
            }
            DoIP_Con2IpAddrState[conIndx]  = (uint8)SOAD_IPADDR_STATE_UNASSIGNED;
            // (void)DoIP_GetSoConIdByConId(conIndx, &soConId);
            DoIP_Con2SoConId[conIndx]      = soConId;
            // printf("DoIP_init(void)    DoIP_Con2SoConId[conIndx] = %d\n",DoIP_Con2SoConId[conIndx]);
            DoIP_Con2SoConState[conIndx]   = (uint8)SOAD_SOCON_OFFLINE;
            DoIP_Con2SoConClosing[conIndx] = (uint8)FALSE;
            conIndx++;
        }
       
        conIndx = DOIP_CONNECTION_TOTAL;
        while( DOIP_ZERO < conIndx )
        {
            idxTcpTx = DOIP_TCP_TX_MGT_QUEUE_SIZE;

            conIndx--;
            DoIP_TcpCon2ActivMgt[conIndx].testerAddr    = DOIP_ADDR_ANY;
            DoIP_TcpCon2ActivMgt[conIndx].testerIdx     = DOIP_INV_TESTER_IDX;
            DoIP_TcpCon2ActivMgt[conIndx].routActIdx    = DOIP_INV_ROUT_ACT_IDX;
            DoIP_TcpCon2ActivMgt[conIndx].activState    = DOIP_ROUT_ACTIV_STATE_NONE;
            DoIP_TcpCon2InactivCnt[conIndx]             = DOIP_ZERO;
            DoIP_TcpCon2RxMsgWaitCnt[conIndx]           = DOIP_ZERO;
            DoIP_TcpCon2SkipRxMsg[conIndx]              = FALSE;
            DoIP_TcpCon2RxMsgOffset[conIndx]            = DOIP_ZERO;
            DoIP_TcpCon2TxBytesCopied[conIndx]          = DOIP_ZERO;
            DoIP_TcpCon2LastRxBufSize[conIndx]          = DOIP_ZERO;
            DoIP_TcpCon2LastTxBufSize[conIndx]          = DOIP_ZERO;
            DoIP_TcpCon2RxChannelActive[conIndx]        = DOIP_INV_PDU_ID;
            DoIP_TcpCon2TxMgtQueLvl[conIndx]            = DOIP_ZERO;
            DoIP_TcpCon2TxMgtQueIdx[conIndx]            = DOIP_ZERO;
            DoIP_TcpCon2TxTpSessionActive[conIndx]      = FALSE;
            DoIP_TcpCon2RxTpSessionActive[conIndx]      = FALSE;
            DoIP_TcpCon2TpPreTransMgt[conIndx].hdrType  = DOIP_HDR_TYPE_INVALID;
            DoIP_TcpCon2TxTpCancelRequested[conIndx]    = FALSE;
            DoIP_TcpCon2RxTpCancelRequested[conIndx]    = FALSE;
            while( DOIP_ZERO < idxTcpTx )
            {
                idxTcpTx--;
                DoIP_TcpCon2TcpTxMgt[conIndx][idxTcpTx].channel     = DOIP_INV_PDU_ID;
                DoIP_TcpCon2TcpTxMgt[conIndx][idxTcpTx].txHdrBufLen = DOIP_ZERO;
            }
        }
                     
        conIndx = DOIP_UDP_TX_MGT_LIST_SIZE;
        while( DOIP_ZERO < conIndx )
        {
            conIndx--;
            DoIP_UdpTxMgtList[conIndx].udpCon = DOIP_INV_PDU_ID;

        }

        conIndx = DOIP_CHANNELS_TOTAL;
        while( DOIP_ZERO < conIndx )
        {
            conIndx--;
            /* DoIP_Channel2TcpCon[conIndx] = DOIP_INV_PDU_ID; */
            DoIP_Channel2TcpCon[conIndx] = DoIP_Channel2DefaultTcpCon[conIndx];
            DoIP_Channel2TxMsgLen[conIndx] = DOIP_ZERO;
        }

#if( DOIP_NACK_APPEND_REQ == STD_ON )
        conIndx = DOIP_TESTER_TOTAL;
        while( DOIP_ZERO < conIndx )
        {
            conIndx--;
            DoIP_Tester2DiagNAckOffset[conIndx] = DOIP_ZERO;
        }
#endif /* (DOIP_NACK_APPEND_REQ == STD_ON ) */

        conIndx = DOIP_LOCAL_ADDR_TOTAL;
        while( DOIP_ZERO < conIndx )
        {
            conIndx--;
            DoIP_LocalAddrIdx2IpAddrReqState[conIndx] = DOIP_IP_ADDR_REQ_STATE_NONE;
        }
        
        id = DOIP_ZERO;
        while (id < DOIP_CONNECTION_TOTAL)
        {
            conIndx = DOIP_MAX_CONS_PER_LOC_ADDR;
            while( DOIP_ZERO < conIndx )
            {
                conIndx--;
                DoIP_RoutActivHandler[id].aliveCheckList[conIndx] = DOIP_INV_PDU_ID;
            }
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_ZERO] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_ONE] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_TWO] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecReq[DOIP_THREE] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_ZERO] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_ONE] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_TWO] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecRes[DOIP_THREE] = DOIP_ZERO;
            DoIP_RoutActivHandler[id].oemSpecUsed = FALSE;
            DoIP_RoutActivHandler[id].routActIdx = DOIP_INV_ROUT_ACT_IDX;
            DoIP_RoutActivHandler[id].testerAddr = DOIP_ADDR_ANY;
            DoIP_RoutActivHandler[id].testerIdx = DOIP_INV_ADDR_IDX;
            for(int conx = DOIP_ZERO;conx < DOIP_TESTER_TOTAL;conx++)
            {
                DoIP_RoutActivHandler[id].aliveCheckCnt[conx] = DOIP_ZERO;
            }
            DoIP_RoutActivHandler[id].aliveCheckElemNum = DOIP_ZERO;
            DoIP_RoutActivHandler[id].tcpCon = DOIP_INV_PDU_ID;
            id++;
        }
        
        

        DoIP_ActivationLineLocalState = DOIP_ACTIVATION_LINE_LOCAL_INACTIVE;

#if( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
        DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_ACTIVE;
#else
        DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_INACTIVE;
#endif /* (DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON) */

#if( DOIP_GID_SYNC_ENABLED == STD_ON )
        DoIP_GidInSync = FALSE;
#endif /* (DOIP_GID_SYNC_ENABLED == STD_ON) */

        DoIP_State = DOIP_STATE_INIT;
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_INIT, errorId);  /* Det report. */
#endif
}

#if( STD_ON == DOIP_VERSIONINFOAPI )
/*
*******************************************************************************
* Function Name: DoIP_GetVersionInfo
*
* Explanation: Returns the version information of this module.
*
* param: Std_VersionInfoType* versioninfo: Pointer to where to store the version
*                                          information of this module.
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00027] */
FUNC(void, DOIP_CODE) DoIP_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, DOIP_APPL_DATA)versionInfo
)
{
    uint8 errorId = DOIP_E_OK;

    if( NULL_PTR == versionInfo )
    {
        errorId = DOIP_E_PARAM_POINTER;   /* [SWS_DoIP_00172] */
    }
    else
    {
        versionInfo->vendorID = DOIP_VENDOR_ID;
        versionInfo->moduleID = DOIP_MODULE_ID;
        versionInfo->sw_major_version = DOIP_SW_MAJOR_VERSION;
        versionInfo->sw_minor_version = DOIP_SW_MINOR_VERSION;
        versionInfo->sw_patch_version = DOIP_SW_PATCH_VERSION;
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_GET_VERSION_INFO, errorId);  /* Det report. */
#endif
}
#endif

/*
*******************************************************************************
* Function Name: DoIP_SoAdTpCopyTxData
*
* Explanation: This function is called to acquire the transmit data of an I-PDU
*              segment (N-PDU). Each call to this function provides the next part
*              of the I-PDU data unless retry->TpDataState is TP_DATARETRY. In
*              this case the function restarts to copy the data beginning at the
*              offset from the current position indicated by retry->TxTpDataCnt.
*              The size of the remaining data is written to the position indicated
*              by availableDataPtr.
*
* param: PduIdType id: Identification of the transmitted I-PDU.
*        const PduInfoType* info: Provides the destination buffer (SduDataPtr)
*                                 and the number of bytes to be copied
*                                 (SduLength).
*        RetryInfoType* retry: This parameter is used to acknowledge transmitted
*                              data or to retransmit data after transmission
*                              problems.
*        PduLengthType* availableDataPtr: Indicates the remaining number of bytes
*                                         that are available in the upper layer
*                                         module's Tx buffer. availableDataPtr
*                                         can be used by TP modules that support
*                                         dynamic payload lengths(e.g. FrIsoTp)
*                                         to determine the size of the following
*                                         CFs.
*
* retval: BUFREQ_OK: Data has been copied to the transmit buffer completely as
*                    requested.
*         BUFREQ_E_BUSY: Request could not be fulfilled, because the required
*                        amount of Tx data is not available. The lower layer
*                        module may retry this call later on. No data has been
*                        copied.
*         BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
*******************************************************************************
*/
FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpCopyTxData
(
    PduIdType id,
    const PduInfoType* info,
    RetryInfoType* retry,
    PduLengthType* availableDataPtr
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    BufReq_ReturnType bufReqRetVal = BUFREQ_E_NOT_OK;
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( DOIP_CONNECTION_TCP_TOTAL <= id )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else if( (NULL_PTR == info) || (NULL_PTR == availableDataPtr) )
    {
        errorId = DOIP_E_PARAM_POINTER;
    }
    else if( (DOIP_ZERO != info->SduLength) && (NULL_PTR == info->SduDataPtr) )
    {
        errorId = DOIP_E_PARAM_POINTER;
    }
    else if( retry != NULL_PTR )
    {
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
#else
    DOIP_DUMMY_STATEMENT(retry);
#endif
    {
        if( DOIP_ACTIVATION_LINE_LOCAL_ACTIVE == DoIP_ActivationLineLocalState )
        {
           /* Check socket connection state. */
           if( (uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConState[id] )
           {
               /* TxPduId is equal to index for Connection. */
               bufReqRetVal = DoIP_TcpTxQueueCopyElement(id, (PduInfoType*)info, availableDataPtr);
           }
        }
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_TP_COPY_TX_DATA, errorId);
#endif

    return bufReqRetVal;
}

/*
*******************************************************************************
* Function Name: DoIP_SoAdTpTxConfirmation
*
* Explanation: This function is called after the I-PDU has been transmitted on
*              its network, the result indicates whether the transmission was
*              successful or not.
*
* param: PduIdType id: Identification of the transmitted I-PDU.
*        Std_ReturnType result: Result of the transmission of the I-PDU.
*
* retval: None
*******************************************************************************
*/
FUNC(void, DOIP_CODE) DoIP_SoAdTpTxConfirmation
(
    PduIdType id,
    Std_ReturnType result
)
{
    uint8 errorId = DOIP_E_NO_ERROR;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( DOIP_CONNECTION_TCP_TOTAL <= id )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else if( ((Std_ReturnType)DOIP_E_OK != result) && ((Std_ReturnType)DOIP_E_NOT_OK != result))
    {
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
#endif
    {
#if( DOIP_DEV_ERROR_DETECT == STD_OFF )
        if( (DOIP_STATE_INIT == DoIP_State) && (id < DOIP_CONNECTION_TCP_TOTAL) )
#endif
        {
            DoIP_TcpTxQueueRemoveElement(id, result);

            /* Reset cancellation. */
            if( TRUE == DoIP_TcpCon2TxTpCancelRequested[id] )
            {
                DoIP_TcpCon2TxTpCancelRequested[id] = FALSE;
            }

            if( (TRUE == DoIP_Con2SoConClosing[id]) && (DOIP_ZERO == DOIP_TCP_TX_QUEUE_GET_LEVEL(id)))
            {
                /* Socket shall be closed. [SWS_DoIP_00058] */
                DoIP_CloseSoCon(id);
                ActiveConfig_Init(id);
            }
            else
            {
#if( DOIP_TCP_TP_OPTIMZED == STD_ON )
                if( DOIP_TCP_TX_QUEUE_GET_LEVEL(id) > DOIP_ZERO )
                {
                    DoIP_TcpTxQueueSend(id);
                }
#endif
            }
        }
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_TP_TX_CONFIRMATION, errorId);
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_SoAdTpCopyRxData
*
* Explanation: This function is called to provide the received data of an I-PDU
*              segment (N-PDU) to the upper layer.
* param: PduIdType id: Identification of the received I-PDU.
*        const PduInfoType* info: Provides the source buffer (SduDataPtr) and the
*                                 number of bytes to be copied (SduLength). An
*                                 SduLength of 0 can be used to query the current
*                                 amount of available buffer in the upper layer
*                                 module. In this case, the SduDataPtr may be a
*                                 NULL_PTR.
*        PduLengthType* bufferSizePtr: Available receive buffer after data has
*                                      been copied.
*
* retval: BUFREQ_OK: Data copied successfully.
*         BUFREQ_E_NOT_OK: Data was not copied because an error occurred.
*******************************************************************************
*/
/* [SWS_DoIP_00033] */
FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpCopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST) info,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA) bufferSizePtr
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;  /* [SWS_DoIP_00183] */
    }
     else if( DOIP_CONNECTION_TOTAL <= id )
     {
         errorId = DOIP_E_INVALID_PDU_SDU_ID;  /* [SWS_DoIP_00036] */
     }
    else if( (NULL_PTR == info) || (NULL_PTR == bufferSizePtr) )
    {
        errorId = DOIP_E_PARAM_POINTER;  /* [SWS_DoIP_00184] */
    }
    else if( (info->SduLength != 0u) && (info->SduDataPtr == NULL_PTR) )
    {
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
#else
   // if( id < DOIP_CONNECTION_TCP_TOTAL )
   if( id < 100 )
#endif
    {
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
    if( TRUE == DoIP_IsTcpClientConnection[id] )
        {
            retVal = DoIP_SoAdTpClientCopyRxData(id, info,bufferSizePtr);
        }
        else
#endif
        {
            //DoIP_SoAdTpStartOfReception call this variable to indicate start recepetion data
            //DoIP_TcpCon2RxTpSessionActive[0] = TRUE;
            retVal = DoIP_SoAdTpServerCopyRxData(id, info, bufferSizePtr);
        }

        if( (BUFREQ_OK == retVal) && ((*bufferSizePtr) != DOIP_ZERO) )
        {
            /* Indicates that no exception has occurred and expects to copy data from SoAd modules. */
            DoIP_TcpCon2RxMsgWaitCnt[id] = DOIP_TCP_RX_MSG_WAIT;
        }
        else
        {
            DoIP_TcpCon2RxMsgWaitCnt[id] = DOIP_ZERO;
        }
    }

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_TP_COPY_RX_DATA, errorId);
#endif

    return retVal;
}

/*
*******************************************************************************
* Function Name: DoIP_SoAdTpStartOfReception
*
* Explanation: This function is called at the start of receiving an N-SDU. The
*              N-SDU might be fragmented into multiple N-PDUs (FF with one or
*              more following CFs) or might consist of a single N-PDU (SF).
* param: PduIdType id: Identification of the I-PDU.
*        const PduInfoType* info: Pointer to a PduInfoType structure containing
*                                 the payload data (without protocol information)
*                                 and payload length of the first frame or single
*                                 frame of a transport protocol I-PDU reception.
*                                 Depending on the global parameter MetaDataLength,
*                                 additional bytes containing MetaData (e.g. the
*                                 CAN ID) are appended after the payload data,
*                                 increasing the length accordingly. If neither
*                                 first/single frame data nor MetaData are
*                                 available, this parameter is set to NULL_PTR.
*        PduLengthType TpSduLength: Total length of the N-SDU to be received.
*        PduLengthType* bufferSizePtr: Available receive buffer in the receiving
*                                      module. This parameter will be used to
*                                      compute the Block Size (BS) in the
*                                      transport protocol module.
*
* retval: BUFREQ_OK: Connection has been accepted. bufferSizePtr indicates the
*                    available receive buffer; reception is continued. If no
*                    buffer of the requested size is available, a receive buffer
*                    size of 0 shall be indicated by bufferSizePtr.
*         BUFREQ_E_NOT_OK: Connection has been rejected; reception is aborted.
*                          bufferSizePtr remains unchanged.
*         BUFREQ_E_OVFL: No buffer of the required length can be provided;
*                        reception is aborted. bufferSizePtr remains unchanged.
*******************************************************************************
*/
/* [SWS_DoIP_00037] */
FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpStartOfReception
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)info,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA)bufferSizePtr
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )  /* [SWS_DoIP_00186] */
    {
        errorId = DOIP_E_UNINIT;
    }
    else if( DOIP_CONNECTION_TOTAL <= id )  /* [SWS_DoIP_00187] */
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;
    }
    else if( NULL_PTR == bufferSizePtr )   /* [SWS_DoIP_00188] */
    {
        errorId = DOIP_E_PARAM_POINTER;
    }
    else if ( TpSduLength != 0u )
    {
      errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
#else
    DOIP_DUMMY_STATEMENT(TpSduLength);
    DOIP_DUMMY_STATEMENT(bufferSizePtr);
    if( id < DOIP_CONNECTION_TCP_TOTAL )
#endif
    {
        if( DOIP_ACTIVATION_LINE_LOCAL_ACTIVE == DoIP_ActivationLineLocalState )
        {
            /* Prevent compiler warnings for unused parameter. */
            DOIP_DUMMY_STATEMENT(info);
            DoIP_TcpCon2LastRxBufSize[id] = DOIP_REQ_LEN_BYTE_TOTAL;
#if 0
            /* [SWS_DoIP_00207] */
            // *bufferSizePtr = DOIP_REQ_LEN_BYTE_TOTAL;
            // DoIP_TcpCon2LastRxBufSize[id] = DOIP_REQ_LEN_BYTE_TOTAL;

            if( info->SduLength >  DoIP_TcpCon2LastRxBufSize[id])
            {
                /* unexpected length. [SWS_DoIP_00018]*/
                (void)DoIP_TcpTransmit(id, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_OUT_OF_MEM, DOIP_ZERO, DOIP_ZERO, NULL_PTR, TRUE);  /* [SWS_DoIP_00018] */
                retVal = BUFREQ_E_OVFL;
            }
#endif
            /* Check socket connection state. */
            if( (uint8)SOAD_SOCON_ONLINE != DoIP_Con2SoConState[id] )
            {
                /* Socket connection is not online. nothing to do here. */
            }
            /* TP Routing is already active. */
            else if( TRUE == DoIP_TcpCon2RxTpSessionActive[id] )
            {
                retVal = BUFREQ_OK;
                /* nothing to do here. */
            }
            else /* TP Routing is not active. */
            {
                /* Activate TP session. */
                DoIP_TcpCon2RxTpSessionActive[id] = TRUE;
                retVal = BUFREQ_OK;
            }
        }
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( errorId != DOIP_E_NO_ERROR )
    {
        DoIP_Det_ErrorReport(DOIP_API_ID_TP_START_OF_RECEPTION, errorId);
    }
#else
    DOIP_DUMMY_STATEMENT(errorId);
#endif
    return retVal;
}


/*
*******************************************************************************
* Function Name: DoIP_SoAdTpRxIndication
*
* Explanation: Called after an I-PDU has been received via the TP API, the result
*              indicates whether the transmission was successful or not.
*
* param: PduIdType id: Identification of the received I-PDU.
*        Std_ReturnType result: Result of the reception.
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00038] */
FUNC(void, DOIP_CODE) DoIP_SoAdTpRxIndication
(
    PduIdType id,
    Std_ReturnType result
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;  /* [SWS_DoIP_00190] */
    }
    else if( DOIP_CONNECTION_TCP_TOTAL <= id )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;  /* [SWS_DoIP_00191] */
    }
    else if( ((Std_ReturnType)DOIP_E_OK != result) &&
             ((Std_ReturnType)DOIP_E_NOT_OK != result) )
    {
        errorId = DOIP_E_INVALID_PARAMETER;   /* [SWS_DoIP_00192] */
    }
    else
#else
    DOIP_DUMMY_STATEMENT(result);
    if( id < DOIP_CONNECTION_TCP_TOTAL )
#endif
    {
        /* TP session is now offline. */
        DoIP_TcpCon2RxTpSessionActive[id] = FALSE;
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if ( errorId != DOIP_E_NO_ERROR )
    {
        DoIP_Det_ErrorReport(DOIP_API_ID_TP_RX_INDICATION, errorId);
    }
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_SoAdIfRxIndication
*
* Explanation: Indication of a received I-PDU from a lower layer communication
*              interface module.
*
* param: RxPduId: ID of the received I-PDU.
*        PduInfoPtr: Contains the length (SduLength) of the received I-PDU
*                    and a pointer to a buffer (SduDataPtr) containing the I-PDU.
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00244] */
FUNC(void, DOIP_CODE) DoIP_SoAdIfRxIndication
(
    PduIdType RxPduId,
    PduIdType soConID,
    P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)PduInfoPtr
)
{
    boolean closeSocket = FALSE;
    uint8 srcHdrVer;
    uint8 srcHdrInvVer;
    uint8 errorId = DOIP_E_NO_ERROR;
    Std_ReturnType retVal = DOIP_E_OK;
    uint16 srcHdrType;
    uint32 srcHdrLen;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;   /* [SWS_DoIP_00246] */
    }
    else if( (DOIP_CONNECTION_TCP_TOTAL > RxPduId) ||
             (DOIP_CONNECTION_TCP_UDP_TOTAL <= RxPduId) )     /* [SWS_DoIP_00061] [SWS_DoIP_00062] [SWS_DoIP_00067] [SWS_DoIP_00090] [SWS_DoIP_00094] */
    {
       // errorId = DOIP_E_INVALID_PDU_SDU_ID;  /* [SWS_DoIP_00247] */
    }
    else if( (NULL_PTR == PduInfoPtr) || (NULL_PTR == PduInfoPtr->SduDataPtr) )
    {
        errorId = DOIP_E_PARAM_POINTER;   /* [SWS_DoIP_00248] */
    }
    else
    {
        /* Nothing to do. */
    }
#endif
   // DoIP_Con2IpAddrState[RxPduId] = SOAD_IPADDR_STATE_ASSIGNED;
    if( DOIP_E_NO_ERROR == errorId )
    {
        /* No IP is assigned. */
        if( SOAD_IPADDR_STATE_ASSIGNED == DoIP_Con2IpAddrState[RxPduId] )
        {
            /* Socket connection is online and requested is not to be closed. */
            if( ((uint8)SOAD_SOCON_ONLINE == DoIP_Con2SoConUDPState[RxPduId]))
                         //&& ((uint8)FALSE == DoIP_Con2SoConClosing[RxPduId]) )
            {
                /* message too short. */
                if( DOIP_GEN_HDR_LEN_BYTE > PduInfoPtr->SduLength )
                {
                    DoIP_CloseSoConUDP(soConID);     /* [SWS_DoIP_00014] */
                }
                else
                {
                    /* Extract generic header. */
                    DOIP_GET_UINT8(PduInfoPtr->SduDataPtr, ((uint8)DOIP_ZERO), srcHdrVer);
                    DOIP_GET_UINT8(PduInfoPtr->SduDataPtr, ((uint8)DOIP_ONE), srcHdrInvVer);
                    DOIP_GET_UINT16(PduInfoPtr->SduDataPtr, ((uint8)DOIP_TWO), srcHdrType);
                    DOIP_GET_UINT32(PduInfoPtr->SduDataPtr, ((uint8)DOIP_FOUR), srcHdrLen);

                    /* Header pattern does not match configured DoIP version. */
                    /* Check whether default protocol version is used and valid here. */
                    if( (DOIP_PROTOCOL_VERSION != (uint8)srcHdrVer) ||
                         (DOIP_PROTOCOL_VERSION != (uint8)(~srcHdrInvVer)) )
                    {
                        /* Invalid header pattern. */  /* [SWS_DoIP_00015] */
                        if( (DOIP_PROTOCOL_VERSION_DEFAULT != (uint8)srcHdrVer) ||
                              (DOIP_PROTOCOL_VERSION_DEFAULT != (uint8)(~srcHdrInvVer)) ||
                              (DOIP_HDR_TYPE_VEHICLE_IDENT_REQ > srcHdrType) ||
                              (DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN < srcHdrType) )
                        {
                            (void)DoIP_UdpTransmit(soConID, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_FORMAT, TRUE);  /* [SWS_DoIP_00014] */
                            retVal = DOIP_E_NOT_OK;
                        }
                    }

                    if( (Std_ReturnType)DOIP_E_OK == retVal )
                    {
                        /* Invalid header length relative to received data length. */
                        if( (DOIP_GEN_HDR_LEN_BYTE + srcHdrLen) != PduInfoPtr->SduLength )
                        {
                            (void)DoIP_UdpTransmit(soConID, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, TRUE);   /* [SWS_DoIP_00019] */
                        }
                        else
                        {
                            /* Receive the udp data by header type. */
                            DoIP_SoAdIfRxDataOfHdrTyp(soConID, srcHdrType, srcHdrLen, DOIP_ZERO, PduInfoPtr, closeSocket);
                        }
                    }
                }
            }
        }
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_IF_RX_INDICATION, errorId);
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_SoAdIfTxConfirmation
*
* Explanation: The lower layer communication interface module confirms the
*              transmission of an IPDU.
*
* param: TxPduId: ID of the I-PDU that has been transmitted.
*        result: E_OK: The PDU was transmitted.
*                E_NOT_OK: Transmission of the PDU failed.
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00245] */
FUNC(void, DOIP_CODE) DoIP_SoAdIfTxConfirmation
(
    PduIdType TxPduId,
    Std_ReturnType result
)
{
    uint8 errorId = DOIP_E_NO_ERROR;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )

    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;     /* [SWS_DoIP_00249] */
    }
    else if( (DOIP_CONNECTION_TCP_TOTAL > TxPduId) || (DOIP_CONNECTION_TOTAL <= TxPduId) )
    {
        errorId = DOIP_E_INVALID_PDU_SDU_ID;    /* [SWS_DoIP_00250] */
    }
    else if( ((Std_ReturnType)DOIP_E_OK != result) && ((Std_ReturnType)DOIP_E_NOT_OK != result) )
    {
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
    {
        /* nothing to do here. */
    }
#else
    /* Prevent compiler warnings for unused parameter. */
    DOIP_DUMMY_STATEMENT(TxPduId);
    DOIP_DUMMY_STATEMENT(result);
#endif

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( errorId != DOIP_E_NO_ERROR )
    {
        DoIP_Det_ErrorReport(DOIP_API_ID_IF_TX_CONFIRMATION, errorId);
    }
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_SoConModeChg
*
* Explanation: Notification about a SoAd socket connection state change, e.g.
*              socket connection gets online.
*
* param: SoAd_SoConIdType SoConId: socket connection index specifying the socket
*                                  connection with the mode change.
*        SoAd_SoConModeType Mode: new mode.
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00039] */
FUNC(void, DOIP_CODE) DoIP_SoConModeChg
(
    SoAd_SoConIdType SoConId,
    SoAd_SoConModeType Mode
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    uint8 listIdx = DOIP_MAX_CONS_PER_LOC_ADDR;
    PduIdType connection = DOIP_ZERO;
    PduIdType idxChannel;
    PduIdType idxConnection = DOIP_UDP_TX_MGT_LIST_SIZE;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;  /* [SWS_DoIP_00193] */
    }
    else if( sockCon ==  SOAD_INV_SO_CON_ID)
    {
        errorId = DOIP_E_INVALID_PARAMETER;  /* [SWS_DoIP_00194] */
    }
    else
#else
    if( (Std_ReturnType)E_OK == DoIP_GetConnectionBySoConId(SoConId, &connection) )
#endif
    {
        if( (SOAD_SOCON_OFFLINE == Mode) || (SOAD_SOCON_ONLINE == Mode) || (SOAD_SOCON_RECONNECT == Mode) )
        {
            if( SOAD_SOCON_ONLINE != Mode )
            {
                /* [SWS_DoIP_00243] */
                /* Terminate all transmission requests. */
                DoIP_Con2SoConState[connection] = (uint8)Mode;
                DoIP_Con2SoConClosing[connection] = FALSE;
                /* TCP connection. */
                if( DOIP_CONNECTION_TCP_TOTAL > connection )
                {
#if( DOIP_NACK_APPEND_REQ == STD_ON )
                    if( DOIP_INV_TESTER_IDX != DoIP_TcpCon2ActivMgt[connection].testerIdx )
                    {
                        DoIP_Tester2DiagNAckOffset[DoIP_TcpCon2ActivMgt[connection].testerIdx] = DOIP_ZERO;
                    }
#endif /* ( DOIP_NACK_APPEND_REQ == STD_ON ) */
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
                    DoIP_HandleRelatedClientTcpCon(connection, Mode);
#endif
                    /* [SWS_DoIP_00115] */
                    DoIP_TcpCon2ActivMgt[connection].testerIdx    = DOIP_INV_TESTER_IDX;
                    DoIP_TcpCon2ActivMgt[connection].testerAddr   = DOIP_ADDR_ANY;
                    DoIP_TcpCon2ActivMgt[connection].routActIdx   = DOIP_INV_ROUT_ACT_IDX;
                    DoIP_TcpCon2ActivMgt[connection].activState   = DOIP_ROUT_ACTIV_STATE_NONE;
                    DoIP_TcpCon2InactivCnt[connection]            = DOIP_ZERO;
                    DoIP_TcpCon2RxMsgWaitCnt[connection]          = DOIP_ZERO;
                    DoIP_TcpCon2RxMsgOffset[connection]           = DOIP_ZERO;
                    DoIP_TcpCon2TxBytesCopied[connection]         = DOIP_ZERO;
                    DoIP_TcpCon2TxTpSessionActive[connection]     = FALSE;
                    DoIP_TcpCon2RxTpSessionActive[connection]     = FALSE;
                    DoIP_TcpCon2SkipRxMsg[connection]             = FALSE;
                    DoIP_TcpCon2TpPreTransMgt[connection].hdrType = DOIP_HDR_TYPE_INVALID;
                    DoIP_TcpCon2TxTpCancelRequested[connection]   = FALSE;
                    DoIP_TcpCon2RxTpCancelRequested[connection]   = FALSE;
                    /* Alive check ongoing. */
                    if( DOIP_INV_PDU_ID != DoIP_RoutActivHandler[SoConId].tcpCon )
                    {
                        /* Routing Activation active. */
                        if( DOIP_ZERO < DoIP_RoutActivHandler[SoConId].aliveCheckElemNum )
                        {
                            while( DOIP_ZERO < listIdx )
                            {
                                listIdx--;
                                if( connection == DoIP_RoutActivHandler[SoConId].aliveCheckList[listIdx] )
                                {
                                    /* Alive check pending. */
                                    DoIP_RoutActivHandler[SoConId].aliveCheckList[listIdx] = DOIP_INV_PDU_ID;
                                    DoIP_RoutActivHandler[SoConId].aliveCheckElemNum--;
                                }
                            }
                        }
                       if( (DOIP_ZERO == DoIP_RoutActivHandler[SoConId].aliveCheckElemNum) &&
                            ((uint8)SOAD_SOCON_ONLINE != DoIP_Con2SoConState[DoIP_RoutActivHandler[SoConId].tcpCon]) )
                       {
                            /* All routing activation relevant socket connections closed or alive check received. */
                            /* Release handler. */
                            DoIP_RoutActivHandler[SoConId].tcpCon = DOIP_INV_PDU_ID;
                       }
                    }
                    /* Reception is ongoing. */
                    if( DOIP_INV_PDU_ID != DoIP_TcpCon2RxChannelActive[connection] )
                    {
                        PduR_DoIPTpRxIndication(DoIP_Channel2PduRRxPduId[DoIP_TcpCon2RxChannelActive[connection]], E_NOT_OK);
                        DoIP_TcpCon2RxChannelActive[connection] = DOIP_INV_PDU_ID;
                    }
                    /* Reset Tx Queue. */
                    while( DOIP_ZERO < DOIP_TCP_TX_QUEUE_GET_LEVEL(connection) )
                    {
                        DoIP_TcpTxQueueRemoveElement(connection, E_NOT_OK);
                    }

                    /* Reset channel specific structs. */
                    idxChannel = DOIP_CHANNELS_TOTAL;
                    while( DOIP_ZERO < idxChannel )
                    {
                        idxChannel--;
                        if( connection == DoIP_Channel2TcpCon[idxChannel] )
                        {
                            DoIP_Channel2TcpCon[idxChannel]   = DoIP_Channel2DefaultTcpCon[idxChannel];
                            DoIP_Channel2TxMsgLen[idxChannel] = DOIP_ZERO;
                        }
                    }
                }
                else
                {
                    /* UDP connection. */
                    /* Reset Tx list. */
                    while( DOIP_ZERO < idxConnection )
                    {
                        idxConnection--;
                        if( DoIP_UdpTxMgtList[idxConnection].udpCon == connection )
                        {
                            DoIP_UdpTxMgtList[idxConnection].udpCon = DOIP_INV_PDU_ID;
                        }
                    }
                }
            }
            else  /* socket connection is online */
            {

                /* [SWS_DoIP_00241] */
                if( SOAD_IPADDR_STATE_ASSIGNED == DoIP_Con2IpAddrState[connection] )
                {
                    /* IP address assigned. */
                    DoIP_Con2SoConState[connection] = (uint8)Mode;
                    DoIP_Con2SoConClosing[connection] = FALSE;

                   if( DOIP_CONNECTION_TCP_UDP_TOTAL <= connection )
                    {
                        if( TRUE == DoIP_VehicleAnncSendFlag )
                        {
                            /* UDP Vehicle Announcement connection. */
                            /* Trigger Vehicle Announcements. */
                            /* List Vehicle Announcement in Tx list. [SWS_DoIP_00205]*/
                            if( (Std_ReturnType)E_OK != DoIP_UdpTransmit(connection, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_ANNOUNCE_NUM, FALSE) )
                            {
                                /* Buffer overflow after socket connection setup should not happen. */
                                errorId = DOIP_E_NOBUFS;
                            }
                            DoIP_VehicleAnncSendFlag = FALSE;
                        }
                    }
                }
                else
                {
                    errorId = DOIP_E_UNEXPECTED_ASSIGNMENT;
                }
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
                if( SOAD_SOCON_ONLINE == DoIP_Con2SoConState[connection] )
                {
                    DoIP_TriggerSendRouteActiveReq(connection, Mode);
                }
#endif
            }
        }
        else
        {
            /* Invalid Mode. [SWS_DoIP_00194] */
            errorId = DOIP_E_INVALID_PARAMETER;
        }
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_SO_CON_MODE_CHG, errorId);
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_LocalIpAddrAssignmentChg
*
* Explanation: This function gets called by the SoAd if an IP address assignment
*              related to a socket connection changes (i.e. new address assigned
*              or assigned address becomes invalid).
*
* param: SoAd_SoConIdType SoConId: socket connection index specifying the socket
*                                  connection where the IP address assigment has
*                                  changed.
*        TcpIp_IpAddrStateType State: state of IP address assignment.
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00040] */
FUNC(void, DOIP_CODE) DoIP_LocalIpAddrAssignmentChg
(
    SoAd_SoConIdType SoConId,
    TcpIp_IpAddrStateType State
)
{
    uint8 errorId = DOIP_E_NO_ERROR;
    uint8 addrIdx;
    PduIdType connection = DOIP_ZERO;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;   /* [SWS_DoIP_00195] */
    }
    else if( (SOAD_IPADDR_STATE_ASSIGNED != (uint8)State)   &&
             (SOAD_IPADDR_STATE_UNASSIGNED != (uint8)State) &&
             (SOAD_IPADDR_STATE_ONHOLD != (uint8)State) )
    {
        /* Unknown state. [SWS_DoIP_00196]*/
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else if( DoIP_GetConnectionBySoConId(SoConId, &connection) != E_OK )
    {
        errorId = DOIP_E_INVALID_PARAMETER;
    }
    else
#else
    if( (Std_ReturnType)E_OK == DoIP_GetConnectionBySoConId(SoConId, &connection) )
#endif
    {
        addrIdx = DoIP_Con2LocalAddrIdx[connection];
        switch( DoIP_ActivationLineLocalState )
        {
            case DOIP_ACTIVATION_LINE_LOCAL_ACTIVE:
            {
                DoIP_Con2IpAddrState[connection] = (uint8)State;
                if( SOAD_IPADDR_STATE_UNASSIGNED == (uint8)State )
                {
                    DoIP_LocalAddrIdx2IpAddrReqState[addrIdx] = DOIP_IP_ADDR_REQ_STATE_NONE;
                    /* Request socket connection close to reset open/close sequence in SoAd. */
                    DoIP_CloseSoCon(connection);
                    ActiveConfig_Init(connection);
                }
                else if( SOAD_IPADDR_STATE_ASSIGNED == (uint8)State )
                {
                    DoIP_RefreshDhcpHostName(SoConId);   /* [SWS_DoIP_00154] */
                    DoIP_LocalAddrIdx2IpAddrReqState[addrIdx] = DOIP_IP_ADDR_REQ_STATE_ASSIGNED;
                    /* Open socket connections initially after IP address reassignment. */
                    /* (void)SoAd_OpenSoCon(DoIP_Con2SoConId[connection]); */
                    DoIP_OpenSockConInitially(connection);
                }
                else
                {
                    /* Nothing to do. */
                }
                break;
            }
#if( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
            case DOIP_ACTIVATION_LINE_LOCAL_ACTIVE_TO_INACTIVE:
            {
                DoIP_Con2IpAddrState[connection] = (uint8)State;
                if( SOAD_IPADDR_STATE_UNASSIGNED == (uint8)State )
                {
                    /* IP address not assigned. */
                    /* IpAddrReqState is set multiple times (for each SoConId). */
                    DoIP_LocalAddrIdx2IpAddrReqState[addrIdx] = DOIP_IP_ADDR_REQ_STATE_NONE;
                }
                break;
            }
#endif /* ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON ) */
            default:
            {
                /* Invalid state. */
                errorId = DOIP_E_UNEXPECTED_ASSIGNMENT;
                break;
            }
        }
   }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_LOC_IP_ADDR_ASSIGN_CHG, errorId);
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_ActivationLineSwitchActive
*
* Explanation: This function is used to notify the DoIP on a switch of the
*              DoIPActivationLine to active.
*
* param: None
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00201] [SWS_DoIP_00251]*/
FUNC(void, DOIP_CODE) DoIP_ActivationLineSwitchActive(void)
{
    uint8 errorId = DOIP_E_NO_ERROR;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
       errorId = DOIP_E_UNINIT;  /* [SWS_DoIP_00285] */
    }
    else
#endif
    {
#if( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
        /* Switch to active. */
        DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_ACTIVE;
        DoIP_VehicleAnncSendFlag = TRUE;
#endif /* ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON ) */

    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_ACTIVE_LINE_SWITCH, errorId);
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_ActivationLineSwitchInactive
*
* Explanation: This function is used to notify the DoIP on a switch of the
*              DoIPActivationLine to inactive.
*
* param: None
*
* retval: None
*******************************************************************************
*/
/* [SWS_DoIP_00201] [SWS_DoIP_91001]*/
FUNC(void, DOIP_CODE) DoIP_ActivationLineSwitchInactive(void)
{
    uint8 errorId = DOIP_E_NO_ERROR;

#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    if( DOIP_STATE_INIT != DoIP_State )
    {
        errorId = DOIP_E_UNINIT;  /* [SWS_DoIP_00285] */
    }
    else
#endif
    {
#if( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
           /* Switch to inactive. */
           DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_INACTIVE;
#endif /* ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON ) */
    }
#if( DOIP_DEV_ERROR_DETECT == STD_ON )
    DoIP_Det_ErrorReport(DOIP_API_ID_INACTIVE_LINE_SWITCH, errorId);
#endif
}

/*
*******************************************************************************
* Function Name: DoIP_MainFunction
*
* Explanation: Schedules the Diagnostic over IP module.
*              (Entry point for scheduling).
*
* param: None
*
* retval: None
*******************************************************************************
*/
void DoIP_MainFunction(void)
{
   // raise(SIGUSR1);
    uint8 errorId = DOIP_E_NO_ERROR;
    if( DOIP_STATE_UNINIT == DoIP_State )
    {
        errorId = DOIP_E_UNINIT;
    }
    else
    {
        if( DOIP_STATE_INIT == DoIP_State )
        {
            /* DoIP is initialized. */
            /* Handling depends on activation line state. */
            switch( DoIP_ActivationLineLocalState )
            {
                case DOIP_ACTIVATION_LINE_LOCAL_INACTIVE:
                {
                    /* Local activation line state inactive. */
                    DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_ACTIVE;
                    if ( DOIP_ACTIVATION_LINE_ACTIVE == DoIP_ActivationLineState )
                    {
                        /* requested to be active. */
                        DoIP_ActivationLineLocalState = DOIP_ACTIVATION_LINE_LOCAL_INACTIVE_TO_ACTIVE;
                        /* Copy case DOIP_ACTIVATION_LINE_LOCAL_INACTIVE_TO_ACTIVE to handle state in this main function cycle. */
                        DoIP_ActLineToActive();
                    }
                    break;
                }
                case DOIP_ACTIVATION_LINE_LOCAL_INACTIVE_TO_ACTIVE:
                {
                    /* Local activation line state in transition from inactive to active. */
                    DoIP_ActLineToActive();
                    break;
                }
                case DOIP_ACTIVATION_LINE_LOCAL_ACTIVE:
                {
                    /* Local activation line state active. */
#if( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
                    if( DOIP_ACTIVATION_LINE_INACTIVE == DoIP_ActivationLineState )
                    {
                        /* Requested to be inactive. */
                        DoIP_ActivationLineLocalState = DOIP_ACTIVATION_LINE_LOCAL_ACTIVE_TO_INACTIVE;
                        /* Copy case DOIP_ACTIVATION_LINE_LOCAL_ACTIVE_TO_INACTIVE to handle state in this main function cycle. */
                        DoIP_ActLineToInactive();
                    }
                    else
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */
                    {
  
                         DoIP_HandleUDPSocketState();
                        // DoIP_SoConModeChg(DoIP_Con2SoConId[0],SOAD_SOCON_ONLINE);
                         DoIP_HandleUdpTxList();
                        // DoIP_SoConModeChg(DoIP_Con2SoConId[0],SOAD_SOCON_OFFLINE);


                        DoIP_HandleSockConStates();
#if( DOIP_GID_SYNC_ENABLED == STD_ON )
                        DoIP_HandleGidSync();
#endif /* ( DOIP_GID_SYNC_ENABLED == STD_ON ) */
                        uint8 id = DOIP_CONNECTION_TOTAL;
                        while(id > DOIP_ZERO)
                        {
                            id--;
                            DoIP_HandleAuthConf(id);
                       //DoIP_HandleUdpTxList();
                            DoIP_HandleTcpTxQueue();
                            DoIP_TcpRx_HandleAliveCheckTimeouts(id);
                        }
                        DoIP_TcpRx_HandleInactivityTimeouts();
                        DoIP_Tcp_HandleRxMsgTimeouts();
                    }
                    break;
                }
#if( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
                case DOIP_ACTIVATION_LINE_LOCAL_ACTIVE_TO_INACTIVE:
                {
                    /* Local activation line state in transition from active to inactive. */
                    DoIP_ActLineToInactive();
                    break;
                }
#endif /* ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON ) */

                default:
                {
                    /* Invalid state. */
                    /* Nothing to do. */
                    break;
                }
            }
        }
    }
    DoIP_Det_ErrorReport(DOIP_API_ID_MAIN_FUNCTION, errorId);
}

/*
*******************************************************************************
* Function Name: DoIP_Memcpy
* Explanation: DoIP Memcpy Function.
*
* param: destData: Dest Ptr.
*        srcData: Source Ptr.
*        dataCnt: Byte Counter.
*
* retval: None.
*******************************************************************************
*/
void DoIP_HandleUDPSocketState()
{
    int udpCon = 0;
    int connection = 1;
    if(DoIP_Con2SoConUDPState[0] == SOAD_SOCON_OFFLINE)
    {
        udpCon = socketUdpInit(&servaddrUDP);

        DoIP_Con2SoConUDPState[0] = SOAD_SOCON_ONLINE;
        if(udpCon != 0)
        {
            DoIP_UdpTxMgtList[connection -1].udpCon = udpCon;
            DoIP_UdpTxMgtList[connection -1].hdrType = DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT;
            DoIP_UdpTxMgtList[connection -1].retryAttempt = 3;
            DoIP_UdpTxMgtList[connection -1].param2 = 3;
        }
    }
    
}

void DoIP_Memcpy
(
    uint8* destData,
    const uint8* srcData,
    uint32 dataCnt
)
{
    /* judge Null Pointer */
    if( (NULL_PTR == destData) || (NULL_PTR == srcData) || (DOIP_ZERO == dataCnt) )
    {
        /* Nothing Done */
    }
    else
    {
        while( DOIP_ZERO < dataCnt )
        {
            dataCnt--;
            destData[dataCnt] = srcData[dataCnt];
        }
    }
}


/*
*******************************************************************************
* Function Name: DoIP_ActivationLineStateTransitionToActive
*
* Explanation:
*
* param:
*
* retval:
*******************************************************************************
*/
/* [SWS_DoIP_00204] */
Std_ReturnType DoIP_GetSoConIdByConId
(
    uint16 connection,
    SoAd_SoConIdType* soConIdPtr
)
{
    Std_ReturnType stdRet = E_NOT_OK;
    SoAd_SoConIdType soConId = SOAD_INV_SO_CON_ID;

    
    soConId = socketTcpInit(&servaddr);
    
    if(soConId > 0)
    {
        stdRet = E_OK;   
       // printf("socket tcp/ip connect success\n");     
    }
    else
    {
        soConId = SOAD_INV_SO_CON_ID;
    }
    //setSocketcon(soConId);


    // while (connect(soConId, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    // {
    //     printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    // } 
    // printf("socket tcp/ip connect success\n");
    // stdRet = E_OK;
    
    //stdRet = SoAd_GetSoConId(DoIP_Con2SoAdTxPduId[connection], &soConId);  //open socket
    
    *soConIdPtr = soConId;
    //printf("*soConIdPtr  = %d\n",*soConIdPtr);
    

    return stdRet;
}

#define DOIP_STOP_SEC_CODE
//#include "DoIP_MemMap.h"


