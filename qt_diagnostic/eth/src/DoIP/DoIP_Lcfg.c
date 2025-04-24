
#include "../../include/DoIP/DoIP_Lcfg.h"


#define DOIP_START_SEC_CONFIG_DATA

static CONST(uint16, DOIP_CONFIG_DATA) DoIP_RouteActive2TargetAddr00[1]=
{
	0x1001,
};
static CONST(uint16, DOIP_CONFIG_DATA) DoIP_RouteActive2TargetAddr01[1]=
{
	0x1001,
};

#define DOIP_STOP_SEC_CONFIG_DATA



/*
*******************************************************************************
*    Global Variables
*******************************************************************************
*/

#define DOIP_START_SEC_CONFIG_DATA

uint8 DoIP_Con2SoConState[DOIP_CONNECTION_TOTAL];
uint8 DoIP_Con2SoConUDPState[DOIP_CONNECTION_TOTAL] = {0x02U};
VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxTpSessionActive[DOIP_CONNECTION_TOTAL];
VAR(boolean, DOIP_VAR_NO_INIT) DoIP_Con2SoConClosing[DOIP_CONNECTION_TOTAL];
VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2LastRxBufSize[DOIP_CONNECTION_TOTAL];
VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxMsgOffset[DOIP_CONNECTION_TOTAL];
VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2InactivCnt[DOIP_CONNECTION_TOTAL];
VAR(DoIP_HdrType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxHdrBuf[DOIP_CONNECTION_TOTAL];
VAR(DoIP_RoutActivHandlerType_st, DOIP_VAR_NO_INIT) DoIP_RoutActivHandler[DOIP_CONNECTION_TOTAL];
VAR(PduIdType, DOIP_VAR_NO_INIT) DoIP_Channel2TcpCon[DOIP_CHANNELS_TOTAL]; /* connection to channel */
VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2SkipRxMsg[DOIP_CONNECTION_TOTAL];
VAR(uint16, DOIP_VAR_NO_INIT) DoIP_TcpCon2LastRxTgtAddr[DOIP_CONNECTION_TOTAL];
VAR(DoIP_TpTxPrepareType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2TpPreTransMgt[DOIP_CONNECTION_TOTAL];
VAR(uint32, DOIP_VAR_NO_INIT) DoIP_Tester2DiagNAckOffset[DOIP_CONNECTION_TOTAL];
VAR(DoIP_RoutActivSockMgtType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2ActivMgt[DOIP_CONNECTION_TOTAL];
VAR(DoIP_RoutActivStateType, DOIP_VAR_NO_INIT) DoIP_RoutActivState[DOIP_CONNECTION_TCP_TOTAL];
VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxMgtQueLvl[DOIP_CONNECTION_TOTAL];
VAR(uint32, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxMgtQueIdx[DOIP_CONNECTION_TOTAL];
VAR(DoIP_TcpTxMgtType_st, DOIP_VAR_NO_INIT) DoIP_TcpCon2TcpTxMgt[DOIP_CONNECTION_TOTAL][DOIP_TCP_TX_MGT_QUEUE_SIZE];
VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxTpSessionActive[DOIP_CONNECTION_TOTAL];
VAR(DoIP_IfTxBufType_st, DOIP_VAR_NO_INIT) DoIP_Channel2IfTxBuf[DOIP_CHANNELS_TOTAL];
VAR(PduLengthType, DOIP_VAR_NO_INIT) DoIP_Channel2TxMsgLen[DOIP_CHANNELS_TOTAL];
VAR(PduLengthType, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxBytesCopied[DOIP_CONNECTION_TOTAL];
VAR(PduLengthType, DOIP_VAR_NO_INIT) DoIP_TcpCon2LastTxBufSize[DOIP_CONNECTION_TOTAL];
VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2TxTpCancelRequested[DOIP_CONNECTION_TOTAL];
VAR(SoAd_SoConIdType, DOIP_VAR_NO_INIT) DoIP_Con2SoConId[DOIP_CONNECTION_TOTAL];
VAR(boolean, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxTpCancelRequested[DOIP_CONNECTION_TOTAL] = {FALSE,FALSE,FALSE};
VAR(DoIP_UdpTxMgtType_st, DOIP_VAR_NO_INIT) DoIP_UdpTxMgtList[DOIP_UDP_TX_MGT_LIST_SIZE];
VAR(uint8, DOIP_VAR_NO_INIT) DoIP_Con2IpAddrState[DOIP_CONNECTION_TOTAL];
VAR(DoIP_IpAddrReqStateType, DOIP_VAR_NO_INIT) DoIP_LocalAddrIdx2IpAddrReqState[DOIP_LOCAL_ADDR_TOTAL];
VAR(DoIP_IpAddrAssignmentType, DOIP_VAR_NO_INIT) DoIP_LocalAddrIdx2AssignmentType[DOIP_LOCAL_ADDR_TOTAL];
VAR(PduIdType, DOIP_VAR_NO_INIT) DoIP_TcpCon2RxChannelActive[DOIP_CONNECTION_TCP_TOTAL];


VAR(uint8, DOIP_VAR_NO_INIT) DiagAckNackBufOfTester0E00[10];
VAR(uint8, DOIP_VAR_NO_INIT) DiagAckNackBufOfTester0E01[10];
VAR(uint8, DOIP_VAR_NO_INIT) DiagAckNackBufOfTester0E80[10];

PduInfoType lastMsgInfo;

#define DOIP_STOP_SEC_CONFIG_DATA
#include "../../include/DoIP/DoIP_MemMap.h"

CONST(uint8, DOIP_CONFIG_DATA) DoIP_Eid[6] = {0x72,0x34,0x56,0x78,0x9A,0xBC};
CONST(uint8, DOIP_CONFIG_DATA) DoIP_Gid[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
CONST(uint8, DOIP_CONFIG_DATA) DoIP_Channel2ApiType[DOIP_CHANNELS_TOTAL] = //0x00Indicates that all diagnostic messages can be delivered
{
	0x00u, 
	0x00u, 
};
CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Channel2PduRRxPduId[DOIP_CHANNELS_TOTAL + 1U] =
{
	0xFFFF
};
CONST(uint16, DOIP_CONFIG_DATA) DoIP_Channel2EcuAddr[DOIP_CHANNELS_TOTAL + 1U] =
{
	0x1001, 
	0x1FFF, 
	0xFFFF
};
CONST(uint16, DOIP_CONFIG_DATA) DoIP_Channel2SourceAddr[DOIP_CHANNELS_TOTAL] =
{
	0x0E00, 
	0x0E01, 
};
CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Channel2PduRTxConfPduId[DOIP_CHANNELS_TOTAL] = 
{
	0xFFF0U
};
CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Channel2DefaultTcpCon[DOIP_CHANNELS_TOTAL] = 
{
	0xFFFFu, 
	0xFFFFu, 
};
CONST(DoIP_RoutingActivationType_st, DOIP_CONFIG_DATA) DoIP_RoutingActivations[DOIP_ACTIVE_CONNECTION_SIZE + 1U] =
{
	{AuthCallback0_RoutingActivation,ConfirmCallback0_RoutingActivation,1U,0U,0U,0U,0U,0U,DoIP_RouteActive2TargetAddr00},
	{AuthCallback1_RoutingActivation,ConfirmCallback1_RoutingActivation,1U,0U,0U,0U,0U,0x0EU,DoIP_RouteActive2TargetAddr01},
	{NULL_PTR, NULL_PTR, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, NULL_PTR}
};
CONST(uint8, DOIP_CONFIG_DATA) DoIP_RoutActToTest0E00[2] =
{	0, 1,
};
CONST(uint8, DOIP_CONFIG_DATA) DoIP_RoutActToTest0E01[2] =
{	0, 1,
};
CONST(uint8, DOIP_CONFIG_DATA) DoIP_RoutActToTest0E80[2] =
{	0, 1,
};
CONST(DoIP_TesterType_st, DOIP_CONFIG_DATA) DoIP_Tester[DOIP_TESTER_TOTAL + 1U] =
{
{DoIP_RoutActToTest0E00,
#if(STD_ON == DOIP_NACK_APPEND_REQ)
	DiagAckNackBufOfTester0E00,
	10U,
#endif /* (STD_ON == DOIP_NACK_APPEND_REQ) */
	0x0E00,2,FALSE},
{DoIP_RoutActToTest0E01,
#if(STD_ON == DOIP_NACK_APPEND_REQ)
	DiagAckNackBufOfTester0E01,
	10U,
#endif /* (STD_ON == DOIP_NACK_APPEND_REQ) */
	0x0E01,2,FALSE},
{DoIP_RoutActToTest0E80,
#if(STD_ON == DOIP_NACK_APPEND_REQ)
	DiagAckNackBufOfTester0E80,
	10U,
#endif /* (STD_ON == DOIP_NACK_APPEND_REQ) */
	0x0E80,2,FALSE},
{NULL_PTR,
#if(STD_ON == DOIP_NACK_APPEND_REQ)
    NULL_PTR,
    0U,
#endif /* (STD_ON == DOIP_NACK_APPEND_REQ) */
    0xFFFF, 0, FALSE}
};
CONST(uint8, DOIP_CONFIG_DATA) DoIP_Con2LocalAddrIdx[DOIP_CONNECTION_TOTAL] =
{
};
CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Con2SoAdTxPduId[DOIP_CONNECTION_TOTAL + 1U] =
{
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFFFU
};
CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Con2SoAdTxPduIdOfAnnou[DOIP_CONNECTION_UDP_ANNC_TOTAL + 1U] =
{
  0xFFFFU
};
CONST(PduIdType, DOIP_CONFIG_DATA) DoIP_Con2SoAdRxCancelPduId[DOIP_CONNECTION_TCP_TOTAL + 1U] =
{
  0xFFU,
  0xFFFFU
};
CONST(boolean, DOIP_CONFIG_DATA) DoIPRequestAddressAssignment[DOIP_CONNECTION_TOTAL] =
{
  TRUE,
  TRUE,
  TRUE
};
CONST(boolean, DOIP_CONFIG_DATA) DoIP_IsTcpClientConnection[DOIP_CONNECTION_TCP_TOTAL] = 
{
	TRUE
};

#define DOIP_STOP_SEC_CONFIG_DATA
/*
********************************************************************************
* Function Name: DoIP_Memset
*
* Explanation: To initial the data.
*
* param: destPtr: The destination of the data.
*             val: Data value.
*             cnt: The length of the data
*
* retval: None
********************************************************************************
*/
FUNC(void, DOIP_CODE) DoIP_Memset(P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) destPtr, uint8 val, uint32 cnt)
{
    uint32 dataIndex = 0;
    uint8 *beginPtr = (uint8*)destPtr;
    /* Check the parameter. */
    if( (NULL_PTR != destPtr) && (0 != cnt) )
    {
        /* Check the number of the cycle. */
        for( ; dataIndex != cnt; dataIndex++ )
        {
            *(beginPtr + dataIndex) = val; /* Set data. */
        }
    }
}

FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetVinFun(P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) vinBuf)
{
   Std_ReturnType retVal = E_OK;

   //retVal = Dcm_GetVin(vinBuf);
   DoIP_Memset(vinBuf, DOIP_VIN_INV_PATTERN, 17U);
//    if(E_NOT_OK == retVal)
//    {
       
//    }
   return retVal;
}
FUNC(Std_ReturnType, DOIP_CODE) CallbackGetFurtherActionByte(DoIP_FurtherActionByteType* FurtherActionByte)
{
    Std_ReturnType retVal = 0x01U;
    if( NULL_PTR != FurtherActionByte )
    {
        *FurtherActionByte = 0x11U;
        retVal = 0x00U;
    }
    return retVal;
}
FUNC(Std_ReturnType, DOIP_CODE) AuthCallback0_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Authentified, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) AuthenticationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationResData)
{
    Std_ReturnType retVal = E_OK;
    *Authentified = TRUE;
    return retVal;
}
FUNC(Std_ReturnType, DOIP_CODE) AuthCallback1_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Authentified, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) AuthenticationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationResData)
{
    Std_ReturnType retVal = E_OK;
    *Authentified = TRUE;
    return retVal;
}
FUNC(Std_ReturnType, DOIP_CODE) ConfirmCallback0_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Confirmed, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) ConfirmationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) ConfirmationResData)
{
    Std_ReturnType retVal = E_OK;
    *Confirmed = TRUE;
    return retVal;
}
FUNC(Std_ReturnType, DOIP_CODE) ConfirmCallback1_RoutingActivation(P2VAR(boolean, AUTOMATIC, DOIP_APPL_DATA) Confirmed, P2CONST(uint8, AUTOMATIC, DOIP_APPL_CONST) ConfirmationReqData, P2VAR(uint8, AUTOMATIC, DOIP_APPL_DATA) ConfirmationResData)
{
    Std_ReturnType retVal = E_OK;
    *Confirmed = TRUE;
    return retVal;
}
