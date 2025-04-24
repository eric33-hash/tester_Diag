#ifndef DOIP_LCFG_H_
#define DOIP_LCFG_H_

#include "../Type/Type.h"
#include "../Compiler/Compiler.h"



/*
*******************************************************************************
*    Global Macros
*******************************************************************************
*/

#define  DOIP_TESTER_TOTAL  (1U)
#define  DOIP_CHANNELS_TOTAL  (2U)
#define  DOIP_CONNECTION_TOTAL  (1U)
#define  DOIP_CONNECTION_TCP_TOTAL  (1U)
#define  DOIP_CONNECTION_TCP_SERVER_TOTAL  (1U)
#define  DOIP_CONNECTION_TCP_UDP_TOTAL  (3U)
#define  DOIP_CONNECTION_UDP_ANNC_TOTAL  (0U)
#define  DOIP_LOCAL_ADDR_TOTAL  (0U)
#define  DOIP_ACTIVE_CONNECTION_SIZE  (2U)
#define  DOIP_ALIVE_CHECK_WAIT  (500U)
#define  DOIP_TCP_TX_MGT_QUEUE_SIZE   (4U)
#define  DOIP_UDP_TX_MGT_LIST_SIZE  (10U)
#define  DOIP_ADDR  (0x1001U)
#define  DOIP_VIN_INV_PATTERN  (0x0U)
#define  DOIP_GID_INV_PATTERN  (0x0U)
#define  DOIP_ANNOUNCE_WAIT  (50U)
#define  DOIP_ANNOUNCE_NUM  (3U)
#define  DOIP_INIT_INACTIV_WAIT  (6000U)
#define  DOIP_GEN_INACTIV_WAIT  (30000U)
#define  DOIP_TCP_RX_MSG_WAIT  (2000U)
#define  DOIP_ANNOUNCE_INTERVAL  (0xFFFFFFU)
#define  DOIP_REQ_LEN_BYTE_TOTAL  (4096U)
#define  DOIP_MAX_UDP_REQ_PER_MSG  (1U)
#define  DOIP_TCP_TX_QUEUE_GET_LEVEL(connection)  (DoIP_TcpCon2TxMgtQueLvl[connection])
#define  DOIP_MAX_TESTER_CONNECTIONS  (2U)
#define  DOIP_SUPPORT_TCP_CLIENT_CONNECTION  (STD_ON)
#define  EntitysetIP  "127.0.0.1"
#define  DoIPTestersetIP  "127.0.0.1"


/*
*******************************************************************************
*    Global Types
*******************************************************************************
*/

typedef Std_ReturnType (*DoIP_AuthFctPtrType)(boolean* Authentified, const uint8* AuthenticationReqData,uint8* AuthenticationResData);
typedef Std_ReturnType (*DoIP_ConfFctPtrType)(boolean* Confirmed, const uint8* ConfirmationReqData,uint8* ConfirmationResData);


typedef struct
{
    uint8   ver;    /* Version */
	uint8   invVer;   /* Bit-Inverted version */
	uint8   type[2];   /* Payload type */
	uint8   lenByte[4]; /* Payload length */
	uint8   data[DOIP_BUFFER_MAX_LEN_BYTES];
} DoIP_HdrType_st; 
typedef struct
	{
	PduIdType channel;
	PduInfoType msg;
	PduLengthType txHdrBufLen;
	uint8 txHeader[DOIP_HDRBUF_MAX_LEN_BYTES];
	uint8* txData;
	}DoIP_TcpTxMgtType_st;
typedef struct
	{
	uint8     oemSpecReq[4];
	uint8     oemSpecRes[4];
	uint16    testerAddr;
	uint16    aliveCheckCnt[DOIP_TESTER_TOTAL];
	PduIdType aliveCheckList[DOIP_MAX_CONS_PER_LOC_ADDR];
	PduIdType tcpCon;
	uint8     aliveCheckElemNum;
	uint8    testerIdx;
	uint8     routActIdx;
	boolean   oemSpecUsed;
	}DoIP_RoutActivHandlerType_st;
typedef struct
{
    uint16 testerAddr;    /* tester address */
    uint32 testerIdx;     /* tester index */
    uint8 routActIdx;    /* routining activation index */
    DoIP_RoutActivStateType activState;   /* active state */
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_ON )
    uint8 actType;
    boolean oemSpecUsed;
    uint8 oemSpecReq[4];
#endif
} DoIP_RoutActivSockMgtType_st;
typedef struct
{
    uint16        hdrType;
    uint16        param1;
    uint16        param2;
    uint8         param3;
    boolean       closeSocket;
} DoIP_TpTxPrepareType_st;
typedef struct
{
    PduLengthType maxBufLen;
    uint8* bufPtr;
} DoIP_IfTxBufType_st;
typedef struct
{
    char*  remoteAddr;
    uint32                  param1;
    uint16                  param2;
    uint16                  hdrType;
    uint16                  retryAttempt;
    PduIdType               udpCon;
} DoIP_UdpTxMgtType_st;
typedef struct
{
    const uint8*            routActColPtr;
#if( DOIP_NACK_APPEND_REQ == STD_ON )
    uint8*                  diagAckNackBufPtr;
    uint32                  diagAckNackNumByte;
#endif /* ( DOIP_NACK_APPEND_REQ == STD_ON ) */
    uint16                  testerAddr;
    uint8                   routActNum; /* RoutActiv numbers total*/
    boolean                 centralSecurity;
} DoIP_TesterType_st;
typedef struct
{
    DoIP_AuthFctPtrType authFuncPtr;
    DoIP_ConfFctPtrType confFuncPtr;
    uint8 channelNum;
    uint8 authReqLength;
    uint8 authResLength;
    uint8 confReqLength;
    uint8 confResLength;
    uint8 routingActivationNum;
    const uint16 *targetAddrPtr;
} DoIP_RoutingActivationType_st;

extern PduInfoType lastMsgInfo;
/*
*******************************************************************************
*    Global Variables
*******************************************************************************
*/
extern uint8 DoIP_Con2SoConState[DOIP_CONNECTION_TOTAL];
extern uint8 DoIP_Con2SoConUDPState[DOIP_CONNECTION_TOTAL];
extern VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxTpSessionActive[DOIP_CONNECTION_TOTAL];
extern VAR(boolean, DOIP_VAR_NO_INIT) DoIP_Con2SoConClosing[DOIP_CONNECTION_TOTAL];
extern VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2LastRxBufSize[DOIP_CONNECTION_TOTAL];
extern VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxMsgOffset[DOIP_CONNECTION_TOTAL];
extern VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2InactivCnt[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_HdrType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxHdrBuf[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_RoutActivHandlerType_st, DOIP_VAR_NO_INIT) DoIP_RoutActivHandler[DOIP_CONNECTION_TOTAL];
extern VAR(PduIdType, DOIP_VAR_NO_INIT) DoIP_Channel2TcpCon[DOIP_CHANNELS_TOTAL];
extern VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2SkipRxMsg[DOIP_CONNECTION_TOTAL];
extern VAR(uint16, DOIP_VAR_NO_INIT) DoIP_TcpCon2LastRxTgtAddr[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_TpTxPrepareType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2TpPreTransMgt[DOIP_CONNECTION_TOTAL];
extern VAR(uint32, DOIP_VAR_NO_INIT) DoIP_Tester2DiagNAckOffset[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_RoutActivSockMgtType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2ActivMgt[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_RoutActivStateType, DOIP_VAR_NO_INIT) DoIP_RoutActivState[DOIP_CONNECTION_TCP_TOTAL];
extern VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxMgtQueLvl[DOIP_CONNECTION_TOTAL];
extern VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxMgtQueIdx[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_TcpTxMgtType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2TcpTxMgt[DOIP_CONNECTION_TOTAL][DOIP_TCP_TX_MGT_QUEUE_SIZE];
extern VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxTpSessionActive[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_IfTxBufType_st, DOIP_VAR_NO_INIT) DoIP_Channel2IfTxBuf[DOIP_CHANNELS_TOTAL];
extern VAR(PduLengthType, DOIP_VAR_NO_INIT) DoIP_Channel2TxMsgLen[DOIP_CHANNELS_TOTAL];
extern VAR(PduLengthType, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxBytesCopied[DOIP_CONNECTION_TOTAL];
extern VAR(PduLengthType, DOIP_VAR_NO_INIT) DoIP_TcpCon2LastTxBufSize[DOIP_CONNECTION_TOTAL];
extern VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxTpCancelRequested[DOIP_CONNECTION_TOTAL];
extern VAR(SoAd_SoConIdType, DOIP_VAR_NO_INIT) DoIP_Con2SoConId[DOIP_CONNECTION_TOTAL];
extern VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxTpCancelRequested[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_UdpTxMgtType_st, DOIP_VAR_NO_INIT) DoIP_UdpTxMgtList[DOIP_UDP_TX_MGT_LIST_SIZE];
extern VAR(uint8, DOIP_VAR_NO_INIT) DoIP_Con2IpAddrState[DOIP_CONNECTION_TOTAL];
extern VAR(DoIP_IpAddrReqStateType, DOIP_VAR_NO_INIT) DoIP_LocalAddrIdx2IpAddrReqState[DOIP_LOCAL_ADDR_TOTAL];
extern VAR(DoIP_IpAddrAssignmentType, DOIP_VAR_NO_INIT) DoIP_LocalAddrIdx2AssignmentType[DOIP_LOCAL_ADDR_TOTAL];
extern VAR(PduIdType, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxChannelActive[DOIP_CONNECTION_TCP_TOTAL];
extern CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Channel2PduRTxConfPduId[DOIP_CHANNELS_TOTAL]  ;
extern CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Channel2DefaultTcpCon[DOIP_CHANNELS_TOTAL];
extern CONST(uint8, DOIP_CONFIG_DATA) DoIP_Eid[6];
extern CONST(uint8, DOIP_CONFIG_DATA) DoIP_Gid[6];
extern CONST(uint8, DOIP_CONFIG_DATA) DoIP_Channel2ApiType[DOIP_CHANNELS_TOTAL];
extern CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Channel2PduRRxPduId[DOIP_CHANNELS_TOTAL + 1U];
extern CONST(uint16, DOIP_CONFIG_DATA) DoIP_Channel2EcuAddr[DOIP_CHANNELS_TOTAL + 1U];
extern CONST(uint16, DOIP_CONFIG_DATA)DoIP_Channel2SourceAddr[DOIP_CHANNELS_TOTAL];
extern CONST(DoIP_RoutingActivationType_st, DOIP_CONFIG_DATA) DoIP_RoutingActivations[DOIP_ACTIVE_CONNECTION_SIZE + 1U];
extern CONST(DoIP_TesterType_st, DOIP_CONFIG_DATA) DoIP_Tester[DOIP_TESTER_TOTAL + 1U];
extern CONST(uint8, DOIP_CONFIG_DATA) DoIP_Con2LocalAddrIdx[DOIP_CONNECTION_TOTAL];  
extern CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Con2SoAdTxPduId[DOIP_CONNECTION_TOTAL + 1U];
extern CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Con2SoAdRxCancelPduId[DOIP_CONNECTION_TCP_TOTAL + 1U];
extern CONST(boolean, DOIP_CONFIG_DATA) DoIP_IsTcpClientConnection[DOIP_CONNECTION_TCP_TOTAL];
extern CONST(boolean, DOIP_CONFIG_DATA) DoIPRequestAddressAssignment[DOIP_CONNECTION_TOTAL];
extern CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Con2SoAdTxPduIdOfAnnou[DOIP_CONNECTION_UDP_ANNC_TOTAL + 1U];


/*
*******************************************************************************
*    Global Functions
*******************************************************************************
*/
extern FUNC(Std_ReturnType, DOIP_CODE) AuthCallback0_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Authentified, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) AuthenticationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationResData);
extern FUNC(Std_ReturnType, DOIP_CODE) AuthCallback1_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Authentified, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) AuthenticationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationResData);
extern FUNC(Std_ReturnType, DOIP_CODE) ConfirmCallback0_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Confirmed, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) ConfirmationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) ConfirmationResData);
extern FUNC(Std_ReturnType, DOIP_CODE) ConfirmCallback1_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Confirmed, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) ConfirmationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) ConfirmationResData);
extern FUNC(void, DOIP_CODE) DoIP_Memset( P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) destPtr, uint8 val, uint32 cnt);
extern FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetFurtherActionByteFun
(
	DoIP_FurtherActionByteType* furAct
);
extern FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetVinFun(P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) vinBuf);

#endif/* DOIP_LCFG_H_ */
