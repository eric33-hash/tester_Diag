/*
********************************************************************************
*
*  File name:   Dcm_Lcfg.c
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : TanLixiang/2018.11.14
* Change: Neusar
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date : TanLixiang/2019.05.13
* Change: Modify
* Cause:
*(1)Modify file structure.
********************************************************************************
* Version: 1.2
* Author/Date : Songqw/2019.09.02
* Change: Revert 10 service about the 82 subfunction
* Cause: bugfix
********************************************************************************
* Version: 1.3
* Author/Date : Songqw/2019.11.11
* Change: Add the address type to the Dcm_DslProtocol structure.
* Cause: update
********************************************************************************
* Version: 1.4
* Author/Date : Liuziyang/2019.11.21
* Change: The format of code and comment.
* Cause: Modify the code according to the coding specification.
********************************************************************************
* Version: 1.5
* Author/Date : songqingwei/2020.01.22
* Change: Modify the Dcm_22_2E_ServiceInfo struction.
* Cause: How to association with Nvm about the DID buffer point.
********************************************************************************
* Version: 3.0
* Author/Date: ZhuCY/2021.10.28
* Change: Modify header file.
* Cause: Optimization.
********************************************************************************
* Version: 3.1
* Author/Date: LQiao/2023.02.06
* Change: Add Struct. Add 38 service. 
* Cause: Optimization
********************************************************************************
*/
/*
********************************************************************************
*    Include
********************************************************************************
*/
#include "eth/include/Dcm/Dcm.h"
#include "eth/include/Dem/Dem.h"
// #include "CanIf.h"
#include "eth/include/Dcm/Dcm_Callback.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define DCM_START_SEC_VAR_INIT
// #include "Dcm_MemMap.h"

VAR(uint8, DCM_VAR_INIT) Dcm_DslBuffer[DCM_DSL_BUFFERLEN] = {0U};

VAR(uint32, DCM_VAR_INIT) Dcm_ProgrammingLength = DCM_ZERO;

 
VAR(Dcm_ReadBlockId_st, DCM_VAR_INIT) Dcm_ReadBlockId[DCM_READ_BLOCK_NUM + 1] =
{
    {DCM_INVALID_BLOCKID, DCM_E_NOT_OK, DCM_E_NOT_OK, NULL_PTR, NULL_PTR, 0}
};

 
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )

VAR(uint8, DCM_VAR_INIT) Dcm_DidF187Buffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF18ABuffer[10] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF197Buffer[10] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF189Buffer[21] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF089Buffer[21] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF193Buffer[8] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF195Buffer[8] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF18CBuffer[14] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF180Buffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF190Buffer[17] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF010Buffer[8] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF15ABuffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF15BBuffer[10] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidCE00Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidCF00Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidCF01Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidCF02Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidCF03Buffer[3] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidCF04Buffer[3] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0010Buffer[1] = {0x00U};
VAR(uint16, DCM_VAR_INIT) Dcm_22_DidList[DCM_22_MAX_DID_LIST_NUM] = {0};
VAR(uint16, DCM_VAR_INIT) Dcm_22_DidResLen[DCM_22_MAX_DID_LIST_NUM] = {0};
#endif

 
#if (STD_ON == DCM_SERVICE_27_ENABLED)
VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_Data[DCM_27_SUB_NUM + 1U] = {{0x00U}};
VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_INIT_Data[DCM_27_SUB_NUM + 1U] = {{0x00U}};
VAR(uint32, DCM_VAR_INIT) Dcm_27_TimerEngine[DCM_27_SUB_NUM + 1U] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_security_key[DCM_27_MAX_SEED_LENGTH + 1U] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_security_seed[DCM_27_MAX_SEED_LENGTH + 1U] = {0x00U};
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */


#if (STD_ON == DCM_SERVICE_86_ENABLED)
VAR(Dcm_86_NvMEventInfo_st, DCM_VAR_INIT) Dcm_86_NvMInfo = {DCM_ZERO};
#endif/* STD_ON == DCM_SERVICE_86_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
VAR(uint8, DCM_VAR_INIT) Dcm_AuthenticationState[DCM_29_AUT_ROLE_NUM + 1U][DCM_29_AUT_CONN_NUM + 1U] = {{FALSE}};
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#define DCM_STOP_SEC_VAR_INIT
#include "eth/include/Dcm/Dcm_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define DCM_START_SEC_CONFIG_DATA
#include "eth/include/Dcm/Dcm_MemMap.h"

 
CONST(Dcm_ServiceTableType_st, DCM_CONFIG_DATA) Dcm_DspServiceInfoTable[DCM_NUM_SERVICES + 1] =
{
	{0x10U,	DCM_SERVICE_UDS,	2U,	{0x00000001U, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_10_CheckRule,	Dcm_10_Process,	Dcm_10_Init,	Dcm_10_PostProcess},
	{0x11U,	DCM_SERVICE_UDS,	2U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_11_CheckRule,	Dcm_11_Process,	Dcm_11_Init,	Dcm_11_PostProcess},
	{0x27U,	DCM_SERVICE_UDS,	2U,	{0x00000001U, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_27_CheckRule,	Dcm_27_Process,	Dcm_27_Init,	Dcm_27_PostProcess},
	{0x28U,	DCM_SERVICE_UDS,	3U,	{0x00000001U, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_28_CheckRule,	Dcm_28_Process,	Dcm_28_Init,	Dcm_28_PostProcess},
	{0x3EU,	DCM_SERVICE_UDS,	2U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_3E_CheckRule,	Dcm_3E_Process,	Dcm_3E_Init,	Dcm_3E_PostProcess},
	{0x85U,	DCM_SERVICE_UDS,	2U,	{0x00000001U, 0x00000001U},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_85_CheckRule,	Dcm_85_Process,	Dcm_85_Init,	Dcm_85_PostProcess},
	{0x22U,	DCM_SERVICE_UDS,	3U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_22_CheckRule,	Dcm_22_Process,	Dcm_22_Init,	Dcm_22_PostProcess},
	{0x2EU,	DCM_SERVICE_UDS,	4U,	{0x00000001U, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_2E_CheckRule,	Dcm_2E_Process,	Dcm_2E_Init,	Dcm_2E_PostProcess},
	{0x2FU,	DCM_SERVICE_UDS,	4U,	{0x00000001U, 0x00000001U},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_2F_CheckRule,	Dcm_2F_Process,	Dcm_2F_Init,	Dcm_2F_PostProcess},
	{0x29U,	DCM_SERVICE_UDS,	1U,	{0x00000001U, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_29_CheckRule,	Dcm_29_Process,	Dcm_29_Init,	Dcm_29_PostProcess},
	{0x31U,	DCM_SERVICE_UDS,	4U,	{0x00000001U, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_31_CheckRule,	Dcm_31_Process,	Dcm_31_Init,	Dcm_31_PostProcess},
	{0x19U,	DCM_SERVICE_UDS,	2U,	{0x00000002U, 0x00000001U},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_19_CheckRule,	Dcm_19_Process,	Dcm_19_Init,	Dcm_19_PostProcess},
	{0x14U,	DCM_SERVICE_UDS,	4U,	{0x00000002U, 0x00000001U},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_14_CheckRule,	Dcm_14_Process,	Dcm_14_Init,	Dcm_14_PostProcess},
	{0x34U,	DCM_SERVICE_UDS,	5U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_34_CheckRule,	Dcm_34_Process,	Dcm_34_Init,	Dcm_34_PostProcess},
	{0x36U,	DCM_SERVICE_UDS,	2U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_36_CheckRule,	Dcm_36_Process,	Dcm_36_Init,	Dcm_36_PostProcess},
	{0x37U,	DCM_SERVICE_UDS,	1U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_37_CheckRule,	Dcm_37_Process,	Dcm_37_Init,	Dcm_37_PostProcess},
    {0xFFU, 0xFFU,              1U, {0x7FFFFFFFU, 0x7FFFFFFFU}, 0xFFU,          {0x00U, NULL_PTR},	NULL_PTR,   NULL_PTR,       NULL_PTR,       NULL_PTR          }
};

CONST(Dcm_DSDInfo_st, DCM_CONFIG_DATA) Dcm_gcaDSDInfo =
{
    Dcm_DspServiceInfoTable
};

 
CONST(Dcm_DslProtocol_st, DCM_CONFIG_DATA) Dcm_DslProtocol[DCM_DSL_PROTOCOL_NUM + 1] =
{
	{0U,	0U,	DCM_FUN,	DCM_UDS_ON_CAN,	0U,	0xFFFFU,	0x7DFU, FALSE, 0x0U},
	{1U,	0U,	DCM_PHY,	DCM_UDS_ON_CAN,	0U,	0xFFFFU,	0x739U, FALSE, 0x0U},
	{2U,	5U,	DCM_FUN,	DCM_UDS_ON_CAN,	1U,	0xFFFFU,	0x7DFU, FALSE, 0x1U},
	{3U,	5U,	DCM_PHY,	DCM_UDS_ON_CAN,	1U,	0xFFFFU,	0x739U, FALSE, 0x1U},
    {0xFFFFU, 0xFFFFU, 0xFFU, DCM_NO_ACTIVE_PROTOCOL, 0xFFU, 0xFFFFU, 0xFFFFFFFFU, FALSE, 0xFFU}
};

CONST(uint8, DCM_CONFIG_DATA) Dcm_CfgNetConnComMChannelMap[DCM_DSL_CHANNEL_NUM + 1] =
{
	0x00U,
	0x01U,
    0xFFU
};

#if ( STD_ON == DCM_SERVICE_01_ENABLED )	
	
CONST(Dcm_01_PidType_st, DCM_CONFIG_DATA) Dcm_01_SupportPID[DCM_01_SUPPRORTPID + 1] =
{
	{0xFFU, 0x00U, NULL_PTR, NULL_PTR,},
};
	
CONST(Dcm_01_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_01_PIDInfo[DCM_01_SUBID + 1] =
{
	{0x00U, DCM_01_MRESQ, NULL_PTR, 0x00000000U},
	{0x20U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x40U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x60U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x80U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xA0U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xC0U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xE0U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xFFU, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
};

CONST(Dcm_01_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_01_Dispatcher =
{
    Dcm_01_PIDInfo,
    Dcm_01_SupportPID,
};
#endif/* DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
	
CONST(Dcm_02_PidType_st, DCM_CONFIG_DATA) Dcm_02_SupportPID[DCM_02_SUPPRORTPID + 1] =
{
	{0xFFU, 0x00U, NULL_PTR, NULL_PTR, 0U}
};
	
CONST(Dcm_02_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_02_PIDInfo[DCM_02_SUBID + 1] =
{
	{0x00U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x20U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x40U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x60U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x80U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xA0U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xFFU, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
};

CONST(Dcm_02_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_02_Dispatcher =
{
    Dcm_02_PIDInfo,
    Dcm_02_SupportPID,
    Dcm_02_PidList

};
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
	
CONST(Dcm_09_PidType_st, DCM_CONFIG_DATA) Dcm_09_SupportPID[DCM_09_SUPPRORTPID + 1] =
{
	{0xFFU, 0x00U, NULL_PTR, NULL_PTR},
};
	
CONST(Dcm_09_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_09_PIDInfo[DCM_09_SUBID + 1] =
{
	{0x00U, DCM_09_MRESQ, NULL_PTR, 0x00000000U},
	{0x20U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x40U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x60U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x80U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xA0U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xC0U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xE0U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xFFU, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
};

CONST(Dcm_09_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_09_Dispatcher =
{
    Dcm_09_PIDInfo,
    Dcm_09_SupportPID,
};
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

 
#if (STD_ON == DCM_SERVICE_10_ENABLED)
CONST(Dcm_10_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_10_ServiceInfo[DCM_10_SUBID + 1] =
{
	{0x01U,	DCM_PHY_FUN,	{0x00000001U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_01, DCM_P2EX_TIME_01},	DCM_NO_BOOT,	DCM_SESSION_DEFAULT_LEVEL,	NULL_PTR},
	{0x81U,	DCM_PHY_FUN,	{0x00000001U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_01, DCM_P2EX_TIME_01},	DCM_NO_BOOT,	DCM_SESSION_DEFAULT_LEVEL,	NULL_PTR},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},   {0xFFU, 0xFFU},	DCM_NO_BOOT,	DCM_SESSION_DEFAULT_LEVEL,	NULL_PTR}
};
CONST(Dcm_10_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_10_Dispatcher =
{
	Dcm_10_ServiceInfo
};
#endif /* STD_ON == DCM_SERVICE_10_ENABLED */

 
#if (STD_ON == DCM_SERVICE_11_ENABLED)
CONST(Dcm_11_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_11_ServiceInfo[DCM_11_SUBID + 1] = 
{
	{0x01U,	DCM_PHY_FUN,	DCM_BEFORE_RESET,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check11SubResetFunc},
	{0x03U,	DCM_PHY_FUN,	DCM_BEFORE_RESET,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check11SubResetFunc},
	{0xFFU,	DCM_PHY_FUN,    DCM_BEFORE_RESET,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	NULL_PTR}
};
CONST(Dcm_11_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_11_Dispatcher =
{
	Dcm_11_ServiceInfo
};
VAR(uint8, DCM_VAR_INIT) Dcm_11_NvMBuf[DCM_FOUR] = {DCM_ZERO};
#endif /* STD_ON == DCM_SERVICE_11_ENABLED */

 
#if (STD_ON == DCM_SERVICE_14_ENABLED)
CONST(Dcm_14_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_14_ServiceInfo[DCM_14_SUBID_NUM + 1] =
{
	{{0x7FFFFFFFU, 0x7FFFFFFFU},	Dcm_14_CheckRuleFunc,	Dcm_ClearCallBackFunc}
};
CONST(Dcm_g14DispatherInfo_st, DCM_CONFIG_DATA) Dcm_14_Dispatcher =
{
	Dcm_14_ServiceInfo,
};
#endif /* STD_ON == DCM_SERVICE_14_ENABLED */

 
#if (STD_ON == DCM_SERVICE_19_ENABLED)
CONST(Dcm_19_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_19_ServiceInfo[DCM_19_SUBIDNUM + 1] = 
{
	{0x01U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x00000002U, 0x00000001U},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1901_Process,	NULL_PTR},
	{0x02U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x00000002U, 0x00000001U},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1902_Process,	NULL_PTR},
	{0x04U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x00000002U, 0x00000001U},	{0x0U, NULL_PTR},	0x04U,	Dcm_Dsp_1904_Process,	NULL_PTR},
	{0x06U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x00000002U, 0x00000001U},	{0x0U, NULL_PTR},	0x04U,	Dcm_Dsp_1906_Process,	NULL_PTR},
	{0x0AU,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x00000002U, 0x00000001U},	{0x0U, NULL_PTR},	0x00U,	Dcm_Dsp_190A_Process,	NULL_PTR},
	{0xFFU,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,		{0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR},   0x00U,	NULL_PTR,	NULL_PTR},
};
CONST(Dcm_19_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_19_Dispatcher = 
{
	Dcm_19_ServiceInfo,
};
#endif /* STD_ON == DCM_SERVICE_19_ENABLED */

 
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )
CONST(Dcm_22_2E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_22_2E_ServiceInfo[DCM_NUM_DIDS + 1] =
{
	{0xF187U, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF187Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000001U, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F187_ReadData, NULL_PTR}, Dcm_DidMgr_F187_ReadDataLength, {Dcm_DidMgr_F187_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF18AU, TRUE, 0x0AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF18ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F18A_ReadData, NULL_PTR}, Dcm_DidMgr_F18A_ReadDataLength, {Dcm_DidMgr_F18A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF197U, TRUE, 0x0AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF197Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F197_ReadData, NULL_PTR}, Dcm_DidMgr_F197_ReadDataLength, {Dcm_DidMgr_F197_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF189U, TRUE, 0x15U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF189Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F189_ReadData, NULL_PTR}, Dcm_DidMgr_F189_ReadDataLength, {Dcm_DidMgr_F189_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF089U, TRUE, 0x15U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF089Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F089_ReadData, NULL_PTR}, Dcm_DidMgr_F089_ReadDataLength, {Dcm_DidMgr_F089_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF193U, TRUE, 0x08U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF193Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F193_ReadData, NULL_PTR}, Dcm_DidMgr_F193_ReadDataLength, {Dcm_DidMgr_F193_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF195U, TRUE, 0x08U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF195Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F195_ReadData, NULL_PTR}, Dcm_DidMgr_F195_ReadDataLength, {Dcm_DidMgr_F195_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF18CU, TRUE, 0x0EU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF18CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F18C_ReadData, NULL_PTR}, Dcm_DidMgr_F18C_ReadDataLength, {Dcm_DidMgr_F18C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF180U, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF180Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F180_ReadData, NULL_PTR}, Dcm_DidMgr_F180_ReadDataLength, {Dcm_DidMgr_F180_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF190U, TRUE, 0x11U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF190Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x00000001U, 0x00000001U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F190_ReadData, NULL_PTR}, Dcm_DidMgr_F190_ReadDataLength, {Dcm_DidMgr_F190_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_F190_WriteData, NULL_PTR}, Dcm_DidMgr_F190_ConditionCheckWrite, NULL_PTR},
	{0xF010U, TRUE, 0x08U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF010Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x00000001U, 0x00000001U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F010_ReadData, NULL_PTR}, Dcm_DidMgr_F010_ReadDataLength, {Dcm_DidMgr_F010_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_F010_WriteData, NULL_PTR}, Dcm_DidMgr_F010_ConditionCheckWrite, NULL_PTR},
	{0xF15AU, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF15ABuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU, 0x00000001U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F15A_ReadData, NULL_PTR}, Dcm_DidMgr_F15A_ReadDataLength, {Dcm_DidMgr_F15A_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_F15A_WriteData, NULL_PTR}, Dcm_DidMgr_F15A_ConditionCheckWrite, NULL_PTR},
	{0xF15BU, TRUE, 0x0AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF15BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F15B_ReadData, NULL_PTR}, Dcm_DidMgr_F15B_ReadDataLength, {Dcm_DidMgr_F15B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xCE00U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidCE00Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_CE00_ReadData, NULL_PTR}, Dcm_DidMgr_CE00_ReadDataLength, {Dcm_DidMgr_CE00_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xCF00U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidCF00Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_CF00_ReadData, NULL_PTR}, Dcm_DidMgr_CF00_ReadDataLength, {Dcm_DidMgr_CF00_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xCF01U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidCF01Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_CF01_ReadData, NULL_PTR}, Dcm_DidMgr_CF01_ReadDataLength, {Dcm_DidMgr_CF01_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xCF02U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidCF02Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_CF02_ReadData, NULL_PTR}, Dcm_DidMgr_CF02_ReadDataLength, {Dcm_DidMgr_CF02_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xCF03U, TRUE, 0x03U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidCF03Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_CF03_ReadData, NULL_PTR}, Dcm_DidMgr_CF03_ReadDataLength, {Dcm_DidMgr_CF03_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xCF04U, TRUE, 0x03U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidCF04Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_CF04_ReadData, NULL_PTR}, Dcm_DidMgr_CF04_ReadDataLength, {Dcm_DidMgr_CF04_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0010U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0010Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000002U, 0x00000001U}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0010_ReadData, NULL_PTR}, Dcm_DidMgr_0010_ReadDataLength, {Dcm_DidMgr_0010_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xFFFFU, FALSE, 0xFFU, DCM_INVALID_BLOCKID, NULL_PTR, NULL_PTR, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, {NULL_PTR, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR}
};
CONST(Dcm_22_2E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_22_2E_Dispatcher =
{
	Dcm_22_DidList,
	Dcm_22_DidResLen,
	Dcm_22_2E_ServiceInfo,
};
#endif

 
#if (STD_ON == DCM_SERVICE_27_ENABLED)
CONST(Dcm_27_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_27_ServiceInfo[DCM_27_SUB_NUM + 1] =
{
	{0x01U,	DCM_PHY_FUN,	{0x00000001U, 0x7FFFFFFFU},	{0x7FFFFFFFU,0x7FFFFFFFU},	{0x0U, NULL_PTR},	DCM_2701_ATTCOUNTER,	DCM_2701_MAX_SEED_LENGTH,	DCM_2701_MAX_KEY_LENGTH,	DCM_2701_ATTDELAY,	Dcm_SecurityAccess_Level_01_GetSeed,	Dcm_SecurityAccess_Level_01_CompareKey,	Dcm_SecurityAccess_Level_01_CheckRule,	&Dcm_27_Security_Data[0],	Dcm_SecurityAccess_Level_01_GetAttemptCounter,	Dcm_SecurityAccess_Level_01_SetAttemptCounter},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR},	0xFFU,	0xFFU,	0xFFU,	0xFFU,	NULL_PTR,	NULL_PTR,	NULL_PTR,   NULL_PTR,   NULL_PTR,   NULL_PTR}
};
CONST(Dcm_27_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_27_Dispatcher =
{
	Dcm_27_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

 
#if (STD_ON == DCM_SERVICE_28_ENABLED)
CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ControlState[DCM_28_CONTROL_STATE_NUM] = 
{
	0x01U,
	0x02U,
	0x03U
};
CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ChannelId[DCM_28_CHANNLE_NUM + 1U] = 
{
	0xFFU
};
CONST(Dcm_28_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_28_ServiceInfoTable[DCM_28_SUBID_NUM + 1] = 
{
	{0x00U,	DCM_PHY_FUN,	{0x00000001U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check28SubComMFunc},
	{0x03U,	DCM_PHY_FUN,	{0x00000001U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check28SubComMFunc},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR},	NULL_PTR}
};
CONST(Dcm_28_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_28_Dispatcher =
{
	Dcm_28_ControlState,
	Dcm_28_ServiceInfoTable,
};
#endif/* STD_ON == DCM_SERVICE_28_ENABLED */

 
#if (STD_ON == DCM_SERVICE_2F_ENABLED)
CONST(Dcm_2F_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2F_ServiceInfo[DCM_2F_MAX_SUB_DID_NUM + 1] =
{
	{0x0010U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x00000001U, 0x00000001U},	{0x0U, NULL_PTR},	{0U, 1U,0U},	InputOutput_0010_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_0010_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0xFFFFU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x7FFFFFFFU, 0x7FFFFFFFU},    {0x0U, NULL_PTR},   {0U, 0U, 0U},	NULL_PTR,	NULL_PTR,	NULL_PTR,	NULL_PTR,	NULL_PTR}
};
CONST(Dcm_2F_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2F_Dispatcher =
{
	Dcm_2F_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */

 
#if (STD_ON == DCM_SERVICE_31_ENABLED)
CONST(Dcm_31_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_31_ServiceInfo[DCM_31_SUBID_NUM + 1] =
{
	{0x0203U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x00000001U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0U, 5U},	{0U, 0U},	{0U, 0U},	Dcm_31_0x0203_Start,	NULL_PTR,	NULL_PTR,	NULL_PTR},
	{0xFF00U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x7FFFFFFFU, 0x00000001U},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{9U, 5U},	{0U, 0U},	{0U, 0U},	Dcm_31_0xFF00_Start,	NULL_PTR,	NULL_PTR,	NULL_PTR},
	{0x0202U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{4U, 1U},	{0U, 0U},	{0U, 0U},	Dcm_31_0x0202_Start,	NULL_PTR,	NULL_PTR,	NULL_PTR},
	{0xFF01U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x7FFFFFFFU, 0x00000001U},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0U, 5U},	{0U, 0U},	{0U, 0U},	Dcm_31_0xFF01_Start,	NULL_PTR,	NULL_PTR,	NULL_PTR},
	{0x6A00U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x00000001U, 0x00000001U},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{3U, 5U},	{0U, 0U},	{0U, 0U},	Dcm_31_0x6A00_Start,	Dcm_31_0x6A00_Stop,	NULL_PTR,	NULL_PTR},
	{0xFFFFU,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,		{0x7FFFFFFFU, 0x7FFFFFFFU}, 	{0x0U, NULL_PTR}, 	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},  {0U, 0U},	{0U, 0U},	{0U, 0U},	NULL_PTR,	NULL_PTR,	NULL_PTR,	NULL_PTR}
};
CONST(Dcm_31_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_31_Dispatcher =
{
	Dcm_31_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_31_ENABLED */

 
#if (STD_ON == DCM_SERVICE_3E_ENABLED)
CONST(Dcm_3E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_3E_ServiceInfo[DCM_3E_SUBID + 1] =
{
	{0x00U,	DCM_PHY_FUN,	1U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	NULL_PTR},
	{0xFFU,	DCM_PHY_FUN,	1U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	NULL_PTR}
};
CONST(Dcm_3E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_3E_Dispatcher =
{
	Dcm_3E_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_3E_ENABLED */

 
#if (STD_ON == DCM_SERVICE_85_ENABLED)
CONST(Dcm_85_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_85_ServiceInfo[DCM_85_SUBID_NUM + 1] =
{
	{0x01U,	DCM_PHY_FUN,	{0x00000001U, 0x00000001U},	{0x0U, NULL_PTR},	Dcm_Check85SubDtcSettingFunc},
	{0x02U,	DCM_PHY_FUN,	{0x00000001U, 0x00000001U},	{0x0U, NULL_PTR},	Dcm_Check85SubDtcSettingFunc},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},   NULL_PTR}
};
CONST(Dcm_85_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_85_Dispatcher =
{
	Dcm_85_ServiceInfo
};
#endif/* STD_ON == DCM_SERVICE_85_ENABLED */

CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspReadMemoryInfo[DCM_DSP_READMEMORY_NUM + 1] = 
{
	{ 0U, 0U, {0x7FFFFFFFU, 0x7FFFFFFFU}, NULL_PTR }
};

CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspWriteMemoryInfo[DCM_DSP_WRITEMEMORY_NUM + 1] = 
{
	{ 0U, 0xFFFFFFFFU, {0x7FFFFFFFU, 0x7FFFFFFFU}, NULL_PTR }
};

#if (STD_ON == DCM_SERVICE_2A_ENABLED)
	
CONST(Dcm_2A_Channel_st, DCM_CONFIG_DATA) Dcm_2A_Channel[DCM_2A_TX_CHANNEL_NUM + 1U] = 
{
	{
		0xFFFFU,
		0xFFFFU,
	}
};


	
CONST(Dcm_2A_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2A_ServiceInfo[DCM_2A_NUM_DIDS + 1U] = 
{
	{
		0xFFFFU,
		FALSE,
		0xFFU,
		USE_DATA_SYNCH_FNC,
		{0x7FFFFFFFU, 0x7FFFFFFFU},
		{0x0U, NULL_PTR},
		{NULL_PTR, NULL_PTR},
		NULL_PTR,
		{NULL_PTR, NULL_PTR},
		NULL_PTR
	}
};

CONST(Dcm_2A_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2A_Dispatcher =
{
     Dcm_2A_ServiceInfo
};
#endif/* STD_ON == DCM_SERVICE_2A_ENABLED */

 
#if (STD_ON == DCM_SERVICE_2C_ENABLED)
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */
#if (STD_ON == DCM_SERVICE_2C_ENABLED)
CONST(uint8, DCM_CONFIG_DATA) Dcm_2C_SubFunc[DCM_2C_SUB_NUM_DIDS] =
{
	0x01U,
	0x02U,
	0x03U
};
CONST(Dcm_2C_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2C_ServiceInfo[DCM_2C_NUM_DIDS + 1U] ={
	{0xFFFFU, 1U, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR},   NULL_PTR, NULL_PTR}
};
CONST(Dcm_2C_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2C_Dispatcher =
{
	Dcm_2C_SubFunc,
	Dcm_2C_ServiceInfo
};
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
CONST(Dcm_29_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_29_ServiceInfo[DCM_29_SUBID_NUM + 1] =
{

    {
      /* Dcm_ID     = */ 0x00U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 1U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2900_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub00_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x01U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 4U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2901_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub01_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x02U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 4U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2902_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub02_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x03U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 3U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2903_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub03_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x04U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 1U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2904_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub04_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x05U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 1U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2905_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub05_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x06U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 1U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2906_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub06_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x07U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 1U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2907_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub07_CheckRuleFunc
    },
    {
      /* Dcm_ID     = */ 0x08U,
      /* Dcm_Used   = */ TRUE,
      /* Dcm_Length = */ 1U,
      /* Dcm_Filter = */ {0x00000001U, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ Dcm_Dsp_2908_Process,
      /* Dcm_CheckRuleRef = */ Dcm_29_Sub08_CheckRuleFunc
    },

    {
      /* Dcm_ID     = */ 0xFFU,
      /* Dcm_Used   = */ FALSE,
      /* Dcm_Length = */ 0U,
      /* Dcm_Filter = */ {0x7FFFFFFFU, 0x7FFFFFFFU},
      /* (*Dcm_ServiceProcessorType_p)(void); = */ NULL_PTR,
      /* Dcm_CheckRuleRef = */ NULL_PTR
    }
};

CONST(Dcm_29_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_29_Dispatcher =
{
     Dcm_29_ServiceInfo
};

CONST(Dcm_29_AutConn_st, DCM_CONFIG_DATA) Dcm_29_AutConn[DCM_29_AUT_CONN_NUM + 1] = 
{
    {
      /*Dcm_CertVerfCallNotifyRef      = */ FALSE,
      /*Dcm_RandSeedCallNotifyRef      = */ FALSE,
      /*Dcm_SignatureGenerateNotifyRef = */ FALSE,
      /*Dcm_SignatureVerifyNotifyRef   = */ FALSE,
      /*Dcm_ClientCertIdx              = */ 0xFFFFU,
      /*Dcm_ConnCertIdx                = */ 0xFFFFU,
      /*Dcm_MainConnIdx                = */ 0xFFFFU,
      /*Dcm_ECUCertKeyElmtIdx          = */ 0xFFFFU,
      /*Dcm_ECUCertIdx                 = */ 0xFFFFU,
      /*Dcm_PblcKeyElmtIdx             = */ 0xFFFFU,
      /*Dcm_RoleElmtIdx                = */ 0xFFFFU,
      /*Dcm_WLDIDElmtIdx               = */ 0xFFFFU,
      /*Dcm_WLMemSlctElmtIdx           = */ 0xFFFFU,
      /*Dcm_WLRIDElmntIdx              = */ 0xFFFFU,
      /*Dcm_WLSerElmntIdx              = */ 0xFFFFU,
      /*Dcm_CertPblcKeyStoreJobIdx     = */ 0xFFFFFFFFU,
      /*Dcm_ClientChlngSignJobIdx      = */ 0xFFFFFFFFU,
      /*Dcm_RandomJobIdx               = */ 0xFFFFFFFFU,
      /*Dcm_VerifyPOWNJobIdx           = */ 0xFFFFFFFFU,
      /*Dcm_CheckRuleRef               = */ NULL_PTR
    }
};
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
CONST(Dcm_38_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_38_ServiceInfo[DCM_38_SUBID_NUM + 1U] =
{
};

CONST(Dcm_38_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_38_Dispatcher =
{
     Dcm_38_ServiceInfo
};
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#define DCM_STOP_SEC_CONFIG_DATA
// #include "Dcm_MemMap.h"

