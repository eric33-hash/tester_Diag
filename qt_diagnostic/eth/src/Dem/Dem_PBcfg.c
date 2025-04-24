/*
********************************************************************************
*
*  File name:   Dem_PBcfg.c
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: FanHT/20230101
* Change: New
* Cause: New
********************************************************************************
*/
/*
********************************************************************************
*    Include
********************************************************************************
*/
#include "eth/include/Dem/Dem.h"

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


#define DEM_START_SEC_CONFIG_DATA
// #include "Dem_MemMap.h"
CONST(uint32, DEM_CONFIG_DATA) Dem_CfgUdsDtcValue[DEM_CFG_DTC_NUM + 1U] = 
{
	0x0U,
	0x00911716U,
	0x00911717U,
	0x00C07388U,
	0x00C07488U,
	0x00C07588U,
	0x00C07688U,
	0x00C07788U,
	0x00C07888U,
	0x00C07988U,
	0x00C07A88U,
	0x00C07B88U,
	0x00C07C88U,
	0x00C07D88U,
	0x00C07E88U,
	0x00C07F88U,
	0x00C10187U,
	0x00C10387U,
	0x00C11087U,
	0x00C11187U,
	0x00C12287U,
	0x00C12787U,
	0x00C13187U,
	0x00C13487U,
	0x00C14087U,
	0x00C14687U,
	0x00C15187U,
	0x00C15987U,
	0x00C15C87U,
	0x00C16487U,
	0x00C16B87U,
	0x00C19987U,
	0x00C19B87U,
	0x00C1BB87U,
	0x00C20087U,
	0x00C20187U,
	0x00C20287U,
	0x00C20887U,
	0x00C21087U,
	0x00C21187U,
	0x00C21400U,
	0x00C23087U,
	0x00C27A87U,
	0x00C29387U,
	0x00D10088U,
	0x00D20087U,
	0x00D20187U,
	0x00D20287U,
	0x00D20387U,
	0x00D20487U,
	0x00D20587U,
	0x00D20687U,
	0x00D20787U,
	0x00D20887U,
	0x00D20987U,
	0x00D20A87U,
	0x00D20B87U,
	0x00D20D87U,
	0x00D20E87U,
	0x00D20F87U,
	0x00D21087U,
	0x00D21187U,
	0x00D21287U,
	0x00D21387U,
	0x00D21487U,
	0x00D21587U,
	0x00D21687U,
	0x00D21787U,
	0x00D21887U,
	0x00D21987U,
	0x00D21A87U,
	0x00D21B87U,
	0x00D21C87U,
	0x00D21D87U,
	0x00D21E87U,
	0x00D21F87U,
	0x00D23187U,
	0x00D23287U,
	0x00D23387U,
	0x00D23487U,
	0x00D23587U,
	0x00D23687U,
	0x00D23787U,
	0x00D23887U,
	0x00D23987U,
	0x00D23A87U,
	0x00D23B87U,
	0x00D23C87U,
	0x00D23D87U,
	0x00D23E87U,
	0x00D23F87U,
	0x00D24087U,
	0x00D24187U,
};


CONST(boolean, DEM_CONFIG_DATA) Dem_CfgEvtAvail[DEM_CFG_EVENT_NUM + 1U] = 
{
	FALSE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
};


CONST(uint16, DEM_CONFIG_DATA) Dem_CfgDebCntFailThrs[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] = 
{
	0U,
	0U,
};


CONST(sint16, DEM_CONFIG_DATA) Dem_CfgDebCntPassThrs[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] = 
{
	0,
	0,
};


CONST(uint16, DEM_CONFIG_DATA) Dem_CfgDebCntIncStepSize[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] = 
{
	0U,
	0U,
};


CONST(uint16, DEM_CONFIG_DATA) Dem_CfgDebCntDecStepSize[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] = 
{
	0U,
	0U,
};


CONST(boolean, DEM_CONFIG_DATA) Dem_CfgDebCntJuEn[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] = 
{
	FALSE,
	TRUE,
};


CONST(boolean, DEM_CONFIG_DATA) Dem_CfgDebCntJdEn[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] =
{
	FALSE,
	FALSE,
};


CONST(sint16, DEM_CONFIG_DATA) Dem_CfgDebCntJuVal[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] = 
{
	0,
	0,
};


CONST(sint16, DEM_CONFIG_DATA) Dem_CfgDebCntJdVal[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U] = 
{
	0,
	0,
};


CONST(boolean, DEM_CONFIG_DATA) Dem_CfgEnableCond[DEM_CFG_ENCOND_NUM + 1U] = 
{
	FALSE,
};
#define DEM_STOP_SEC_CONFIG_DATA
// #include "Dem_MemMap.h"


