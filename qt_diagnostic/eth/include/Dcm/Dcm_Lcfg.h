/*
********************************************************************************
*
*  File name:   Dcm_Lcfg.h
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
* Author/Date: Tanlx/20190513
* Change: Autosar
* Cause: Modify format.
********************************************************************************
* Version: 1.2
* Author/Date : Liuziyang/2019.11.22
* Change: The format of code and comment.
* Cause: Modify the code according to the coding specification.
********************************************************************************
* Version: 1.3
* Author/Date : Songqingwei/2020.01.22
* Change: Change the DCM_INVALID_BLOCKID from 0xFFFFFFFF to 0xFFFF.
* Cause: Invalid NvM BlockId is error.
********************************************************************************
* Version: 3.0
* Author/Date : ZhuCY/2021.10.27
* Change: Modify header file name.
* Cause: Optimization.
********************************************************************************
* Version: 3.1
* Author/Date: ZhuCY/2021.10.28
* Change: Modify header file.
* Cause: Optimization.
********************************************************************************
* Version: 3.2
* Author/Date: LQiao/2023.02.06
* Change: Add Struct. Add 38 service. 
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LQiao/2023.02.13
* Change: Del redundant struct.
* Cause: Optimization
********************************************************************************
*/
#ifndef DCM_LCFG_H_
#define DCM_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Dcm_Cfg.h"
#include "Dcm_Cbk.h"
// #include "ComM.h"
// #include "ComStack_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define DCM_NUM_ZERO                                (0x0U)
#define DCM_MAX_CAN_CHANNEL                         COMM_ACTIVE_CHANNEL
#define DCM_INVALID_BLOCKID                         (0xFFFFU)
#define DCM_NUM_CHECKCOND 	                        (5U)
#define DCM_PHY 			                        (0x01U)
#define DCM_FUN                                     (0x02U)
#define DCM_PHY_FUN                                 (0x03U)
#define DCM_SERVICE_OBD                             (0x00U)
#define DCM_SERVICE_UDS                             (0x01U)

#ifndef DCM_E_GENERALREJECT
#define DCM_E_GENERALREJECT                         (0x10U)
#endif

#ifndef DCM_E_SERVICENOTSUPPORTED
#define DCM_E_SERVICENOTSUPPORTED                   (0x11U)
#endif

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTED
#define DCM_E_SUBFUNCTIONNOTSUPPORTED               (0x12U)
#endif

#ifndef DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (0x13U)
#endif

#ifndef DCM_E_RESPONSETOOLONG
#define DCM_E_RESPONSETOOLONG                       (0x14U)
#endif

#ifndef DCM_E_BUSYREPEATREQUEST
#define DCM_E_BUSYREPEATREQUEST                     (0x21U)
#endif

#ifndef DCM_E_CONDITIONSNOTCORRECT
#define DCM_E_CONDITIONSNOTCORRECT                  (0x22U)
#endif

#ifndef DCM_E_REQUESTSEQUENCEERROR
#define DCM_E_REQUESTSEQUENCEERROR                  (0x24U)
#endif

#ifndef DCM_E_NORESPONSEFROMSUBNETCOMPONENT
#define DCM_E_NORESPONSEFROMSUBNETCOMPONENT         (0x25U)
#endif

#ifndef DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION
#define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION (0x26U)
#endif

#ifndef DCM_E_REQUESTOUTOFRANGE
#define DCM_E_REQUESTOUTOFRANGE                     (0x31U)
#endif

#ifndef DCM_E_SECURITYACCESSDENIED
#define DCM_E_SECURITYACCESSDENIED                  (0x33U)
#endif

#ifndef DCM_E_INVALIDKEY
#define DCM_E_INVALIDKEY                            (0x35U)
#endif

#ifndef DCM_E_EXCEEDNUMBEROFATTEMPTS
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                (0x36U)
#endif

#ifndef DCM_E_REQUIREDTIMEDELAYNOTEXPIRED
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED           (0x37U)
#endif

#ifndef DCM_E_UPLOADDOWNLOADNOTACCEPTED
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED             (0x70U)
#endif

#ifndef DCM_E_TRANSFERDATASUSPENDED
#define DCM_E_TRANSFERDATASUSPENDED                 (0x71U)
#endif

#ifndef DCM_E_GENERALPROGRAMMINGFAILURE
#define DCM_E_GENERALPROGRAMMINGFAILURE             (0x72U)
#endif

#ifndef DCM_E_WRONGBLOCKSEQUENCECOUNTER
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER             (0x73U)
#endif

#ifndef DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING (0x78U)
#endif

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION   (0x7EU)
#endif

#ifndef DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION    (0x7FU)
#endif

#ifndef DCM_E_RPMTOOHIGH
#define DCM_E_RPMTOOHIGH                            (0x81U)
#endif

#ifndef DCM_E_RPMTOOLOW
#define DCM_E_RPMTOOLOW                             (0x82U)
#endif

#ifndef DCM_E_ENGINEISRUNNING
#define DCM_E_ENGINEISRUNNING                       (0x83U)
#endif

#ifndef DCM_E_ENGINEISNOTRUNNING
#define DCM_E_ENGINEISNOTRUNNING                    (0x84U)
#endif

#ifndef DCM_E_ENGINERUNTIMETOOLOW
#define DCM_E_ENGINERUNTIMETOOLOW                   (0x85U)
#endif

#ifndef DCM_E_TEMPERATURETOOHIGH
#define DCM_E_TEMPERATURETOOHIGH                    (0x86U)
#endif

#ifndef DCM_E_TEMPERATURETOOLOW
#define DCM_E_TEMPERATURETOOLOW                     (0x87U)
#endif

#ifndef DCM_E_VEHICLESPEEDTOOHIGH
#define DCM_E_VEHICLESPEEDTOOHIGH                   (0x88U)
#endif

#ifndef DCM_E_VEHICLESPEEDTOOLOW
#define DCM_E_VEHICLESPEEDTOOLOW                    (0x89U)
#endif

#ifndef DCM_E_THROTTLE_PEDALTOOHIGH
#define DCM_E_THROTTLE_PEDALTOOHIGH                 (0x8AU)
#endif

#ifndef DCM_E_THROTTLE_PEDALTOOLOW
#define DCM_E_THROTTLE_PEDALTOOLOW                  (0x8BU)
#endif

#ifndef DCM_E_TRANSMISSIONRANGENOTINNEUTRAL
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL         (0x8CU)
#endif

#ifndef DCM_E_TRANSMISSIONRANGENOTINGEAR
#define DCM_E_TRANSMISSIONRANGENOTINGEAR            (0x8DU)
#endif

#ifndef DCM_E_BRAKESWITCH_NOTCLOSED
#define DCM_E_BRAKESWITCH_NOTCLOSED                 (0x8FU)
#endif

#ifndef DCM_E_SHIFTERLEVERNOTINPARK
#define DCM_E_SHIFTERLEVERNOTINPARK                 (0x90U)
#endif

#ifndef DCM_E_TORQUECONVERTERCLUTCHLOCKED
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED           (0x91U)
#endif

#ifndef DCM_E_VOLTAGETOOHIGH
#define DCM_E_VOLTAGETOOHIGH                        (0x92U)
#endif

#ifndef DCM_E_VOLTAGETOOLOW
#define DCM_E_VOLTAGETOOLOW                         (0x93U)
#endif

#ifndef DCM_E_KEYON
#define DCM_E_KEYON                                 (0xF0U)
#endif

#ifndef DCM_E_HVSTATE
#define DCM_E_HVSTATE                               (0xF1U)
#endif

#define DCM_SESSION_DEFAULT_LEVEL                   (0x00U)
#define DCM_SESSION_PROG_LEVEL                      (0x01U)
#define DCM_SESSION_EXTEND_LEVEL                    (0x02U)

#define DCM_DSL_CHANNEL_NUM                          (0x02U)
#define DCM_READ_BLOCK_NUM                           (0x00U)
#define DCM_MAINTASK_CYCLE                           (10U)
#define DCM_NUM_SERVICES                             (0x10U)
#define DCM_TIMEOUT_S3                               (5000U / DCM_MAINTASK_CYCLE)
#define DCM_DSL_BUFFERLEN                            (0x0040U)
#define DCM_DSL_RESPPENDDING_NUM                     (0x0014U)
#define DCM_SPT_ADDRESSANDLENGTH_FORMAT              (0x0044U)

#define DCM_NUMOFBLOCKSIZE                           (0x00C8U)
#define DCM_DSL_PROTOCOL_TX_NUM                      (2U)
#define DCM_DSL_PROTOCOL_NUM                         (4U)
#define DCM_DSL_PROTOCOL_TYPE1 (0x01U)
#define DCM_DSL_PROTOCOL_TYPE2 (0x02U)
#define DCM_NUMOFBLOCKSIZE_FILETRANS                 (0x0200U)
#if (STD_ON == DCM_SERVICE_10_ENABLED)
#define DCM_10_SUBID                                 (0x0002U)
#define DCM_P2_TIME_01                               (0x0032U)
#define DCM_P2EX_TIME_01                             (0x1388U)
#define DCM_P2_TIME_02                               (0x0032U)
#define DCM_P2EX_TIME_02                             (0x1388U)
#define DCM_P2_TIME_01                               (0x0032U)
#define DCM_P2EX_TIME_01                             (0x1388U)
#endif
#if (STD_ON == DCM_SERVICE_11_ENABLED)
#define DCM_11_SUBID                                 (0x0002U)
#define DCM_11_BLOCKIDREF                            (0xFFFFU)
#define DCM_11_BLOCKSIZE                             (4U)
#endif
#if (STD_ON == DCM_SERVICE_27_ENABLED)
#define DCM_27_ATTDELAY_ENABLE                       (STD_ON)
#define DCM_27_ATTEMPT_MONITOR                       (STD_ON)
#define DCM_27_MAX_SEED_LENGTH                       (0x04U)
#define DCM_27_SUB_NUM                               (0x0001U)
#define DCM_2701_MAX_SEED_LENGTH                     (0x04U)
#define DCM_2701_MAX_KEY_LENGTH                      (0x04U)
#define DCM_2701_ATTDELAY                            (0x2710U)
#define DCM_2701_ATTCOUNTER                          (0x01U)
#endif
#if (STD_ON == DCM_SERVICE_28_ENABLED)
#define DCM_28_SUBID_NUM                             (0x0002U)
#define DCM_28_CONTROL_STATE_NUM                     (0x03U)
#define DCM_28_CHANNLE_NUM                           (0x00U)
#endif
#if (STD_ON == DCM_SERVICE_3E_ENABLED)
#define DCM_3E_SUBID                                 (0x0001U)
#endif
#if (STD_ON == DCM_SERVICE_85_ENABLED)
#define DCM_85_SUBID_NUM                             (0x0002U)
#endif
#if (STD_ON == DCM_SERVICE_2F_ENABLED)
#define DCM_2F_MAX_SUB_DID_NUM                       (0x0001U)
#endif
#if (STD_ON == DCM_SERVICE_31_ENABLED)
#define DCM_31_SUBID_NUM                             (0x0005U)
#endif
#if (STD_ON == DCM_SERVICE_14_ENABLED)
#define DCM_14_SUBID_NUM                             (0x0000U)
#endif
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )
#define DCM_22_MAX_DID_LIST_NUM                      (1U)
#define DCM_NUM_DIDS                                 (0x14U)
#define DCM_RAED_ACESS                               (0x01U)
#define DCM_WRITE_ACESS                              (0x02U)
#define DCM_RAED_AND_WRITE_ACESS                     (0x03U)
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) */
#define DCM_CANTP_SUPPORT                            (STD_ON)
#define DCM_DSP_READMEMORY_NUM (0x0000U)
#define DCM_DSP_WRITEMEMORY_NUM (0x0001U)

#define DCM_PROGRM_APPEAR                           (0x01U)
#define DCM_PROGRM_DISAPPEAR                        (0x00U)

#if (STD_ON == DCM_SERVICE_36_ENABLED)
#define DCM_36_PROGRAM_FLASH_NO_FINISH              (0x00U)
#define DCM_36_PROGRAM_FLASH_WAITFINISH             (0x01U)
#endif /* STD_ON == DCM_SERVICE_36_ENABLED */

#if (STD_ON == DCM_SERVICE_37_ENABLED)
#define DCM_37_REQUEST_LENGTH                       (0x00U)
#endif /* STD_ON == DCM_SERVICE_37_ENABLED */

#if ( STD_ON == DCM_SERVICE_01_ENABLED )
#define DCM_01_SUBID                                (8U)
#define DCM_01_SUPPRORTPID (0U)
#endif /* STD_ON == DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
#define DCM_02_SUBID                                (6U)
#define DCM_02_SUPPRORTPID (0U)
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
#define DCM_09_SUBID                                (8U)
#define DCM_09_SUPPRORTPID (0U)
#define OBD_INFOTYPE_MAX_NUM                        (0x06U)
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
#define DCM_2C_SUB_NUM_DIDS                         (3U)
#define DCM_2C_NUM_DIDS (0U)
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if ( STD_ON == DCM_SERVICE_2A_ENABLED )
#define DCM_2A_TRANSMODE_SIZE                       (3U)
#define DCM_2A_UUDT_TXBUFFER_SIZE                   (8U)
#define DCM_2A_MAX_DID_LIST_NUM                      (1U)
#define DCM_2A_TX_CHANNEL_NUM                        (0U)
#define DCM_2A_NUM_DIDS                              (0U)
#define DCM_2A_SCHEDULER_SIZE                        (1U)
#endif /* STD_ON == DCM_SERVICE_2A_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
#define DCM_86_EVENTTYPE_NUM                        (8U)

#define DCM_86_EVENTWINDOWTIME_NUM                  (0U)
#define DCM_ROE_CLEARED                             (0U)
#define DCM_ROE_STOPPED                             (1U)
#define DCM_ROE_EVENT_WINDOW_INFINITE               (1U)
#define DCM_ROE_EVENT_WINDOW_CURRENT_CYCLE          (2U)
#define DCM_ROE_BLOCKSIZE                           (20U)
#define DCM_ROE_BLOCKIDREF                          (0xFFFFU)
#define DCM_ROE_BLOCKINVALIDID                      (0xFFFFU)
#define DCM_ROE_INTERMESSAGETIME                    (1U)
#define DCM_86_EEP_EVENTNUM                         ((DCM_ROE_BLOCKSIZE - sizeof(Dcm_86_DslInfo_st))/sizeof(Dcm_86_InfoData_st))
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

#if (STD_ON == DCM_SERVICE_27_ENABLED)
#define DCM_27_BLOCKSIZE                            DCM_27_SUB_NUM
#define DCM_27_BLOCKIDREF                           (0xFFFFU)
#define DCM_2701_SCURITYLEVEL_INDEX                 (0x00U)
#define DCM_27_BLOCKINVALIDID                       (0xFFFFU)
#endif /* STD_ON == DCM_SERVICE_27_ENABLED */
 

#if (STD_ON == DCM_SERVICE_19_ENABLED)
#define DCM_19_SUBIDNUM                              (0x0005U)
#define DCM_STOP_DTC                                 (0x01U)
#define DCM_NO_STOP_DTC                              (0x00U)
#endif
#if (STD_ON == DCM_SERVICE_29_ENABLED)
#define DCM_29_AUT_CONN_NUM                          (0U)
#define DCM_29_AUT_ROLE_NUM                          (0U)
#define DCM_29_SUBID_NUM                             (0x0009U)
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#if (STD_ON == DCM_SERVICE_35_ENABLED)
#define DCM_35_UPLOAD_BLOCKLEN                       (0x0200U)
#endif /* STD_ON == DCM_SERVICE_35_ENABLED */

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef struct{
    uint16 BlockId;
    uint8 RequestResp;
    uint8 ReadResp;
    uint8 *DataPtr;
    uint8 *DataInitPtr;
    uint16 DataSize;
} Dcm_ReadBlockId_st;

typedef struct Dcm_PROGCONDITIONSTYPE_TAG
{
    uint16  TesterSourceAddr;     /* The client ID (source address). */
    uint8   ProtocolId;           /* The protocol ID. */
    uint8   Sid;                  /* The request SID to be responded to. */
    uint8   SubFuncId;            /* The sub-function ID to be responded to. */
    boolean ReprogrammingRequest; /* Specifies whether an ECU preprogramming is needed
                                 	 (TRUE - ECU reprogramming, FALSE - no ECU reprogramming). */
    boolean ApplUpdated;          /* Specifies whether the application has been updated
                                	 (TRUE - application updated, FALSE - no application updated). */
    boolean ResponseRequired;     /* Specifies whether a response to the SID and sub-function 
	                                 has to be sent (TRUE) or just the requested diagnostic session
          					     	 shall be entered (FALSE). */
} Dcm_ProgConditionsType;

typedef uint8 (*Dcm_CheckRuleRef_p) (void);
typedef uint8 (*Dcm_CheckPreCondition_p) (void);
typedef void (*Dcm_ClearCallBackType_p) (void);

typedef struct
{
    uint32 Dcm_Session;
    uint32 Dcm_Security;
} Dcm_ServiceFilter_st;

typedef struct
{
    uint32 Dcm_AutVal;
    uint8* Dcm_CurrAutState;
} Dcm_AutFilter_st;

typedef struct
{
    PduIdType RxPduId;
    PduIdType TxPduId;
    uint8 RxAdrTyp;
    Dcm_ProtocolType ActiveProtocol;
    uint8 Priority;
    uint16 AuthConnId;
    uint32 ClientSrcAdr;
    boolean SendRcrrpOnTransBoot;
    uint8 ComMChannel;
}Dcm_DslProtocol_st;

typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_ServiceType;
    uint16 Dcm_MinReqLength;
    Dcm_ServiceFilter_st Dcm_Filter;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    void (*Dcm_ServiceProcessorType_p)(void);
    void (*Dcm_ServiceInitType_p)(void);
    void (*Dcm_ServicePostProcessorType_p)(uint8 acParm);
} Dcm_ServiceTableType_st;

typedef struct
{
    const Dcm_ServiceTableType_st *Dcm_DspServiceInfoTable;
} Dcm_DSDInfo_st;

typedef struct
{
    uint16 Dcm_TimeOutP2;
    uint32 Dcm_TimeOutP2Ex;
} Dcm_TimerSettingType_st;

#if ( STD_ON == DCM_SERVICE_01_ENABLED )
typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_MResp;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint32 Dcm_Data_ABCD;
} Dcm_01_ServiceInfoType_st;

typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_RespLen;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    void (*Dcm_PidProcessorType_p)(uint8*, uint16*, uint8);
} Dcm_01_PidType_st;

typedef struct{
    const Dcm_01_ServiceInfoType_st* Dcm_ServiceInfoTable;
    const Dcm_01_PidType_st* Dcm_SupportPidTable;
} Dcm_01_DispatherInfo_st;

typedef enum
{
  DCM_01_NO_MRESQ = DCM_NUM_ZERO,
  DCM_01_MRESQ,
} Service01RESPType_e;
#endif /* STD_ON == DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_MResp;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint32 Dcm_Data_ABCD;
} Dcm_02_ServiceInfoType_st;

typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_RespLen;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint8 (*Dcm_PidProcessorType_p)(uint8*, uint16*, uint8);
    uint8 Dcm_PidDataElement;
} Dcm_02_PidType_st;

typedef struct{
    const Dcm_02_ServiceInfoType_st* Dcm_ServiceInfoTable;
    const Dcm_02_PidType_st* Dcm_SupportPidTable;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_02_PidList;
} Dcm_02_DispatherInfo_st;

typedef enum
{
  DCM_02_NO_MRESQ = DCM_NUM_ZERO,
  DCM_02_MRESQ,
} Service02RESPType_e;
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_MResp;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint32 Dcm_Data_ABCD;
} Dcm_09_ServiceInfoType_st;

typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_RespLen;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    void (*Dcm_PidProcessorType_p)(uint8*, uint16*, uint8);
} Dcm_09_PidType_st;

typedef struct{
    const Dcm_09_ServiceInfoType_st* Dcm_ServiceInfoTable;
    const Dcm_09_PidType_st* Dcm_SupportPidTable;
} Dcm_09_DispatherInfo_st;

typedef enum
{
  DCM_09_NO_MRESQ = DCM_NUM_ZERO,
  DCM_09_MRESQ,
} Service09RESPType_e;
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

#if (STD_ON == DCM_SERVICE_10_ENABLED)
typedef struct
{
    uint8 Dcm_IsBoot;
    uint8 Dcm_BootPos;
} Dcm_BootSettingType_st;
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_TimerSettingType_st Dcm_RespTime;
    uint8 Dcm_DspSessionForBoot;
    uint8 Dcm_CurSession;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_10_ServiceInfoType_st;
typedef struct
{
    const Dcm_10_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_10_DispatherInfo_st;
/* This parameter defines whether this diagnostic session allows to jump to
  Bootloader (OEM Bootloader or System Supplier Bootloader) and determines, 
  from which unit the final response will be sent. */
enum
{
  DCM_NO_BOOT = DCM_NUM_ZERO,  /* This diagnostic session doesn't allow to jump to Bootloader. */
  DCM_OEM_BOOT ,  /* This diagnostic session allows to jump to OEM Bootloader and bootloader sends final response. */
  DCM_OEM_BOOT_RESPAPP,  /* This diagnostic session allows to jump to OEM Bootloader and application sends final response. */
  DCM_SYS_BOOT,  /* This diagnostic session allows to jump to System Supplier Bootloader and bootloader sends final response. */
  DCM_SYS_BOOT_RESPAPP  /* This diagnostic session allows to jump to System Supplier Bootloader and application sends final response. */
};
#endif /* STD_ON == DCM_SERVICE_10_ENABLED */

#if (STD_ON == DCM_SERVICE_11_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_RespToEcuRst;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
}Dcm_11_ServiceInfoType_st;
typedef struct
{
    const Dcm_11_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_11_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_11_ENABLED */

#if (STD_ON == DCM_SERVICE_14_ENABLED)
typedef struct
{
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    Dcm_ClearCallBackType_p Dcm_CallBackRef;
} Dcm_14_ServiceInfoType_st;
typedef struct
{
    const Dcm_14_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_g14DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_14_ENABLED */

#if (STD_ON == DCM_SERVICE_19_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_NeedStopDtc;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    uint16 Dcm_ReqDataLength;
    void (*Dcm_ServiceProcessorType_p)(void);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_19_ServiceInfoType_st;
typedef struct
{
    const Dcm_19_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_19_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_19_ENABLED */
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )

typedef uint8 (*Dcm_CheckValueCallBackType_p) (void);
typedef Std_ReturnType (*Dcm_DidReadData_sync)(uint8* Data);
typedef Std_ReturnType (*Dcm_DidReadData_async)(Dcm_OpStatusType OpStatus, uint8* Data, Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidWriteData_sync)(uint8* Data, Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidWriteData_async)(Dcm_OpStatusType OpStatus, uint8* Data, Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidReadDataLength)(uint16* DataLength);
typedef Std_ReturnType (*Dcm_DidConditionCheckRead_sync)(Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidConditionCheckRead_async)(Dcm_OpStatusType OpStatus,Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidConditionCheckWrite)(Dcm_NegativeResponseCodeType* ErrorCode);

typedef struct
{
	Dcm_DidReadData_sync Dcm_DidReadData_sync;  
	Dcm_DidReadData_async Dcm_DidReadData_async;
}Dcm_DidReadData_st;

typedef struct
{
	Dcm_DidWriteData_sync Dcm_DidWriteData_sync;  
	Dcm_DidWriteData_async Dcm_DidWriteData_async;
}Dcm_DidWriteData_st;

typedef struct
{
	Dcm_DidConditionCheckRead_sync Dcm_DidConditionCheckRead_sync;
	Dcm_DidConditionCheckRead_async Dcm_DidConditionCheckRead_async;
}Dcm_DidConditionCheckRead_st;

typedef enum
{
	USE_BLOCK_ID = 0u,
	USE_DATA_ASYNCH_CLIENT_SERVER,
	USE_DATA_ASYNCH_CLIENT_SERVER_ERROR,
	USE_DATA_ASYNCH_FNC,
	USE_DATA_ASYNCH_FNC_ERROR,
	USE_DATA_ASYNCH_FNC_PROXY,
	USE_DATA_SENDER_RECEIVER,
	USE_DATA_SENDER_RECEIVER_AS_SERVICE,
	USE_DATA_SYNCH_CLIENT_SERVER,
	USE_DATA_SYNCH_FNC,
	USE_DATA_SYNCH_FNC_PROXY
}Dcm_DataUsedPort_e;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_Used;
    uint16 Dcm_Length;
    uint16 Dcm_BlockIdRef;
    uint8 *Dcm_BlockStarAdr;
    uint8 *Dcm_BlockDataPtr;
    uint8 Dcm_RorW;
    Dcm_DataUsedPort_e Dcm_DataUsedPort;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
    Dcm_AutFilter_st Dcm_ReadAutFilter;
    Dcm_ServiceFilter_st Dcm_WriteFilter;
    Dcm_AutFilter_st Dcm_WriteAutFilter;
    Dcm_DidReadData_st Dcm_DidReadData;    
    Dcm_DidReadDataLength Dcm_DidReadDataLength;
    Dcm_DidConditionCheckRead_st Dcm_DidCondCheckRead;
    Dcm_DidWriteData_st Dcm_DidWriteData;
	Dcm_DidConditionCheckWrite Dcm_DidCondCheckWrite;
	Dcm_CheckPreCondition_p Dcm_PreCondition;
}Dcm_22_2E_ServiceInfoType_st;

typedef struct
{
    uint16 *Dcm_22_DidList;
    uint16 *Dcm_22_DidResLen;
    const Dcm_22_2E_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_22_2E_DispatherInfo_st;
#endif

#if (STD_ON == DCM_SERVICE_27_ENABLED)
typedef struct
{
    uint8 AttemptCounter;
} Dcm_27_Security_cfg;

typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_SeedFilter;
    Dcm_ServiceFilter_st Dcm_KeyFilter;
    Dcm_AutFilter_st Dcm_ReadAutFilter;
    uint8 Dcm_NumMaxAttDelay;
    uint16 Dcm_SeedLength;
    uint16 Dcm_KeyLength;
    uint32 Dcm_DelayInvKey;
    Std_ReturnType (*Dcm_GetSeedCallBackType_p)(Dcm_OpStatusType OpStatus, uint8 *Seed, Dcm_NegativeResponseCodeType *ErrorCode);
    Std_ReturnType (*Dcm_SendKeyCallBackType_p)(uint8* Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    Dcm_27_Security_cfg* Dcm_27_SecurityData;
    Std_ReturnType (*Dcm_GetAttemptCounterCallBackType_p)(Dcm_OpStatusType OpStatus, uint8* AttemptCounter);
    Std_ReturnType (*Dcm_SetAttemptCounterCallBackType_p)(Dcm_OpStatusType OpStatus, uint8 AttemptCounter);
}Dcm_27_ServiceInfoType_st;
typedef struct
{
    const Dcm_27_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_27_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_27_ENABLED */
#if (STD_ON == DCM_SERVICE_28_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_28_ServiceInfoType_st;

typedef struct
{
    const uint8* Dcm_ControlStete;
    const Dcm_28_ServiceInfoType_st* Dcm_ServiceInfoTable;
} Dcm_28_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_28_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
typedef struct
{
    uint8 Dcm_CertVerfCallNotifyRef;
    uint8 Dcm_RandSeedCallNotifyRef;
    uint8 Dcm_SignatureGenerateNotifyRef;
    uint8 Dcm_SignatureVerifyNotifyRef;
    uint16 Dcm_ClientCertIdx;
    uint16 Dcm_ConnectionCertIdx;
    uint16 Dcm_ConnectionMainConnectionIdx;
    uint16 Dcm_ECUCertificateKeyElmtIdx;
    uint16 Dcm_ECUCertificateIdx;
    uint16 Dcm_PublicKeyElmtIdx;
    uint16 Dcm_RoleElmtIdx;
    uint16 Dcm_WLDIDElmtIdx;
    uint16 Dcm_WLMemorySelectionElmtIdx;
    uint16 Dcm_WLRIDElementIdx;
    uint16 Dcm_WLServicesElementIdx;
    uint32 Dcm_CertPublicKeyStoreJobIdx;
    uint32 Dcm_ClientChallengeSignJobIdx;
    uint32 Dcm_RandomJobIdx;
    uint32 Dcm_VerifyPOWNJobIdx;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_29_AutConn_st;

typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Used;
    uint16 Dcm_Length;
    Dcm_ServiceFilter_st Dcm_Filter;
    void (*Dcm_ServiceProcessorType_p)(void);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_29_ServiceInfoType_st;

typedef struct
{
    const Dcm_29_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_29_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    Dcm_AutFilter_st Dcm_AutFilter;
    Std_ReturnType (*Dcm_38_Info_Trans)(const Dcm_38_ServiceInfoType_Req* DataInVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Std_ReturnType (*Dcm_38_Info_Capture)(Dcm_38_ServiceInfoType_Res* DataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
} Dcm_38_ServiceInfoType_st;

typedef struct
{
    const Dcm_38_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_38_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#if (STD_ON == DCM_SERVICE_2F_ENABLED)
enum
{
    DCM_2F_SIGNAL_TYPE_FIXED = 0x00U,
    DCM_2F_SIGNAL_TYPE_VARIABLE
};

typedef struct
{
    uint8 Dcm_length_Sub00_Sub01_Sub02;
    uint8 Dcm_length_Sub03;
    uint8 Dcm_length_Mask;
} Dcm_2F_RequestDataLen_st;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_DspDidUsed;
    uint8 Dcm_FixedLength;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_2F_RequestDataLen_st Dcm_Length;
    uint8 (*Dcm_00_IOControlCallBackType_p)(uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    uint8 (*Dcm_01_IOControlCallBackType_p)(Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    uint8 (*Dcm_02_IOControlCallBackType_p)(Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    uint8 (*Dcm_03_IOControlCallBackType_p)(const uint8* DataInVar, uint16 ReqLength, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_2F_ServiceInfoType_st;
typedef struct
{
    const Dcm_2F_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_2F_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */
#if (STD_ON == DCM_SERVICE_31_ENABLED)
enum
{
    DCM_31_SIGNAL_TYPE_FIXED = 0x00U,
    DCM_31_SIGNAL_TYPE_VARIABLE
};

typedef struct
{
    uint16 Dcm_ReqLen;
    uint16 Dcm_ResLen;
} Dcm_ReqResLen_st;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_DspRoutineUsed; 
    uint8 Dcm_FixedLength;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_StarAutFilter;
    Dcm_AutFilter_st Dcm_StopAutFilter;
    Dcm_AutFilter_st Dcm_ReqResultAutFilter;
    Dcm_ReqResLen_st Dcm_StartLen;
    Dcm_ReqResLen_st Dcm_StopLen;
    Dcm_ReqResLen_st Dcm_ReqResultLen;
    Std_ReturnType  (*Dcm_RouteControl_01_p)(const uint8* DataInVar, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16 CurrentLengthDataInVar, uint16* CurrentLengthDataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Std_ReturnType  (*Dcm_RouteControl_02_p)(const uint8* DataInVar, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16 CurrentLengthDataInVar, uint16* CurrentLengthDataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Std_ReturnType  (*Dcm_RouteControl_03_p)(Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16* CurrentLengthDataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
}Dcm_31_ServiceInfoType_st;

typedef struct
{
    const Dcm_31_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_31_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_31_ENABLED */

#if (STD_ON == DCM_SERVICE_3E_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_ReqLen;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_3E_ServiceInfoType_st;

typedef struct
{
    const Dcm_3E_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_3E_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_3E_ENABLED */

#if (STD_ON == DCM_SERVICE_85_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_85_ServiceInfoType_st;

typedef struct
{
    const Dcm_85_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_85_DispatherInfo_st;
#endif  /* STD_ON == DCM_SERVICE_85_ENABLED */
#if ( STD_ON == DCM_SERVICE_34_ENABLED )
typedef struct
{
    uint8 Dcm_DataFormatId;
    uint32 Dcm_MemoryAddress;
    uint32 Dcm_MemorySize;
} Dcm_34_RepeaterProxyContextType_st;

typedef struct
{
    uint8 Dcm_DataFormatId;
    uint32 Dcm_MemoryAddress;
    uint32 Dcm_MemorySize;
    uint8* Dcm_RespBuffer;
    uint16* Dcm_RespBufferLen;
} Dcm_34_ProcessContextType_st;
#endif /* STD_ON == DCM_SERVICE_34_ENABLED */

#if (STD_ON == DCM_SERVICE_35_ENABLED)
typedef struct
{
    uint8 Dcm_DataFormatId;
    uint8 Dcm_AddrAndLenFmtId;
    uint32 Dcm_MemoryAddress;
    uint32 Dcm_MemorySize;
} Dcm_35_RepeaterProxyContextType_st;
#endif /* STD_ON == DCM_SERVICE_35_ENABLED */

typedef struct
{
    uint32 Dcm_MemoryAddress_Low;
    uint32 Dcm_MemoryAddress_High;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_DspMemoryInfoType_st;

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
typedef struct
{
    uint32 Dcm_MemAddr;
    uint32 Dcm_MemSize;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
	Dcm_AutFilter_st Dcm_AutFilter;
} Dcm_2C_DDDid_Info_st;
typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_DDDidMaxElmt;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
	Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_2C_DDDid_Info_st* Dcm_2C_DDDid_Info;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_2C_ServiceInfoType_st;
typedef struct
{
    const uint8* Dcm_SubServiceInfoTable;
    const Dcm_2C_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_2C_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_2A_ENABLED)
typedef struct
{
    uint16 Dcm_LocPduIdx;
    uint16 Dcm_TxPduId;
} Dcm_2A_Channel_st;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_Used;
    uint16 Dcm_Length;
    Dcm_DataUsedPort_e Dcm_DataUsedPort;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_DidReadData_st Dcm_DidReadData;
    Dcm_DidReadDataLength Dcm_DidReadDataLength;
    Dcm_DidConditionCheckRead_st Dcm_DidCondCheckRead;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_2A_ServiceInfoType_st;

typedef struct
{
    const Dcm_2A_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_2A_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_2A_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
typedef struct
{
    PduIdType RxPduId;
    PduIdType TxPduId;
    uint32 ClientSrcAddr;
} Dcm_86_DslInfo_st;

typedef struct
{
    uint8 Dcm_EventId;
    uint8 Dcm_EventState; /* EventState: Start, Stop, Clear. */
    uint8 Dcm_EventWndTime;
    uint8 Dcm_StorageStatus;
    uint8 Dcm_EventMask; /* EventType = onDTCStatusChange */
    uint16 Dcm_DidValue; /* EventType = onChangeOfDataIdentifier */
} Dcm_86_InfoData_st;

typedef struct
{
    Dcm_86_DslInfo_st Dcm_DslInfo;
    Dcm_86_InfoData_st Dcm_InfoData[DCM_86_EEP_EVENTNUM];
} Dcm_86_NvMInfo_st;

typedef struct {
	union
	{
		uint8 NvMRamData[DCM_ROE_BLOCKSIZE];
		Dcm_86_NvMInfo_st NvMInfoData;
	}NvmInfo;
}Dcm_86_NvMEventInfo_st;

typedef struct
{
	uint8 Dcm_TransType; /* DcmDslProtocolTransType. */
    uint8 Dcm_Priority;
    PduIdType Dcm_RxPduId;
    PduIdType Dcm_TxPduId;
} Dcm_86_DslProtocol_st;

typedef struct
{
    uint8 Dcm_EventType;
    uint8 Dcm_MsgLength; /* Request message length except the service ID( one byte). */
} Dcm_86_RequestMsg_st;

typedef struct
{
    uint8 Dcm_EventID;
    uint8 Dcm_EventInitStatus;
	uint8 Dcm_DidValid;
    uint16 Dcm_DidValue;
} Dcm_86_ServiceInfoType_st;

typedef struct
{
    const Dcm_86_ServiceInfoType_st* Dcm_ServiceInfoTable;
} Dcm_86_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
extern VAR(uint8, DCM_VAR_INIT) Dcm_DslBuffer[DCM_DSL_BUFFERLEN];
extern VAR(Dcm_ReadBlockId_st, DCM_VAR_INIT) Dcm_ReadBlockId[DCM_READ_BLOCK_NUM + 1];
extern VAR(uint32, DCM_VAR_INIT) Dcm_ProgrammingLength;

#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) )
extern VAR(uint16, DCM_VAR_INIT) Dcm_22_DidList[DCM_22_MAX_DID_LIST_NUM];
extern VAR(uint16, DCM_VAR_INIT) Dcm_22_DidResLen[DCM_22_MAX_DID_LIST_NUM];
 
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF187Buffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF18ABuffer[10U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF197Buffer[10U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF189Buffer[21U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF089Buffer[21U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF193Buffer[8U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF195Buffer[8U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF18CBuffer[14U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF180Buffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF190Buffer[17U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF010Buffer[8U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF15ABuffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF15BBuffer[10U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidCE00Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidCF00Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidCF01Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidCF02Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidCF03Buffer[3U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidCF04Buffer[3U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0010Buffer[1U];
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) */

#if (STD_ON == DCM_SERVICE_27_ENABLED)
extern VAR(uint32, DCM_VAR_INIT) Dcm_27_TimerEngine[DCM_27_SUB_NUM + 1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_security_key[DCM_27_MAX_SEED_LENGTH + 1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_security_seed[DCM_27_MAX_SEED_LENGTH + 1U];
extern VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_Data[DCM_27_SUB_NUM + 1U];
extern VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_INIT_Data[DCM_27_SUB_NUM + 1U];
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
extern VAR(uint8, DCM_VAR_INIT) Dcm_AuthenticationState[DCM_29_AUT_ROLE_NUM + 1U][DCM_29_AUT_CONN_NUM + 1U];
extern CONST(Dcm_29_AutConn_st, DCM_CONFIG_DATA) Dcm_29_AutConn[DCM_29_AUT_CONN_NUM + 1U];
extern CONST(Dcm_29_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_29_ServiceInfo[DCM_29_SUBID_NUM + 1U];
extern CONST(Dcm_29_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_29_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
extern CONST(Dcm_38_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_38_ServiceInfo[DCM_38_SUBID_NUM + 1];
extern CONST(Dcm_38_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_38_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
extern CONST(Dcm_ServiceTableType_st, DCM_CONFIG_DATA) Dcm_DspServiceInfoTable[DCM_NUM_SERVICES + 1];
extern CONST(Dcm_DslProtocol_st, DCM_CONFIG_DATA) Dcm_DslProtocol[DCM_DSL_PROTOCOL_NUM + 1];
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_CfgNetConnComMChannelMap[DCM_DSL_CHANNEL_NUM + 1];
extern CONST(Dcm_DSDInfo_st, DCM_CONFIG_DATA) Dcm_gcaDSDInfo;

#if ( STD_ON == DCM_SERVICE_01_ENABLED )
extern CONST(Dcm_01_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_01_PIDInfo[DCM_01_SUBID + 1U];
extern CONST(Dcm_01_PidType_st, DCM_CONFIG_DATA) Dcm_01_SupportPID[DCM_01_SUPPRORTPID + 1U];
extern CONST(Dcm_01_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_01_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
extern CONST(Dcm_02_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_02_PIDInfo[DCM_02_SUBID + 1U];
extern CONST(Dcm_02_PidType_st, DCM_CONFIG_DATA) Dcm_02_SupportPID[DCM_02_SUPPRORTPID + 1U];
extern CONST(Dcm_02_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_02_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
extern CONST(Dcm_09_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_09_PIDInfo[DCM_09_SUBID + 1U];
extern CONST(Dcm_09_PidType_st, DCM_CONFIG_DATA) Dcm_09_SupportPID[DCM_09_SUPPRORTPID + 1U];
extern CONST(Dcm_09_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_09_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

#if ( STD_ON == DCM_SERVICE_10_ENABLED )
extern CONST(Dcm_10_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_10_ServiceInfo[DCM_10_SUBID + 1U];
extern CONST(Dcm_10_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_10_Dispatcher;

#endif /* STD_ON == DCM_SERVICE_10_ENABLED */

#if ( STD_ON == DCM_SERVICE_11_ENABLED )
extern CONST(Dcm_11_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_11_ServiceInfo[DCM_11_SUBID + 1U];
extern CONST(Dcm_11_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_11_Dispatcher;
extern VAR(uint8, DCM_VAR_INIT) Dcm_11_NvMBuf[4];
#endif /* STD_ON == DCM_SERVICE_11_ENABLED */

#if ( STD_ON == DCM_SERVICE_14_ENABLED )
extern CONST(Dcm_14_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_14_ServiceInfo[DCM_14_SUBID_NUM + 1U];
extern CONST(Dcm_g14DispatherInfo_st, DCM_CONFIG_DATA) Dcm_14_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_14_ENABLED */

#if ( STD_ON == DCM_SERVICE_19_ENABLED )
extern CONST(Dcm_19_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_19_ServiceInfo[DCM_19_SUBIDNUM + 1U];
extern CONST(Dcm_19_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_19_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_19_ENABLED */

#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) )
extern CONST(Dcm_22_2E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_22_2E_ServiceInfo[DCM_NUM_DIDS + 1U];
extern CONST(Dcm_22_2E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_22_2E_Dispatcher;
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) */

#if (STD_ON == DCM_SERVICE_27_ENABLED)
extern CONST(Dcm_27_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_27_ServiceInfo[DCM_27_SUB_NUM + 1U];
extern CONST(Dcm_27_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_27_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

#if (STD_ON == DCM_SERVICE_28_ENABLED)
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ChannelId[DCM_28_CHANNLE_NUM + 1U];
extern CONST(Dcm_28_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_28_ServiceInfoTable[DCM_28_SUBID_NUM + 1U];
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ControlState[DCM_28_CONTROL_STATE_NUM];
extern CONST(Dcm_28_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_28_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_28_ENABLED */

#if (STD_ON == DCM_SERVICE_2F_ENABLED)
extern CONST(Dcm_2F_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2F_ServiceInfo[DCM_2F_MAX_SUB_DID_NUM + 1U];
extern CONST(Dcm_2F_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2F_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */

#if (STD_ON == DCM_SERVICE_31_ENABLED)
extern CONST(Dcm_31_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_31_ServiceInfo[DCM_31_SUBID_NUM + 1U];
extern CONST(Dcm_31_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_31_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_31_ENABLED */

#if (STD_ON == DCM_SERVICE_3E_ENABLED)
extern CONST(Dcm_3E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_3E_ServiceInfo[DCM_3E_SUBID + 1U];
extern CONST(Dcm_3E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_3E_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_3E_ENABLED */

#if ( STD_ON == DCM_SERVICE_85_ENABLED )
extern CONST(Dcm_85_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_85_ServiceInfo[DCM_85_SUBID_NUM + 1U];
extern CONST(Dcm_85_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_85_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_85_ENABLED */

extern CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspReadMemoryInfo[DCM_DSP_READMEMORY_NUM + 1U];
extern CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspWriteMemoryInfo[DCM_DSP_WRITEMEMORY_NUM + 1U];

#if (STD_ON == DCM_SERVICE_2A_ENABLED)
extern CONST(Dcm_2A_Channel_st, DCM_CONFIG_DATA) Dcm_2A_Channel[DCM_2A_TX_CHANNEL_NUM + 1U];
extern CONST(uint16, DCM_CONFIG_DATA) Dcm_2A_TransmissionRate[DCM_2A_TRANSMODE_SIZE + 1U];
extern CONST(Dcm_2A_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2A_ServiceInfo[DCM_2A_NUM_DIDS + 1U];
extern CONST(Dcm_2A_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2A_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_2A_ENABLED */

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_2C_SubFunc[DCM_2C_SUB_NUM_DIDS];
extern CONST(Dcm_2C_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2C_ServiceInfo[DCM_2C_NUM_DIDS + 1U];
extern CONST(Dcm_2C_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2C_Dispatcher;


#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
extern CONST(Dcm_86_DslProtocol_st, DCM_CONFIG_DATA) Dcm_86_DslProtocol[DCM_86_ROE_DSL_NUM + 1U];
extern CONST(Dcm_86_RequestMsg_st, DCM_CONFIG_DATA) Dcm_86_RequestMsg[DCM_86_EVENTTYPE_NUM];
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_86_WindowTime[DCM_86_EVENTWINDOWTIME_NUM + 1U];
extern CONST(Dcm_86_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_86_ServiceInfo[DCM_86_EVENT_NUM + 1U];
extern CONST(Dcm_86_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_86_Dispatcher;
extern VAR(Dcm_86_NvMEventInfo_st, DCM_VAR_INIT) Dcm_86_NvMInfo;
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#if ( (STD_ON == DCM_SERVICE_10_ENABLED) || (STD_ON == DCM_SERVICE_28_ENABLED) )
extern FUNC(void, DCM_CODE) Dcm_ControlCommunication(uint8 subfunc, uint8 comtype);
#endif


#endif /* DCM_LCFG_H_ */

