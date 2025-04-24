/*
*******************************************************************************
*
*  File name: DoIP_Cbk.h
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
* Change: Add
* Cause: New
*******************************************************************************
* Version: 3.1
* Author/Date : HongYQ/2020.09.14
* Change: Add the memory definition of AUTOSAR to the code. 
          By #define DOIP_START_SEC_CODE
             #include "DoIP_MemMap.h" 
             #define DOIP_STOP_SEC_CODE
             #include "DoIP_MemMap.h"
          form realization.
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.2
* Author/Date : HongYQ/2020.09.16
* Change: Convert the definition of the Function declaration to the style
             of AUTOSAR code.
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.3
* Author/Date : HongYQ/2020.10.13
* Change: Modify the AUTOSAR code style (formal parameters)
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.4
* Author/Date: WangC/2021.11.11
* Change: Modify header file reference.
* Cause: Optimization.
********************************************************************************
*/
#ifndef DOIP_CBK_H_
#define DOIP_CBK_H_

/*
*******************************************************************************
*    Includes
*******************************************************************************
*/
// #include "ComStack_Types.h"
// #include "DoIP_Cfg.h"
// #include "SoAd.h"
// #include "TcpIp.h"
#include "../Compiler/Compiler.h"
#include "../Type/DoIP_Types.h"
/*
*******************************************************************************
*    Global Macros
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Types
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Variables
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Constants
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Functions
*******************************************************************************
*/
extern FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpCopyTxData
(
	PduIdType id,
	P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)info,
	P2VAR(RetryInfoType, AUTOMATIC, DOIP_APPL_DATA)retry,
	P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA)availableDataPtr
);
extern FUNC(void, DOIP_CODE) DoIP_SoAdTpTxConfirmation
(
	PduIdType id, Std_ReturnType result
);
extern FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpCopyRxData
(
	VAR(PduIdType, AUTOMATIC)id, 
	P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)info,
	P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA)bufferSizePtr
);
extern FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpStartOfReception
(
	PduIdType id,
	P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)info,
	PduLengthType TpSduLength,
	P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_DATA)bufferSizePtr
);
extern FUNC(void, DOIP_CODE) DoIP_SoAdTpRxIndication
(
	PduIdType id,
	Std_ReturnType result
);
extern FUNC(void, DOIP_CODE) DoIP_SoAdIfRxIndication
(
	PduIdType RxPduId,
	PduIdType soConID,
	P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_CONST)PduInfoPtr
);
extern FUNC(void, DOIP_CODE) DoIP_SoAdIfTxConfirmation
(
	PduIdType TxPduId,
	Std_ReturnType result
);
extern FUNC(void, DOIP_CODE) DoIP_SoConModeChg
(
	SoAd_SoConIdType SoConId,
	SoAd_SoConModeType Mode
);
extern FUNC(void, DOIP_CODE) DoIP_LocalIpAddrAssignmentChg
(
	SoAd_SoConIdType SoConId,
	TcpIp_IpAddrStateType State
);

#endif /* DOIP_CBK_H_ */

