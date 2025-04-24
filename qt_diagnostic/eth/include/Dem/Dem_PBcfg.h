/*
********************************************************************************
*
*  File name:   Dem_PBcfg.h
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
#ifndef DEM_PBCFG_H_
#define DEM_PBCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Dem_Types.h"

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
*    Global Constants
********************************************************************************
*/
extern CONST(uint32, DEM_CONFIG_DATA) Dem_CfgUdsDtcValue[DEM_CFG_DTC_NUM + 1U];


extern CONST(boolean, DEM_CONFIG_DATA) Dem_CfgEvtAvail[DEM_CFG_EVENT_NUM + 1U];


extern CONST(uint16, DEM_CONFIG_DATA) Dem_CfgDebCntFailThrs[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(sint16, DEM_CONFIG_DATA) Dem_CfgDebCntPassThrs[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(uint16, DEM_CONFIG_DATA) Dem_CfgDebCntIncStepSize[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(uint16, DEM_CONFIG_DATA) Dem_CfgDebCntDecStepSize[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(boolean, DEM_CONFIG_DATA) Dem_CfgDebCntJuEn[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(boolean, DEM_CONFIG_DATA) Dem_CfgDebCntJdEn[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(sint16, DEM_CONFIG_DATA) Dem_CfgDebCntJuVal[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(sint16, DEM_CONFIG_DATA) Dem_CfgDebCntJdVal[DEM_CFG_DEBOUNCE_COUNTER_NUM + 1U];


extern CONST(boolean, DEM_CONFIG_DATA) Dem_CfgEnableCond[DEM_CFG_ENCOND_NUM + 1U];

/*
*********************************************************************************
*    Global Functions
*********************************************************************************
*/


#endif /* DEM_PBCFG_H_ */

