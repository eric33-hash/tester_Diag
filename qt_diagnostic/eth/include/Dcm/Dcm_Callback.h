/*
********************************************************************************
*
*  File name:   Dcm_Callback.h
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: Tanlx/20190501
* Change: Autosar
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: lqiao/20220831
* Change: Dcm_37_RoutineFunction
* Cause: Add function declare
********************************************************************************
* Version: 3.0
* Author/Date: LQiao/2023.2.13
* Change: DCM_SERVICE_38
* Cause: Optimization
********************************************************************************
*/
#ifndef DCM_CALLBACK_H_
#define DCM_CALLBACK_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Dcm_Cfg.h"
#include "Dcm_Cbk.h"
// #include "ComM.h"
// #include "ComStack_Types.h"
#include "Dcm_Lcfg.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/*
********************************************************************************
*    Global Types
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
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#if ( STD_ON == DCM_SERVICE_01_ENABLED )
	

#endif /* STD_ON == DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )


#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )


#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

#if (STD_ON == DCM_SERVICE_10_ENABLED)
extern FUNC(uint8, DCM_CODE) Dcm_Check10SubProgrammingFunc(void);
extern FUNC(uint8, DCM_CODE) Dcm_Check10SubextendedFunc(void);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Check10WithPara(uint8 Subfunc, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SetProgConditions(Dcm_OpStatusType OpStatus, P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions);
extern FUNC(void, DCM_CODE) Dcm_10_JumpToBootWithAppResp(void);
extern FUNC(void, DCM_CODE) Dcm_10_JumpToBootWithBootResp(void);
extern FUNC(void, DCM_CODE) Dcm_OnChangeParameter(void);
extern FUNC(void, DCM_CODE) Dcm_10_SessionChangedCallBack(void);
extern FUNC(void, DCM_CODE) Dcm_SessionChangedMode(uint8 sessionMode);
#endif /* STD_ON == DCM_SERVICE_10_ENABLED */

#if (STD_ON == DCM_SERVICE_11_ENABLED)
extern FUNC(uint8, DCM_CODE) Dcm_Check11SubResetFunc(void);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Check11WithPara(uint8 Subfunc, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(void, DCM_CODE) Dcm_EcuResetMode(uint8 acRequestedMode);
#endif /* STD_ON == DCM_SERVICE_11_ENABLED */

#if (STD_ON == DCM_SERVICE_14_ENABLED)
extern FUNC(uint8, DCM_CODE) Dcm_14_CheckRuleFunc(void);
extern FUNC(void, DCM_CODE) Dcm_ClearCallBackFunc(void);
#endif /* STD_ON == DCM_SERVICE_14_ENABLED */

 


uint32 crc32(uint8* ReqBuffer,uint16 ReqBufferLen,uint32* crcValue);
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F187_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F187_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F187_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18A_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18A_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18A_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F197_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F197_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F197_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F189_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F189_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F189_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F089_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F089_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F089_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F193_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F193_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F193_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F195_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F195_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F195_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18C_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18C_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F18C_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F180_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F180_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F180_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_WriteData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F190_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_WriteData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F010_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_WriteData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15A_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15B_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15B_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_F15B_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CE00_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CE00_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CE00_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF00_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF00_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF00_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF01_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF01_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF01_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF02_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF02_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF02_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF03_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF03_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF03_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF04_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF04_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_CF04_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_0010_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_0010_ReadData(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgr_0010_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) */
 
#if (STD_ON == DCM_SERVICE_27_ENABLED)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_CompareKey(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_GetAttemptCounter(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) AttemptCounter);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SecurityAccess_Level_01_SetAttemptCounter(Dcm_OpStatusType OpStatus, uint8 AttemptCounter);
extern FUNC(uint8, DCM_CODE) Dcm_SecurityAccess_Level_01_CheckRule(void);
extern FUNC(void, DCM_CODE) Dcm_SecurityAcces_CalcRand(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ranSeed);
#endif /* STD_ON == DCM_SERVICE_27_ENABLED */
 
#if (STD_ON == DCM_SERVICE_2F_ENABLED)
extern VAR(uint8,DCM_CODE) Dcm_Check2FSubIOFunc(void);
extern FUNC(uint8, DCM_CODE) InputOutput_0010_ReturnControlToECU(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) RsepLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(uint8, DCM_CODE) InputOutput_0010_ShortTermAdjustment(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, uint16 ReqLength, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) RsepLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */
 
#if (STD_ON == DCM_SERVICE_31_ENABLED)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_31_0x0203_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_31_0xFF00_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_31_0x0202_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_31_0xFF01_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_31_0x6A00_Start(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_31_0x6A00_Stop(P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) DataInVar, Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataOutVar, uint16 CurrentLengthDataInVar, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) CurrentLengthDataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
#endif /* STD_ON == DCM_SERVICE_31_ENABLED */

#if (STD_ON == DCM_SERVICE_28_ENABLED)
extern FUNC(uint8, DCM_CODE) Dcm_Check28SubComMFunc(void);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Check28WithPara(uint8 Subfunc, uint8 Comtype, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
#endif /* STD_ON == DCM_SERVICE_28_ENABLED */

#if ( STD_ON == DCM_SERVICE_85_ENABLED )
extern FUNC(uint8, DCM_CODE) Dcm_Check85SubDtcSettingFunc(void);
extern FUNC(void, DCM_CODE) Dcm_Notify85SubDtcSettingFunc(uint8 subFunc);
#endif /* STD_ON == DCM_SERVICE_85_ENABLED */



#if (STD_ON == DCM_SERVICE_34_ENABLED)
extern FUNC(void, DCM_CODE) Dcm_34_PreConditionCheckRead
(
	P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
);
extern FUNC(uint8, DCM_CODE) Dcm_34_RoutineFunction(P2VAR(Dcm_34_ProcessContextType_st, AUTOMATIC, DCM_APPL_DATA) ProcessContext, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
#endif /* STD_ON == DCM_SERVICE_34_ENABLED */

#if (STD_ON == DCM_SERVICE_35_ENABLED)
extern FUNC(void, DCM_CODE) Dcm_35_PreConditionCheckRead
(
	P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
);
extern FUNC(uint8, DCM_CODE) Dcm_ProcessRequestUpload
(
    Dcm_OpStatusType OpStatus, uint8 DataFormatIdentifier,
    uint8 MemoryIdentifier, uint32 MemoryAddress, uint32 MemorySize,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) BlockLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
);
#endif /* STD_ON == DCM_SERVICE_35_ENABLED */

#if ( (STD_ON == DCM_SERVICE_10_ENABLED) || (STD_ON == DCM_SERVICE_28_ENABLED) )
extern FUNC(void, DCM_CODE) Dcm_ControlCommunication(uint8 subfunc, uint8 comtype);
#endif /* (STD_ON == DCM_SERVICE_10_ENABLED) || (STD_ON == DCM_SERVICE_28_ENABLED) */	

#if (STD_ON == DCM_SERVICE_36_ENABLED)
extern FUNC(uint8, DCM_CODE) Dcm_36_RoutineFunctionForDcm34(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ReqBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ReqBufferLen, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RespBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) RespBufferLen, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_36_RoutineFunctionForDcm35
(
	Dcm_OpStatusType OpStatus,
	uint8 MemoryIdentifier,
	uint32 MemoryAddress,
	uint32 MemorySize,
	P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) MemoryData,
	P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_36_RoutineFunctionForDcm38(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
#endif /* STD_ON == DCM_SERVICE_36_ENABLED */

#if (STD_ON == DCM_SERVICE_37_ENABLED)
extern FUNC(uint8, DCM_CODE) Dcm_37_RoutineFunctionForDcm34(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataBufferLen, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(uint8, DCM_CODE) Dcm_37_RoutineFunctionForDcm35(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataBuffer, P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataBufferLen, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_37_RoutineFunctionForDcm38(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
#endif/* STD_ON == DCM_SERVICE_37_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub00_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub01_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub02_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub03_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub04_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub05_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub06_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub07_CheckRuleFunc(void);
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_29_Sub08_CheckRuleFunc(void);





#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_38_Info_Trans(P2CONST(Dcm_38_ServiceInfoType_Req, AUTOMATIC, DCM_APPL_DATA) DataInVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_38_Info_Capture(P2VAR(Dcm_38_ServiceInfoType_Res, AUTOMATIC, DCM_APPL_DATA) DataOutVar, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorPtr);
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

extern FUNC(uint8, DCM_CODE) Dcm_10_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_11_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_27_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_28_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_3E_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_85_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_22_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_2E_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_2F_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_29_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_31_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_19_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_14_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_34_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_36_CheckRule(void);
extern FUNC(uint8, DCM_CODE) Dcm_37_CheckRule(void);



static const unsigned long crc_table[256] =
{
    0x00000000UL, 0x77073096UL, 0xee0e612cUL, 0x990951baUL, 0x076dc419UL,
    0x706af48fUL, 0xe963a535UL, 0x9e6495a3UL, 0x0edb8832UL, 0x79dcb8a4UL,
    0xe0d5e91eUL, 0x97d2d988UL, 0x09b64c2bUL, 0x7eb17cbdUL, 0xe7b82d07UL,
    0x90bf1d91UL, 0x1db71064UL, 0x6ab020f2UL, 0xf3b97148UL, 0x84be41deUL,
    0x1adad47dUL, 0x6ddde4ebUL, 0xf4d4b551UL, 0x83d385c7UL, 0x136c9856UL,
    0x646ba8c0UL, 0xfd62f97aUL, 0x8a65c9ecUL, 0x14015c4fUL, 0x63066cd9UL,
    0xfa0f3d63UL, 0x8d080df5UL, 0x3b6e20c8UL, 0x4c69105eUL, 0xd56041e4UL,
    0xa2677172UL, 0x3c03e4d1UL, 0x4b04d447UL, 0xd20d85fdUL, 0xa50ab56bUL,
    0x35b5a8faUL, 0x42b2986cUL, 0xdbbbc9d6UL, 0xacbcf940UL, 0x32d86ce3UL,
    0x45df5c75UL, 0xdcd60dcfUL, 0xabd13d59UL, 0x26d930acUL, 0x51de003aUL,
    0xc8d75180UL, 0xbfd06116UL, 0x21b4f4b5UL, 0x56b3c423UL, 0xcfba9599UL,
    0xb8bda50fUL, 0x2802b89eUL, 0x5f058808UL, 0xc60cd9b2UL, 0xb10be924UL,
    0x2f6f7c87UL, 0x58684c11UL, 0xc1611dabUL, 0xb6662d3dUL, 0x76dc4190UL,
    0x01db7106UL, 0x98d220bcUL, 0xefd5102aUL, 0x71b18589UL, 0x06b6b51fUL,
    0x9fbfe4a5UL, 0xe8b8d433UL, 0x7807c9a2UL, 0x0f00f934UL, 0x9609a88eUL,
    0xe10e9818UL, 0x7f6a0dbbUL, 0x086d3d2dUL, 0x91646c97UL, 0xe6635c01UL,
    0x6b6b51f4UL, 0x1c6c6162UL, 0x856530d8UL, 0xf262004eUL, 0x6c0695edUL,
    0x1b01a57bUL, 0x8208f4c1UL, 0xf50fc457UL, 0x65b0d9c6UL, 0x12b7e950UL,
    0x8bbeb8eaUL, 0xfcb9887cUL, 0x62dd1ddfUL, 0x15da2d49UL, 0x8cd37cf3UL,
    0xfbd44c65UL, 0x4db26158UL, 0x3ab551ceUL, 0xa3bc0074UL, 0xd4bb30e2UL,
    0x4adfa541UL, 0x3dd895d7UL, 0xa4d1c46dUL, 0xd3d6f4fbUL, 0x4369e96aUL,
    0x346ed9fcUL, 0xad678846UL, 0xda60b8d0UL, 0x44042d73UL, 0x33031de5UL,
    0xaa0a4c5fUL, 0xdd0d7cc9UL, 0x5005713cUL, 0x270241aaUL, 0xbe0b1010UL,
    0xc90c2086UL, 0x5768b525UL, 0x206f85b3UL, 0xb966d409UL, 0xce61e49fUL,
    0x5edef90eUL, 0x29d9c998UL, 0xb0d09822UL, 0xc7d7a8b4UL, 0x59b33d17UL,
    0x2eb40d81UL, 0xb7bd5c3bUL, 0xc0ba6cadUL, 0xedb88320UL, 0x9abfb3b6UL,
    0x03b6e20cUL, 0x74b1d29aUL, 0xead54739UL, 0x9dd277afUL, 0x04db2615UL,
    0x73dc1683UL, 0xe3630b12UL, 0x94643b84UL, 0x0d6d6a3eUL, 0x7a6a5aa8UL,
    0xe40ecf0bUL, 0x9309ff9dUL, 0x0a00ae27UL, 0x7d079eb1UL, 0xf00f9344UL,
    0x8708a3d2UL, 0x1e01f268UL, 0x6906c2feUL, 0xf762575dUL, 0x806567cbUL,
    0x196c3671UL, 0x6e6b06e7UL, 0xfed41b76UL, 0x89d32be0UL, 0x10da7a5aUL,
    0x67dd4accUL, 0xf9b9df6fUL, 0x8ebeeff9UL, 0x17b7be43UL, 0x60b08ed5UL,
    0xd6d6a3e8UL, 0xa1d1937eUL, 0x38d8c2c4UL, 0x4fdff252UL, 0xd1bb67f1UL,
    0xa6bc5767UL, 0x3fb506ddUL, 0x48b2364bUL, 0xd80d2bdaUL, 0xaf0a1b4cUL,
    0x36034af6UL, 0x41047a60UL, 0xdf60efc3UL, 0xa867df55UL, 0x316e8eefUL,
    0x4669be79UL, 0xcb61b38cUL, 0xbc66831aUL, 0x256fd2a0UL, 0x5268e236UL,
    0xcc0c7795UL, 0xbb0b4703UL, 0x220216b9UL, 0x5505262fUL, 0xc5ba3bbeUL,
    0xb2bd0b28UL, 0x2bb45a92UL, 0x5cb36a04UL, 0xc2d7ffa7UL, 0xb5d0cf31UL,
    0x2cd99e8bUL, 0x5bdeae1dUL, 0x9b64c2b0UL, 0xec63f226UL, 0x756aa39cUL,
    0x026d930aUL, 0x9c0906a9UL, 0xeb0e363fUL, 0x72076785UL, 0x05005713UL,
    0x95bf4a82UL, 0xe2b87a14UL, 0x7bb12baeUL, 0x0cb61b38UL, 0x92d28e9bUL,
    0xe5d5be0dUL, 0x7cdcefb7UL, 0x0bdbdf21UL, 0x86d3d2d4UL, 0xf1d4e242UL,
    0x68ddb3f8UL, 0x1fda836eUL, 0x81be16cdUL, 0xf6b9265bUL, 0x6fb077e1UL,
    0x18b74777UL, 0x88085ae6UL, 0xff0f6a70UL, 0x66063bcaUL, 0x11010b5cUL,
    0x8f659effUL, 0xf862ae69UL, 0x616bffd3UL, 0x166ccf45UL, 0xa00ae278UL,
    0xd70dd2eeUL, 0x4e048354UL, 0x3903b3c2UL, 0xa7672661UL, 0xd06016f7UL,
    0x4969474dUL, 0x3e6e77dbUL, 0xaed16a4aUL, 0xd9d65adcUL, 0x40df0b66UL,
    0x37d83bf0UL, 0xa9bcae53UL, 0xdebb9ec5UL, 0x47b2cf7fUL, 0x30b5ffe9UL,
    0xbdbdf21cUL, 0xcabac28aUL, 0x53b39330UL, 0x24b4a3a6UL, 0xbad03605UL,
    0xcdd70693UL, 0x54de5729UL, 0x23d967bfUL, 0xb3667a2eUL, 0xc4614ab8UL,
    0x5d681b02UL, 0x2a6f2b94UL, 0xb40bbe37UL, 0xc30c8ea1UL, 0x5a05df1bUL,
    0x2d02ef8dUL
};

#endif /* DCM_CALLBACK_H_ */

