/*
********************************************************************************
*
*  File name:   Dcm_Callback.c
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
* Author/Date : lqiao/2022.09.06
* Change: 1. DCM_START_SEC_CONFIG_DATA to DCM_START_SEC_CODE
          2. delete DCM_START_SEC_VAR_INIT
* Cause: 1. CCOREDBUG-1113
         2. CCOREDBUG-1115
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
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define DCM_START_SEC_CODE
#include "eth/include/Dcm/Dcm_MemMap.h"


#if (STD_ON == DCM_SERVICE_10_ENABLED)
FUNC(uint8, DCM_CODE) Dcm_Check10SubProgrammingFunc(void)
{
    return DCM_E_OK;
}

FUNC(uint8, DCM_CODE) Dcm_Check10SubextendedFunc(void)
{
    return DCM_E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_Check10WithPara(uint8 Subfunc, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    return DCM_E_OK;
}

/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetProgConditions(Dcm_OpStatusType OpStatus, P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions)
{
    return DCM_E_OK;
}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_10_JumpToBootWithAppResp(void)
{
    while(DCM_ONE);
}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_10_JumpToBootWithBootResp(void)
{
    while(DCM_ONE);
}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_OnChangeParameter(void)
{

}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_10_SessionChangedCallBack(void)
{
}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_SessionChangedMode(uint8 sessionMode)
{
}

#endif/* STD_ON == DCM_SERVICE_10_ENABLED */

#if (STD_ON == DCM_SERVICE_11_ENABLED)
FUNC(uint8, DCM_CODE) Dcm_Check11SubResetFunc(void)
{
    return DCM_E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_Check11WithPara(uint8 Subfunc, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    return DCM_E_OK;
}

FUNC(void, DCM_CODE) Dcm_EcuResetMode(uint8 acRequestedMode)
{
}

#endif /* STD_ON == DCM_SERVICE_11_ENABLED */


#if (STD_ON == DCM_SERVICE_14_ENABLED)

/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(uint8, DCM_CODE) Dcm_14_CheckRuleFunc(void)
{
    uint8 retValue = DCM_E_OK;
    return retValue;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/

/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_ClearCallBackFunc(void)
{
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/

#endif/* STD_ON == DCM_SERVICE_14_ENABLED */


 

 
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F187_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF187U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F187_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF187U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F187_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F187_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18A_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF18AU;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18A_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF18AU;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F18A_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18A_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F197_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF197U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F197_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF197U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F197_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F197_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F189_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF189U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F189_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF189U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F189_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F189_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F089_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF089U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F089_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF089U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F089_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F089_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F193_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF193U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F193_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF193U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F193_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F193_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F195_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF195U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F195_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF195U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F195_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F195_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18C_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF18CU;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18C_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF18CU;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F18C_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18C_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F180_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF180U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F180_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF180U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F180_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F180_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF190U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF190U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F190_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_WriteData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	uint32 index = DCM_NUM_ZERO;
	uint16 did = 0xF190U;
	uint16 length = DCM_NUM_ZERO;
	uint8 ret = DCM_E_OK;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
		return DCM_E_NOT_OK;
	}
	ret = Dcm_DidMgr_F190_ReadDataLength(&length);
	if( DCM_E_OK != ret )
	{
		return ret;
	}
	if( DCM_E_OK == ret )
	{
		Dcm_MemCpy(Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr, Data, length);
	}
	return ret;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	*ErrorCode = DCM_E_OK;
	return *ErrorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF010U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF010U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F010_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_WriteData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	uint32 index = DCM_NUM_ZERO;
	uint16 did = 0xF010U;
	uint16 length = DCM_NUM_ZERO;
	uint8 ret = DCM_E_OK;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
		return DCM_E_NOT_OK;
	}
	ret = Dcm_DidMgr_F010_ReadDataLength(&length);
	if( DCM_E_OK != ret )
	{
		return ret;
	}
	if( DCM_E_OK == ret )
	{
		Dcm_MemCpy(Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr, Data, length);
	}
	return ret;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	uint8 lResult = DCM_E_OK;
	if( DCM_E_OK == *ErrorCode )
	{
		lResult = DCM_E_OK;
	}
	else
	{
		lResult = DCM_E_NOT_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF15AU;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF15AU;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F15A_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_WriteData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	uint32 index = DCM_NUM_ZERO;
	uint16 did = 0xF15AU;
	uint16 length = DCM_NUM_ZERO;
	uint8 ret = DCM_E_OK;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
		return DCM_E_NOT_OK;
	}
	ret = Dcm_DidMgr_F15A_ReadDataLength(&length);
	if( DCM_E_OK != ret )
	{
		return ret;
	}
	if( DCM_E_OK == ret )
	{
		Dcm_MemCpy(Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr, Data, length);
	}
	return ret;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	uint8 lResult = DCM_E_OK;
	if( DCM_E_OK == *ErrorCode )
	{
		lResult = DCM_E_OK;
	}
	else
	{
		lResult = DCM_E_NOT_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15B_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xF15BU;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15B_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xF15BU;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_F15B_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15B_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CE00_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xCE00U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CE00_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xCE00U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_CE00_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CE00_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF00_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xCF00U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF00_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xCF00U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_CF00_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF00_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF01_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xCF01U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF01_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xCF01U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_CF01_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF01_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF02_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xCF02U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF02_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xCF02U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_CF02_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF02_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF03_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xCF03U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF03_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xCF03U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_CF03_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF03_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF04_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0xCF04U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF04_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0xCF04U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_CF04_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF04_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_0010_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 did = 0x0010U;
	uint32 index = DCM_NUM_ZERO;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		*DataLength = Dcm_22_2E_Dispatcher.Dcm_ServiceInfoTable[index].Dcm_Length;
		lResult = DCM_E_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_0010_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	uint8 lResult = DCM_E_NOT_OK;
	uint16 length = DCM_NUM_ZERO;
	uint16 did = 0x0010U;
	uint32 index = DCM_NUM_ZERO;
	uint8 *srcData = NULL_PTR;
	index = Dcm_FindDid(did);
	if( DCM_NUM_DIDS <= index )
	{
		lResult = DCM_E_NOT_OK;
	}
	else
	{
		srcData = Dcm_22_2E_ServiceInfo[index].Dcm_BlockDataPtr;
		lResult = Dcm_DidMgr_0010_ReadDataLength(&length);
		if( DCM_E_OK == lResult )
		{
			Dcm_MemCpy(Data, srcData, length);
		}
	}
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_0010_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	Std_ReturnType lResult = DCM_E_OK;
	*ErrorCode = DCM_E_OK;

	return lResult;
}
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) */

 
#if (STD_ON == DCM_SERVICE_27_ENABLED)
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    uint8 ret = DCM_E_NOT_OK;
    uint8 secLvlIdx = DCM_2701_SCURITYLEVEL_INDEX;
    
    ret = Dcm_GetSeed(secLvlIdx,Dcm_security_seed);
    if( DCM_E_REQUIREDTIMEDELAYNOTEXPIRED == ret )
    {
        *ErrorCode = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
        return DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
    }
    if( DCM_E_OK != ret )
    {
        *ErrorCode = DCM_E_NOT_OK;
        return DCM_E_NOT_OK;
    }
    Dcm_MemCpy(Seed, (const uint8*)Dcm_security_seed, DCM_2701_MAX_SEED_LENGTH);
    /* Calculate the key by the OEM method using the Seed below.
       Using the variable "Dcm_security_key" to store the calculated key value.*/
    

	// calculate the key
	Dcm_MemCpy(Dcm_security_key, (const uint8*)Dcm_security_seed, DCM_2701_MAX_KEY_LENGTH);
    *ErrorCode = DCM_E_OK;
    
    return DCM_E_OK;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_CompareKey(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    uint8 index = DCM_NUM_ZERO;

    if( NULL_PTR == Key )
    {
        return DCM_E_NOT_OK;
    }

    for( ; DCM_2701_MAX_KEY_LENGTH != index; index++ )
    {
        if( Dcm_security_key[index] != Key[index] )   
        {
            *ErrorCode = DCM_E_COMPARE_KEY_FAILED;    

            return DCM_E_COMPARE_KEY_FAILED;          
        }
    }
    *ErrorCode = DCM_E_OK;

    return DCM_E_OK;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_GetAttemptCounter(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) AttemptCounter)
{
    uint8 retVal = DCM_E_OK;
    uint8 secLvlIdx = DCM_2701_SCURITYLEVEL_INDEX;

    if( NULL_PTR == AttemptCounter )
    {
        retVal = DCM_E_NOT_OK;
    }
    else
    {
        /* Get the attempt counter. */
        *AttemptCounter = Dcm_27_Security_Data[secLvlIdx].AttemptCounter;
    }

    return retVal;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_SetAttemptCounter(Dcm_OpStatusType OpStatus, uint8 AttemptCounter)
{
    uint8 secLvlIdx = DCM_2701_SCURITYLEVEL_INDEX;
    uint8 ret = DCM_E_OK;

    Dcm_27_Security_Data[secLvlIdx].AttemptCounter = AttemptCounter;

    return ret;
}
FUNC(uint8, DCM_CODE) Dcm_SecurityAccess_Level_01_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(void, DCM_CODE) Dcm_SecurityAcces_CalcRand(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ranSeed)
{
    uint32 counter = DCM_ZERO;
    uint8 rand[DCM_27_MAX_SEED_LENGTH] = {DCM_ZERO};
    Dcm_MemCpy(ranSeed, (const uint8*)rand, DCM_27_MAX_SEED_LENGTH);
}
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

#if (STD_ON == DCM_SERVICE_28_ENABLED)

FUNC(uint8, DCM_CODE) Dcm_Check28SubComMFunc(void)
{
    return DCM_E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_Check28WithPara(uint8 Subfunc, uint8 Comtype, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    return DCM_E_OK;
}

#endif/* STD_ON == DCM_SERVICE_28_ENABLED */

 
#if (STD_ON == DCM_SERVICE_2F_ENABLED)
FUNC(uint8, DCM_CODE) Dcm_Check2FSubIOFunc(void)
{
    return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) InputOutput_0010_ReturnControlToECU(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) RsepLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	uint8 lResult = DCM_E_OK;
	if( DCM_E_OK == *ErrorCode )
	{
		lResult = DCM_E_OK;
	}
	else
	{
		lResult = DCM_E_NOT_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(uint8, DCM_CODE) InputOutput_0010_ShortTermAdjustment(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, uint16 ReqLength, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) RsepLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	uint8 lResult = DCM_E_OK;
	if( DCM_E_OK == *ErrorCode )
	{
		lResult = DCM_E_OK;
	}
	else
	{
		lResult = DCM_E_NOT_OK;
	}
	return lResult;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */

 
#if (STD_ON == DCM_SERVICE_31_ENABLED)
FUNC(Std_ReturnType, DCM_CODE)  Dcm_31_0x0203_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
	uint8 lResult = DCM_E_OK;
	*ErrorPtr = DCM_E_OK;
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE)  Dcm_31_0xFF00_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
	uint8 lResult = DCM_E_OK;
	*ErrorPtr = DCM_E_OK;
	return lResult;
}
//Integrity verifying
FUNC(Std_ReturnType, DCM_CODE)  Dcm_31_0x0202_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
	uint8 lResult = DCM_E_OK;
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE)  Dcm_31_0xFF01_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
	uint8 lResult = DCM_E_OK;
	*ErrorPtr = DCM_E_OK;
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE)  Dcm_31_0x6A00_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
	uint8 lResult = DCM_E_OK;
	*ErrorPtr = DCM_E_OK;
	return lResult;
}
FUNC(Std_ReturnType, DCM_CODE)  Dcm_31_0x6A00_Stop(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
	uint8 lResult = DCM_E_OK;
	*ErrorPtr = DCM_E_OK;
	return lResult;
}
#endif/* STD_ON == DCM_SERVICE_31_ENABLED */

#if (STD_ON == DCM_SERVICE_85_ENABLED)

FUNC(uint8, DCM_CODE) Dcm_Check85SubDtcSettingFunc(void)
{
    return DCM_E_OK;
}

/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/

FUNC(void, DCM_CODE) Dcm_Notify85SubDtcSettingFunc(uint8 subFunc)
{
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
#endif/* STD_ON == DCM_SERVICE_85_ENABLED */

#if (STD_ON == DCM_SERVICE_34_ENABLED)
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE)Dcm_34_PreConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    *ErrorCode = DCM_E_OK;
}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(uint8, DCM_CODE) Dcm_34_RoutineFunction(P2VAR(Dcm_34_ProcessContextType_st, AUTOMATIC, DCM_APPL_DATA) ProcessContext, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    uint8 retValue = DCM_E_OK;

    if( (NULL_PTR != ProcessContext) && (NULL_PTR != ErrorCode) )
    {
       Dcm_DslInfoPool.Dcm_DataPtr[1] = 0x10;
       
    }
    else
    {
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        retValue = DCM_E_NOT_OK;
    }

    return retValue;
}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
#endif /* STD_ON == DCM_SERVICE_34_ENABLED */

#if (STD_ON == DCM_SERVICE_36_ENABLED)
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/

uint32 crc32(uint8* ReqBuffer,uint16 ReqBufferLen,uint32* crcValue)
{
	for(int i = 0;i < ReqBufferLen;i++)
	{
		*crcValue = ((*crcValue >> 8) & 0x00FFFFFF) ^ crc_table[(*crcValue ^ ReqBuffer[i])&0xFF];
	}
	return *crcValue;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_36_RoutineFunctionForDcm34(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ReqBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ReqBufferLen, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RespBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) RespBufferLen, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    Std_ReturnType retValue = DCM_E_OK;
    // if( (NULL_PTR != ReqBuffer) && (NULL_PTR != RespBuffer) && (NULL_PTR != ReqBufferLen) && (NULL_PTR != RespBufferLen) && (NULL_PTR != ErrorCode) )
    // {
	// 	crc32(ReqBuffer,*ReqBufferLen,&initialCRC32Value);
    // }
    // else
    // {
    //     *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    //     retValue = DCM_E_NOT_OK;
    // }
 return retValue;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_36_RoutineFunctionForDcm35(Dcm_OpStatusType OpStatus,
                                        uint8 MemoryIdentifier,
                                        uint32 MemoryAddress,
                                        uint32 MemorySize,
                                        P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) MemoryData,
                                        P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    Std_ReturnType retValue = DCM_E_OK;

    DCM_DUMMY_STATEMENT(OpStatus);
    DCM_DUMMY_STATEMENT(MemoryIdentifier);
    if( NULL_PTR == ErrorCode )
    {
        retValue = DCM_E_NOT_OK;
    }
    else if( (DCM_ZERO == MemorySize) || (NULL_PTR == MemoryData) )
    {
        retValue = DCM_E_NOT_OK;
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        Dcm_MemCpy(MemoryData, (const uint8*)MemoryAddress, MemorySize);
        *ErrorCode = DCM_E_OK;
    }
    
    return retValue;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_36_RoutineFunctionForDcm38(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
    return DCM_E_OK;
}



#endif /* STD_ON == DCM_SERVICE_36_ENABLED */

#if (STD_ON == DCM_SERVICE_37_ENABLED)
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(uint8, DCM_CODE) Dcm_37_RoutineFunctionForDcm34(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataBufferLen, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    uint8 retValue = DCM_E_NOT_OK;

    if( (NULL_PTR != DataBuffer) && (NULL_PTR != DataBufferLen) && (NULL_PTR != ErrorCode) )
    {
        *ErrorCode = DCM_E_OK;
        retValue = DCM_E_OK;
    }
    else
    {
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        retValue = DCM_E_NOT_OK;
    }

    return retValue;
}
FUNC(uint8, DCM_CODE) Dcm_37_RoutineFunctionForDcm35(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataBufferLen, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    uint8 retValue = DCM_E_NOT_OK;

    if( (NULL_PTR != DataBuffer) && (NULL_PTR != DataBufferLen) && (NULL_PTR != ErrorCode) )
    {
        *ErrorCode = DCM_E_OK;
        retValue = DCM_E_OK;
    }
    else
    {
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        retValue = DCM_E_NOT_OK;
    }

    return retValue;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_37_RoutineFunctionForDcm38(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
    return DCM_E_OK;
}
#endif /* STD_ON == DCM_SERVICE_37_ENABLED */

#if ( (STD_ON == DCM_SERVICE_10_ENABLED) || (STD_ON == DCM_SERVICE_28_ENABLED) )
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_ControlCommunication(uint8 subfunc, uint8 comtype)
{
    uint8 channelID = DCM_ZERO;
    uint8 pdurGrpNum = DCM_ZERO; /* Must equal to "PDUR_MAX_ROUTING_PATH_GROUP_CNT". */
    uint8 ipduSignal[DCM_COMM_SIGNAL_NUM] = {DCM_ZERO};

    /* Enable rx and tx. */
    if( (DCM_COMM_ENABLE_RX_AND_TX == subfunc) || (DCM_COMM_ENABLE_RX_AND_TX_SUPPRESSPOS == subfunc) )
    {
        if( (uint8)((uint32)DCM_COMM_NORMALMSG & (uint32)comtype) != DCM_ZERO )  /* COM */
        {
            Dcm_MemSet(ipduSignal, DCM_COMM_SIGNAL_ENABLE_RX_AND_TX, DCM_COMM_SIGNAL_NUM);
            /* Application message enable. */
            // (void)Com_IpduGroupControl(ipduSignal, FALSE);
            /* Group message enable. */
            for( channelID = DCM_ZERO; channelID != pdurGrpNum; channelID++ )
            {
                // PduR_EnableRouting(channelID);
            }

        }

#if ( STD_ON == DCM_SERVICE_28_ENABLED )
        if( (uint8)((uint32)DCM_COMM_NMMSG & (uint32)comtype) != DCM_ZERO )  /* NM */
        {
            for( channelID = DCM_ZERO; channelID != DCM_28_CHANNLE_NUM; channelID++ )
            {
                /* Network manger message enable. */
                // (void)Nm_EnableCommunication(Dcm_28_ChannelId[channelID]);
            }
        }
#endif
    }

    /* Enable rx and disable tx. */
    else if( (DCM_COMM_ENABLE_RX_AND_DISABLE_TX == subfunc)
            || (DCM_COMM_ENABLE_RX_AND_DISABLE_TX_SUPPRESSPOS == subfunc) )
    {
        if( (uint8)((uint32)DCM_COMM_NORMALMSG & (uint32)comtype) != DCM_ZERO )  /* COM */
        {
            Dcm_MemSet(ipduSignal, DCM_COMM_SIGNAL_ENABLE_RX_AND_DISABLE_TX, DCM_COMM_SIGNAL_NUM);
            /* Application message enable. */
            // (void)Com_IpduGroupControl(ipduSignal, FALSE);
            /* Group message disable. */
            for( channelID = DCM_ZERO; channelID != pdurGrpNum; channelID++ )
            {
                // PduR_DisableRouting(channelID, TRUE);
            }

        }

#if ( STD_ON == DCM_SERVICE_28_ENABLED )
        if( (uint8)((uint32)DCM_COMM_NMMSG & (uint32)comtype) != DCM_ZERO )  /* NM */
        {
            for( channelID = DCM_ZERO; channelID != DCM_28_CHANNLE_NUM; channelID++ )
            {
                /* Network manger message disable. */
                // (void)Nm_DisableCommunication(Dcm_28_ChannelId[channelID]);
            }
        }
#endif

    }

    /* Disable rx and enable tx. */
    else if( (DCM_COMM_DISABLE_RX_AND_ENABLE_TX == subfunc)
            || (DCM_COMM_DISABLE_RX_AND_ENABLE_TX_SUPPRESSPOS == subfunc) )
    {
        if( (uint8)((uint32)DCM_COMM_NORMALMSG & (uint32)comtype)!= DCM_ZERO )  /* COM */
        {
            Dcm_MemSet(ipduSignal, DCM_COMM_SIGNAL_DISABLE_RX_AND_ENABLE_TX, DCM_COMM_SIGNAL_NUM);
            /* Application message enable. */
            // (void)Com_IpduGroupControl(ipduSignal, FALSE);

            /* Group message enable. */
            for( channelID = DCM_ZERO; channelID != pdurGrpNum; channelID++ )
            {
                // PduR_EnableRouting(channelID);
            }
        }

#if ( STD_ON == DCM_SERVICE_28_ENABLED )
        if( (uint8)((uint32)DCM_COMM_NMMSG & (uint32)comtype) != DCM_ZERO )  /* NM */
        {
            for( channelID = DCM_ZERO; channelID != DCM_28_CHANNLE_NUM; channelID++ )
            {
                /* Network manger message enable. */
                // (void)Nm_EnableCommunication(Dcm_28_ChannelId[channelID]);
            }
        }
#endif

    }
    /* Disable rx and tx. */
    else if( (DCM_COMM_DISABLE_RX_AND_TX == subfunc) || (DCM_COMM_DISABLE_RX_AND_TX_SUPPRESSPOS == subfunc) )
    {
        if( (uint8)((uint32)DCM_COMM_NORMALMSG & (uint32)comtype) != DCM_ZERO )  /* COM */
        {
            Dcm_MemSet(ipduSignal, DCM_COMM_SIGNAL_DISABLE_RX_AND_TX, DCM_COMM_SIGNAL_NUM);
            /* Application message enable. */
            // (void)Com_IpduGroupControl(ipduSignal, FALSE);

            /* Group message disable. */
            for( channelID = DCM_ZERO; channelID != pdurGrpNum; channelID++ )
            {
                // PduR_DisableRouting(channelID, TRUE);
            }
        }

#if ( STD_ON == DCM_SERVICE_28_ENABLED )
        if( (uint8)((uint32)DCM_COMM_NMMSG & (uint32)comtype) != DCM_ZERO )  /* NM */
        {
            for( channelID = DCM_ZERO; channelID != DCM_28_CHANNLE_NUM; channelID++ )
            {
                /* Network manger message disable. */
                // (void)Nm_DisableCommunication(Dcm_28_ChannelId[channelID]);
            }
        }
#endif

    }
    else
    {
        /* Nothing to do. */
    }
}

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
#endif/* (STD_ON == DCM_SERVICE_10_ENABLED) || (STD_ON == DCM_SERVICE_28_ENABLED) */

#if (STD_ON == DCM_SERVICE_29_ENABLED)

/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub00_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub01_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub02_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub03_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub04_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub05_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub06_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub07_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub08_CheckRuleFunc(void)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;
    return errorCode;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/




#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if ( STD_ON == DCM_SERVICE_01_ENABLED )
	
#endif

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
	
#endif

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
	
#endif

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/

/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
#endif

#if (STD_ON == DCM_SERVICE_35_ENABLED)
/*
********************************************************************************
*    <User_Function_Definition_Begin>
********************************************************************************
*/
FUNC(void, DCM_CODE) Dcm_35_PreConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
    *ErrorCode = DCM_E_OK;
}

FUNC(uint8, DCM_CODE) Dcm_ProcessRequestUpload
(
    Dcm_OpStatusType OpStatus, uint8 DataFormatIdentifier,
    uint8 MemoryIdentifier, uint32 MemoryAddress, uint32 MemorySize,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) BlockLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
)
{
    uint8 retValue = DCM_E_OK;
    if( (NULL_PTR != BlockLength) && (NULL_PTR != ErrorCode) )
    {
    }
    else
    {
        retValue = DCM_E_NOT_OK;
    }
    return retValue;
}
/*
********************************************************************************
*    <User_Function_Definition_End>
********************************************************************************
*/
#endif /* STD_ON == DCM_SERVICE_35_ENABLED */

FUNC(uint8, DCM_CODE) Dcm_10_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_11_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_27_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_28_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_3E_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_85_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_22_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_2E_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_2F_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_29_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_31_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_19_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_14_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_34_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_36_CheckRule(void)
{
	return DCM_E_OK;
}
FUNC(uint8, DCM_CODE) Dcm_37_CheckRule(void)
{
	return DCM_E_OK;
}

#if (STD_ON == DCM_SERVICE_38_ENABLED)
FUNC(Std_ReturnType, DCM_CODE) Dcm_38_Info_Trans(P2CONST(Dcm_38_ServiceInfoType_Req, AUTOMATIC, DCM_APPL_DATA) DataInVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
    uint8 lResult = DCM_E_NOT_OK;

    
    if( DCM_E_OK == *ErrorPtr )
    {
        lResult = DCM_E_OK;
    }
    else
    {
        lResult = DCM_E_NOT_OK;
    }

    return lResult;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_38_Info_Capture(P2VAR(Dcm_38_ServiceInfoType_Res, AUTOMATIC, DCM_APPL_DATA) DataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr)
{
    uint8 lResult = DCM_E_NOT_OK;

    
    if( DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING == *ErrorPtr )
    {
        lResult = DCM_E_PENDING;
    }
    else if( DCM_E_OK == *ErrorPtr )
    {
         lResult = DCM_E_OK;
    }
    else
    {
         lResult = DCM_E_NOT_OK;
    }

    return lResult;
}
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#define DCM_STOP_SEC_CODE
#include "eth/include/Dcm/Dcm_MemMap.h"

