/*
********************************************************************************
*
*  File name:   Dem_Lcfg.h
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: WangJP/20210814
* Change: New
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: LQiao/2023.01.13
* Change: Add Includes.
* Cause: Bugfix
********************************************************************************
*/
#ifndef DEM_LCFG_H_
#define DEM_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Dem_Types.h"
// #include "Rte_Dem.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Configurations of component */
#define DEM_CFG_COMP_NUM                                    (0U)
#define DEM_CFG_MAX_CHILD_COMP_NUM                          (1U)
/* Configurations of Operation Cycles */
#define DEM_CFG_OPCYC_NUM                                   (1U)
/* Configurations of DTC list */
#define DEM_CFG_DTC_NUM                                     (92U)
#define DEM_CFG_DTC_GROUP_NUM                               (0U)
#define DEM_CFG_COMB_DTC_MAX_EVENT_NUM                      (1U)
/* Configurations of Supported Event Memory */
#define DEM_CFG_EVENT_MEMORY_NUM                            (1U)
#define DEM_CFG_PRIMARY_MAX_NUMBER_EVENT_ENTRY              (10U)
#define DEM_CFG_USER0_MAX_NUMBER_EVENT_ENTRY                (1U)
#define DEM_CFG_USER1_MAX_NUMBER_EVENT_ENTRY                (1U)
#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY                      (10U)
/* Configurations of Event list ***/
#define DEM_CFG_EVENT_NUM                                   (92U)
#define DEM_CFG_EVENT_ID_MAX                                (92U)
#define DEM_CFG_EVENT_MAX_REF_INDICATOR_NUM                 (1U)
/* Configurations of Debounce counter */
#define DEM_CFG_DEBOUNCE_COUNTER_NUM                        (1U)
#define DEM_CFG_DEBOUNCE_TIME_NUM                           (0U)
/* Configurations of OBD DTC */
#define DEM_CFG_OBD_DTC_NUM                                 (0U)
#define DEM_CFG_OBD_PID_DATA_NUM                            (0U)
#define DEM_CFG_PID_MAX_REF_DATA_ELEMENT_NUM                (1U)
/* Configurations of data element */
#define DEM_CFG_DATA_ELEMENT_NUM                            (1U)
#define DEM_CFG_DID_NUM                                     (0U)
#define DEM_CFG_DID_MAX_REF_DATA_ELEMENT_NUM                (1U)
#define DEM_CFG_EXDATA_NUM                                  (1U)
#define DEM_CFG_EXDATA_MAX_REF_EXDATA_RECORD_NUM            (1U)
#define DEM_CFG_EXDATA_RECORD_NUM                           (1U)
#define DEM_CFG_EXDATA_MAX_REF_DATA_ELEMENT_NUM             (1U)
#define DEM_CFG_FFDATA_NUM                                  (0U)
#define DEM_CFG_FFDATA_MAX_REF_DID_NUM                      (1U)
#define DEM_CFG_FFDATA_RECORDNUM_NUM                        (0U)
#define DEM_CFG_FFDATA_MAX_REF_RECORD_NUM                   (1U)
#define DEM_CFG_FFDATA_RECORD_NUM                           (0U)
/* Enable Condition Configurations */
#define DEM_CFG_ENCOND_NUM                                  (0U)
#define DEM_CFG_ENCOND_GROUP_NUM                            (0U)
#define DEM_CFG_ENCONDGRP_MAX_REF_ENCOND_NUM                (1U)
/* Storage Condition Configurations */
#define DEM_CFG_STORCOND_NUM                                (0U)
#define DEM_CFG_STORCOND_GROUP_NUM                          (0U)
#define DEM_CFG_STORCONDGRP_MAX_REF_STORCOND_NUM            (1U)
/* Indicator Configurations */
#define DEM_CFG_INDICATOR_NUM                               (0U)
/* Nvm Block Configurations */
#define DEM_CFG_NVM_BLOCK_NUM                               (0U)
/* Callback of DTC status changed Configurations */
#define DEM_CFG_DTC_STATUS_CHANGED_CALLBACK_NUM             (0U)
/* Ratio for OBD Configurations */
#define DEM_CFG_OBD_RATIO_NUM                               (0U)
#define DEM_CFG_MAX_SECOND_FIM_FUNC_NUM                     (1U)
/* OBD DTC status changed callback configurations */
#define DEM_CFG_OBDDTC_STATUS_CHANGED_CALLBACK_NUM          (0U)
/* Dtr configtrations */
#define DEM_CFG_DTR_NUM                                     (0U)

/* Freeze Frame Data/Extended Data max bytes for 1 DTC */
#define DEM_CFG_EXDATA_MAX_BYTES                            (1U)
#define DEM_CFG_FFDATA_MAX_BYTES                            (1U)

/* Configur Event ID */
#define DEM_DTC911716 (1U)
#define DEM_DTC911717 (2U)
#define DEM_DTCC07388 (3U)
#define DEM_DTCC07488 (4U)
#define DEM_DTCC07588 (5U)
#define DEM_DTCC07688 (6U)
#define DEM_DTCC07788 (7U)
#define DEM_DTCC07888 (8U)
#define DEM_DTCC07988 (9U)
#define DEM_DTCC07A88 (10U)
#define DEM_DTCC07B88 (11U)
#define DEM_DTCC07C88 (12U)
#define DEM_DTCC07D88 (13U)
#define DEM_DTCC07E88 (14U)
#define DEM_DTCC07F88 (15U)
#define DEM_DTCC10187 (16U)
#define DEM_DTCC10387 (17U)
#define DEM_DTCC11087 (18U)
#define DEM_DTCC11187 (19U)
#define DEM_DTCC12287 (20U)
#define DEM_DTCC12787 (21U)
#define DEM_DTCC13187 (22U)
#define DEM_DTCC13487 (23U)
#define DEM_DTCC14087 (24U)
#define DEM_DTCC14687 (25U)
#define DEM_DTCC15187 (26U)
#define DEM_DTCC15987 (27U)
#define DEM_DTCC15C87 (28U)
#define DEM_DTCC16487 (29U)
#define DEM_DTCC16B87 (30U)
#define DEM_DTCC19987 (31U)
#define DEM_DTCC19B87 (32U)
#define DEM_DTCC1BB87 (33U)
#define DEM_DTCC20087 (34U)
#define DEM_DTCC20187 (35U)
#define DEM_DTCC20287 (36U)
#define DEM_DTCC20887 (37U)
#define DEM_DTCC21087 (38U)
#define DEM_DTCC21187 (39U)
#define DEM_DTCC21400 (40U)
#define DEM_DTCC23087 (41U)
#define DEM_DTCC27A87 (42U)
#define DEM_DTCC29387 (43U)
#define DEM_DTCD10088 (44U)
#define DEM_DTCD20087 (45U)
#define DEM_DTCD20187 (46U)
#define DEM_DTCD20287 (47U)
#define DEM_DTCD20387 (48U)
#define DEM_DTCD20487 (49U)
#define DEM_DTCD20587 (50U)
#define DEM_DTCD20687 (51U)
#define DEM_DTCD20787 (52U)
#define DEM_DTCD20887 (53U)
#define DEM_DTCD20987 (54U)
#define DEM_DTCD20A87 (55U)
#define DEM_DTCD20B87 (56U)
#define DEM_DTCD20D87 (57U)
#define DEM_DTCD20E87 (58U)
#define DEM_DTCD20F87 (59U)
#define DEM_DTCD21087 (60U)
#define DEM_DTCD21187 (61U)
#define DEM_DTCD21287 (62U)
#define DEM_DTCD21387 (63U)
#define DEM_DTCD21487 (64U)
#define DEM_DTCD21587 (65U)
#define DEM_DTCD21687 (66U)
#define DEM_DTCD21787 (67U)
#define DEM_DTCD21887 (68U)
#define DEM_DTCD21987 (69U)
#define DEM_DTCD21A87 (70U)
#define DEM_DTCD21B87 (71U)
#define DEM_DTCD21C87 (72U)
#define DEM_DTCD21D87 (73U)
#define DEM_DTCD21E87 (74U)
#define DEM_DTCD21F87 (75U)
#define DEM_DTCD23187 (76U)
#define DEM_DTCD23287 (77U)
#define DEM_DTCD23387 (78U)
#define DEM_DTCD23487 (79U)
#define DEM_DTCD23587 (80U)
#define DEM_DTCD23687 (81U)
#define DEM_DTCD23787 (82U)
#define DEM_DTCD23887 (83U)
#define DEM_DTCD23987 (84U)
#define DEM_DTCD23A87 (85U)
#define DEM_DTCD23B87 (86U)
#define DEM_DTCD23C87 (87U)
#define DEM_DTCD23D87 (88U)
#define DEM_DTCD23E87 (89U)
#define DEM_DTCD23F87 (90U)
#define DEM_DTCD24087 (91U)
#define DEM_DTCD24187 (92U)
#define DEM_DemDTC_911716 (9508630U)
#define DEM_DemDTC_911717 (9508631U)
#define DEM_DemDTC_C07388 (12612488U)
#define DEM_DemDTC_C07488 (12612744U)
#define DEM_DemDTC_C07588 (12613000U)
#define DEM_DemDTC_C07688 (12613256U)
#define DEM_DemDTC_C07788 (12613512U)
#define DEM_DemDTC_C07888 (12613768U)
#define DEM_DemDTC_C07988 (12614024U)
#define DEM_DemDTC_C07A88 (12614280U)
#define DEM_DemDTC_C07B88 (12614536U)
#define DEM_DemDTC_C07C88 (12614792U)
#define DEM_DemDTC_C07D88 (12615048U)
#define DEM_DemDTC_C07E88 (12615304U)
#define DEM_DemDTC_C07F88 (12615560U)
#define DEM_DemDTC_C10187 (12648839U)
#define DEM_DemDTC_C10387 (12649351U)
#define DEM_DemDTC_C11087 (12652679U)
#define DEM_DemDTC_C11187 (12652935U)
#define DEM_DemDTC_C12287 (12657287U)
#define DEM_DemDTC_C12787 (12658567U)
#define DEM_DemDTC_C13187 (12661127U)
#define DEM_DemDTC_C13487 (12661895U)
#define DEM_DemDTC_C14087 (12664967U)
#define DEM_DemDTC_C14687 (12666503U)
#define DEM_DemDTC_C15187 (12669319U)
#define DEM_DemDTC_C15987 (12671367U)
#define DEM_DemDTC_C15C87 (12672135U)
#define DEM_DemDTC_C16487 (12674183U)
#define DEM_DemDTC_C16B87 (12675975U)
#define DEM_DemDTC_C19987 (12687751U)
#define DEM_DemDTC_C19B87 (12688263U)
#define DEM_DemDTC_C1BB87 (12696455U)
#define DEM_DemDTC_C20087 (12714119U)
#define DEM_DemDTC_C20187 (12714375U)
#define DEM_DemDTC_C20287 (12714631U)
#define DEM_DemDTC_C20887 (12716167U)
#define DEM_DemDTC_C21087 (12718215U)
#define DEM_DemDTC_C21187 (12718471U)
#define DEM_DemDTC_C21400 (12719104U)
#define DEM_DemDTC_C23087 (12726407U)
#define DEM_DemDTC_C27A87 (12745351U)
#define DEM_DemDTC_C29387 (12751751U)
#define DEM_DemDTC_D10088 (13697160U)
#define DEM_DemDTC_D20087 (13762695U)
#define DEM_DemDTC_D20187 (13762951U)
#define DEM_DemDTC_D20287 (13763207U)
#define DEM_DemDTC_D20387 (13763463U)
#define DEM_DemDTC_D20487 (13763719U)
#define DEM_DemDTC_D20587 (13763975U)
#define DEM_DemDTC_D20687 (13764231U)
#define DEM_DemDTC_D20787 (13764487U)
#define DEM_DemDTC_D20887 (13764743U)
#define DEM_DemDTC_D20987 (13764999U)
#define DEM_DemDTC_D20A87 (13765255U)
#define DEM_DemDTC_D20B87 (13765511U)
#define DEM_DemDTC_D20D87 (13766023U)
#define DEM_DemDTC_D20E87 (13766279U)
#define DEM_DemDTC_D20F87 (13766535U)
#define DEM_DemDTC_D21087 (13766791U)
#define DEM_DemDTC_D21187 (13767047U)
#define DEM_DemDTC_D21287 (13767303U)
#define DEM_DemDTC_D21387 (13767559U)
#define DEM_DemDTC_D21487 (13767815U)
#define DEM_DemDTC_D21587 (13768071U)
#define DEM_DemDTC_D21687 (13768327U)
#define DEM_DemDTC_D21787 (13768583U)
#define DEM_DemDTC_D21887 (13768839U)
#define DEM_DemDTC_D21987 (13769095U)
#define DEM_DemDTC_D21A87 (13769351U)
#define DEM_DemDTC_D21B87 (13769607U)
#define DEM_DemDTC_D21C87 (13769863U)
#define DEM_DemDTC_D21D87 (13770119U)
#define DEM_DemDTC_D21E87 (13770375U)
#define DEM_DemDTC_D21F87 (13770631U)
#define DEM_DemDTC_D23187 (13775239U)
#define DEM_DemDTC_D23287 (13775495U)
#define DEM_DemDTC_D23387 (13775751U)
#define DEM_DemDTC_D23487 (13776007U)
#define DEM_DemDTC_D23587 (13776263U)
#define DEM_DemDTC_D23687 (13776519U)
#define DEM_DemDTC_D23787 (13776775U)
#define DEM_DemDTC_D23887 (13777031U)
#define DEM_DemDTC_D23987 (13777287U)
#define DEM_DemDTC_D23A87 (13777543U)
#define DEM_DemDTC_D23B87 (13777799U)
#define DEM_DemDTC_D23C87 (13778055U)
#define DEM_DemDTC_D23D87 (13778311U)
#define DEM_DemDTC_D23E87 (13778567U)
#define DEM_DemDTC_D23F87 (13778823U)
#define DEM_DemDTC_D24087 (13779079U)
#define DEM_DemDTC_D24187 (13779335U)
#define DEM_DemOperationCyclePower (0U)
#define DEM_DemOperationCycleIgn (1U)

#define DEM_CFG_J1939DTC_STATUS_CHANGED_CALLBACK_NUM        (0U)
#define DEM_CFG_J1939NODE_NUM                               (255U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef struct
{
    uint8  compPriIgnor;
    uint8  childCompIdx[DEM_CFG_MAX_CHILD_COMP_NUM];
    void   (*DemComponentFailedCallbackFnc)(Dem_ComponentIdType ComponentId, boolean ComponentFailedStauts);
} Dem_ConfigComponent_st;

typedef struct
{
    uint8 acCycleId;        /* Opercycle Id. */
    uint8 acCycType;        /* Opercycle Type */
    uint8 acCycleStartType; /* Opercycle Start Type. */
    uint8 acCycleEndType;   /* Opercycle End Type. */
} Dem_ConfigOperCycle_st;

typedef struct
{
    uint8   acFuncId;            /* DTC assigned Function unit id */
    uint8   acDtcSeverity;        /* DTC Severity. */
    uint8   acWwhObdClass;       /* WWH-OBD class */
    uint16  acObdDtcIdx;         /* Assigned Obd DTC */
    uint16  combEvtIdx[DEM_CFG_COMB_DTC_MAX_EVENT_NUM]; /* Combined event idx list */
    
    /* start of Dtc Attributes define */
    boolean acAgeAllow;         /* Switch of aging allowed or not */
    uint8   acAgeCycThrs;       /* Aging cycles needs to delete event, 1~255 */
    uint8   acAgeCycThrsTFSLC;  /* Aging cycles needs to reset bit TFSLC */
    uint8   acDtcSign;
    uint8   acFdcEvtMemStorThrs;/* Threshold of FDC to capture FF and EX data */
    boolean acImdiStor;         /* Switch of immediate Nvm storage */
    uint8   acAgeOpcycIdx;      /* Operation cycle used for aging refer index number */
    uint8   acExDataClsIdx;     /* Extend data class refer index number */
    uint8   acFfDataRecClsIdx;  /* Freeze frame record data class refer index number */
    uint8   acJ1939DtcNdId;
    uint8   acWobdFfDataClsIdx; /* WWH-OBD Freeze frame data class refer index number */
    uint8   acEvtMemIdx[DEM_CFG_EVENT_MEMORY_NUM];      /* Event memory Index */
    /* end of Dtc Attributes define */
} Dem_ConfigDTCTable_st;

/* Event Config Struct. */
typedef struct
{
    uint8    acCompPri;         /* Component priority within ref DemComponent */
    uint16   awEvtId;           /* Event ID, start from 1 */
    uint8    acEvtKind;         /* Event kind */
    uint8    acEvtRepBhv;       /* Event report behavior */
    uint16   awEvtComIdx;       /* Component class index */
    uint16   awEvtEnCondGrpIdx; /* Enable condition group index */
    uint8    acEvtOpcycIdx;     /* Event operation cycle index */
    uint8    acEvtStorCondGrpIdx;  /* Event storage condition group index */
    uint8    acIndiIdx[DEM_CFG_EVENT_MAX_REF_INDICATOR_NUM];          /* Referred Indicator Index */
    uint8    acIndiFccThrs[DEM_CFG_EVENT_MAX_REF_INDICATOR_NUM];     /* Indicator failure cycle counter threshold */
    uint8    acIndiHccThrs[DEM_CFG_EVENT_MAX_REF_INDICATOR_NUM];     /* Indicator healing cycle counter threshold */
    uint8    acCallbackClrEvtBhv;     /* Clear event behavior on if call back function allow clear action */
    uint8    (*DemCallbackGetFDC)(sint8 *FaultDetectionCounter);    /* DemCallbackGetFDCFnc */
    uint8    (*DemCallbackClearAllowed_p)(boolean *Allowed);    /* DemCallbackClearEventAllowed */
    void     (*DemCallbackEventDataChanged_p)(Dem_EventIdType EventId);    /* DemCallbackEventDataChanged */
    void     (*DemCallbackEventStatusChanged_p)(Dem_EventIdType EventId, Dem_UdsStatusByteType DTCStatusOld, Dem_UdsStatusByteType DTCStatusNew);  /* DemCallbackEventStatusChanged  */
    void     (*DemCallbackInitMonitor_p)(Dem_InitMonitorReasonType Reason);    /* CallbackInitMonitorForEvent */
} Dem_ConfigEventTable_st;

/* Debounce Algorithm Configration Struct */
typedef struct
{
    uint8    acDebBhv;            /* Debounce behavior */
    boolean  acDebCntStor;        /* Debounce counter storage */
} Dem_ConfigDebCntBasedTable_st;

typedef struct
{
    uint8    acDebBhv;            /* Debounce behavior */
} Dem_ConfigDebTimBasedTable_st;

typedef struct
{
    uint8    acEvtMemId;            /* Event memory id */
    uint8    acEvtMemType;          /* Event memory type: primary or user defined */
    uint8    acEvtMemMaxEntry;      /* Max entries for the event memory */
} Dem_ConfigEventMemoryTable_st;

/* OBD related Configurations */
typedef struct
{
    boolean acConsidePto;           /* Whether consider the pto status */
    uint8   acObbEvtReadinessGrp;   /* Readiness group */
    uint32  awJ1939DtcVal;
} Dem_ConfigObdDtcTable_st;

/* PID Configurations */
typedef struct
{
    uint8 pidId;
    uint8 pidDataElementIdx[DEM_CFG_PID_MAX_REF_DATA_ELEMENT_NUM];
} Dem_CfgObdPidDataTable_st;

/* Freeze Frame and Extended Data */
typedef struct
{
    uint8   acDataType;             /* Data element type: internal or CS, SR currently not support */
    uint8   acDataSize;             /* Data element size */
    uint8   acInterDataElement;     /* Internal date element */
    boolean acDataUsePort;          /* For CS data element, whether generate a R-port to obtain data from interface */
    uint8   (*DataElementReadPortPtr)(uint8 *DataBufPtr);  /* For CS data element, if acDataUsePort selected, Dem will generate a R-port interface to read data */
    uint8   (*DataElementReadFncPtr)(uint8 *DataBufPtr);  /* For CS data element, the interface from SWC or BSW to read data */
} Dem_ConfigDataElementTable_st;

typedef struct
{
    uint16  acDid;                 /* Did identifier */
    uint8   acDataElementIdx[DEM_CFG_DID_MAX_REF_DATA_ELEMENT_NUM];    /* the index of reference data elements */
    uint16  acDataLen;             /* Data length */
} Dem_ConfigDidTable_st;

typedef struct
{
    uint8   acExDataRecordIdx[DEM_CFG_EXDATA_MAX_REF_EXDATA_RECORD_NUM];
    uint8   acExDataRecLen;          /* Extended data record data length */
} Dem_ConfigExDataTable_st;

typedef struct
{
    uint8   acExDataRecNum;           /* Extended data record number */
    uint8   acExDataRecTrig;          /* Trigger to store this extended data record */
    uint8   acExDataRecUpdate;        /* Whether store the exdata record when the trigger is fulfilled */
    uint8   acExDataElementIdx[DEM_CFG_EXDATA_MAX_REF_DATA_ELEMENT_NUM];
    uint8   acExDataLen;              /* Extended data length */
} Dem_ConfigExDataRecordTable_st;

typedef struct
{
    uint8   acFfDataDidIdx[DEM_CFG_FFDATA_MAX_REF_DID_NUM];
    uint8   acFfDataLen;     /* FF data length */
} Dem_ConfigFfDataTable_st;

typedef struct
{
    uint8   acFfDataRecordIdx[DEM_CFG_FFDATA_MAX_REF_RECORD_NUM];
} Dem_ConfigFfDataRecordNumTable_st;

typedef struct
{
    uint8   acFfDataRecordNum;
    uint8   acFfDataRecTrig;          /* Trigger to store this extended data record */
    uint8   acFfDataRecUpdate;        /* Whether store the exdata record when the trigger is fulfilled */
} Dem_ConfigFfDataRecordTable_st;

/* Enable Condition Configurations */
typedef struct
{
    uint8   acEnCondId;                /* Enable condition ID */
} Dem_ConfigEnCondTable_st;

typedef struct
{
    uint8   acEnCondIdx[DEM_CFG_ENCONDGRP_MAX_REF_ENCOND_NUM];               /* Index of Referenced Enable condition */
} Dem_ConfigEnCondGrpTable_st;

/* Storage Condition Configurations */
typedef struct
{
    uint8   acStorCondId;                 /* Storage Condition ID */
    boolean acStorCondSt;                 /* Storage Condition status */
    uint16  acStorCondRepEvtIdx;           /* Storage Condition replacement event index */
} Dem_ConfigStorCondTable_st;

typedef struct
{
    uint8   acStorCondIdx[DEM_CFG_STORCONDGRP_MAX_REF_STORCOND_NUM];               /* Index of Referenced storage condition */
} Dem_ConfigStorCondGrpTable_st;

/* Callback of DTC status changed Configurations */
typedef struct
{
    void    (*DemCallbackDTCStatusChanged_p)(uint32 DTC, Dem_UdsStatusByteType DTCStatusOld, Dem_UdsStatusByteType DTCStatusNew);
} Dem_ConfigDTCStatusChangedPtrTable_st;

/* Ratio for OBD Configurations */
typedef struct
{
    uint8   acIuprDenGrp;
    uint8   acIuprGrp;
    uint16  awRatioId;
    uint8   acRatioKind;
    uint16  awEvtIdx;
    uint16  awPriFimFuncIdx;
    uint16  awSecFimFuncIdx[DEM_CFG_MAX_SECOND_FIM_FUNC_NUM];
} Dem_ConfigObdRatioTable_st;

/* OBD DTC status changed callback configurations */
typedef struct
{
    void    (*DemCallbackDTCStatusChanged_p)(uint32 DTC, Dem_UdsStatusByteType DTCStatusOld, Dem_UdsStatusByteType DTCStatusNew);
} Dem_ConfigObdDTCStatusChangedPtrTable_st;

/* Dtrs Configurations */
typedef struct
{
    sint32 dtrCompuDenominator0;
    sint32 dtrCompuNumerator0;
    sint32 dtrCompuNumerator1;
    uint16 dtrId;
    uint8  dtrMid;
    uint8  dtrTid;
    uint8  dtrUasid;
    uint8  dtrUpdatekind;
    uint16 dtrEventRefIdx;
} Dem_ConfigDtrTable_st;

/* Callback of J1939DTC status changed Configurations */
typedef struct
{
    void    (*DemCallbackDTCStatusChanged_p)(uint32 DTC, Dem_UdsStatusByteType DTCStatusOld, Dem_UdsStatusByteType DTCStatusNew);
} Dem_ConfigJ1939DTCStatusChangedPtrTable_st;

typedef struct
{
    uint8  J1939NmNdRefld;
} Dem_ConfigJ1939NodeTable_st;

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
extern CONST(Dem_ConfigComponent_st, DEM_CONFIG_DATA) Dem_ConfigComponentTable[DEM_CFG_COMP_NUM + 1U];
extern CONST(Dem_ConfigOperCycle_st, DEM_CONFIG_DATA) Dem_CfgOperationCycleTable[DEM_CFG_OPCYC_NUM + 1U];
extern CONST(Dem_ConfigDTCTable_st, DEM_CONFIG_DATA) Dem_CfgDTCTable[DEM_CFG_DTC_NUM + 1U];
extern CONST(uint32, DEM_CONFIG_DATA) Dem_CfgDTCGrpTable[DEM_CFG_DTC_GROUP_NUM + 1U];
extern CONST(Dem_ConfigEventTable_st, DEM_CONFIG_DATA) Dem_CfgEventTable[DEM_CFG_EVENT_NUM + 1U];
extern CONST(uint16, DEM_CONFIG_DATA) Dem_CfgEventIdTableIndex[DEM_CFG_EVENT_ID_MAX + 1U];
extern CONST(Dem_ConfigDebCntBasedTable_st, DEM_CONFIG_DATA) Dem_CfgDebCounterTable[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];
extern CONST(Dem_ConfigDebTimBasedTable_st, DEM_CONFIG_DATA) Dem_CfgDebTimeTable[DEM_CFG_DEBOUNCE_TIME_NUM + 1U];
extern CONST(Dem_ConfigEventMemoryTable_st, DEM_CONFIG_DATA) Dem_CfgEventMemoryTable[DEM_CFG_EVENT_MEMORY_NUM + 1U];
extern CONST(Dem_ConfigObdDtcTable_st, DEM_CONFIG_DATA) Dem_CfgObdDTCTable[DEM_CFG_OBD_DTC_NUM + 1U];
extern CONST(Dem_CfgObdPidDataTable_st, DEM_CONFIG_DATA) Dem_CfgObdPidDataTable[DEM_CFG_OBD_PID_DATA_NUM + 1U];
extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgObdPidDataIndexTable[DEM_CFG_OBD_PID_DATA_NUM + 1U];
extern CONST(Dem_ConfigDataElementTable_st, DEM_CONFIG_DATA) Dem_CfgDataElementTable[DEM_CFG_DATA_ELEMENT_NUM + 1U];
extern CONST(Dem_ConfigDidTable_st, DEM_CONFIG_DATA) Dem_CfgDidTable[DEM_CFG_DID_NUM + 1U];
extern CONST(Dem_ConfigExDataTable_st, DEM_CONFIG_DATA) Dem_CfgExDataTable[DEM_CFG_EXDATA_NUM + 1U];
extern CONST(Dem_ConfigExDataRecordTable_st, DEM_CONFIG_DATA) Dem_CfgExDataRecordTable[DEM_CFG_EXDATA_RECORD_NUM + 1U];
extern CONST(Dem_ConfigFfDataTable_st, DEM_CONFIG_DATA) Dem_CfgFfDataTable[DEM_CFG_FFDATA_NUM + 1U];
extern CONST(Dem_ConfigFfDataRecordNumTable_st, DEM_CONFIG_DATA) Dem_CfgFfDataRecordNumTable[DEM_CFG_FFDATA_RECORDNUM_NUM + 1U];
extern CONST(Dem_ConfigFfDataRecordTable_st, DEM_CONFIG_DATA) Dem_CfgFfDataRecordTable[DEM_CFG_FFDATA_RECORD_NUM + 1U];
extern CONST(Dem_ConfigEnCondTable_st, DEM_CONFIG_DATA) Dem_CfgEnConditionTable[DEM_CFG_ENCOND_NUM + 1U];
extern CONST(Dem_ConfigEnCondGrpTable_st, DEM_CONFIG_DATA) Dem_CfgEnConditionGrpTable[DEM_CFG_ENCOND_GROUP_NUM + 1U];
extern CONST(Dem_ConfigStorCondTable_st, DEM_CONFIG_DATA) Dem_CfgStorConditionTable[DEM_CFG_STORCOND_NUM + 1U];
extern CONST(Dem_ConfigStorCondGrpTable_st, DEM_CONFIG_DATA) Dem_CfgStorConditionGrpTable[DEM_CFG_STORCOND_GROUP_NUM + 1U];
extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgIndicatorTable[DEM_CFG_INDICATOR_NUM + 1U];
extern CONST(uint16, DEM_CONFIG_DATA) Dem_CfgNvmBlockTable[DEM_CFG_NVM_BLOCK_NUM + 1U];
extern CONST(Dem_ConfigDTCStatusChangedPtrTable_st, DEM_CONFIG_DATA) Dem_CfgDTCStatsuChangedPtrTable[DEM_CFG_DTC_STATUS_CHANGED_CALLBACK_NUM + 1U];
extern CONST(Dem_ConfigObdRatioTable_st, DEM_CONFIG_DATA) Dem_ConfigObdRatioTable[DEM_CFG_OBD_RATIO_NUM + 1U];
extern CONST(Dem_ConfigObdDTCStatusChangedPtrTable_st, DEM_CONFIG_DATA) Dem_CfgObdDTCStatusChangedPtrTable[DEM_CFG_OBDDTC_STATUS_CHANGED_CALLBACK_NUM + 1U];
extern CONST(Dem_ConfigDtrTable_st, DEM_CONFIG_DATA) Dem_ConfigDtrTable[DEM_CFG_DTR_NUM + 1U];

extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgEvtIndiBhv[DEM_CFG_EVENT_NUM + 1U][DEM_CFG_EVENT_MAX_REF_INDICATOR_NUM];
extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgDtcPriority[DEM_CFG_DTC_NUM + 1U];
extern CONST(uint32, DEM_CONFIG_DATA) Dem_CfgObdDtcValue[DEM_CFG_OBD_DTC_NUM + 1U];
extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgEvtFcThrs[DEM_CFG_EVENT_NUM + 1U];
extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgEvtDebCntCls[DEM_CFG_EVENT_NUM + 1U];
extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgEvtDebCntIdx[DEM_CFG_EVENT_NUM + 1U];
extern CONST(uint16, DEM_CONFIG_DATA) Dem_CfgEvtDtcIdx[DEM_CFG_EVENT_NUM + 1U];
extern CONST(uint32, DEM_CONFIG_DATA) Dem_CfgDebTimFailThrs[DEM_CFG_DEBOUNCE_TIME_NUM + 1U];
extern CONST(uint32, DEM_CONFIG_DATA) Dem_CfgDebTimPassThrs[DEM_CFG_DEBOUNCE_TIME_NUM + 1U];
extern CONST(uint8, DEM_CONFIG_DATA) Dem_CfgDtcFfDataClsIdx[DEM_CFG_DTC_NUM + 1U];

extern CONST(Dem_ConfigJ1939DTCStatusChangedPtrTable_st, DEM_CONFIG_DATA) Dem_CfgJ1939DTCStatusChangedPtrTable[DEM_CFG_J1939DTC_STATUS_CHANGED_CALLBACK_NUM + 1U];
extern CONST(Dem_ConfigJ1939NodeTable_st, DEM_CONFIG_DATA) Dem_CfgJ1939NodeDTCTable[DEM_CFG_J1939NODE_NUM + 1U];
/*
*********************************************************************************
*    Global Functions
*********************************************************************************
*/

#endif /* DEM_LCFG_H_ */

