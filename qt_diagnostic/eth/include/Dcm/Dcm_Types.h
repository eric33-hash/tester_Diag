/*
********************************************************************************
*
*  File name:   Dcm_Types.h
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: Tanlx/2019.05.13
* Change: Add Autosar
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date : Liuziyang/2019.11.21
* Change: The format of code and comment.
* Cause: Modify the code according to the coding specification.
********************************************************************************
* Version: 1.2
* Author/Date : Songqw/2019.12.21
* Change: Modify the included header files according to the AUTOSAR 4.2.
* Cause: Bugfix.
********************************************************************************
* Version: 3.0
* Author/Date : Songqingwei/2020.05.15
* Change: Modify the coding specification.
* Cause: Optimize.
********************************************************************************
* Version: 3.1
* Author/Date : ZhuCY/2021.10.27
* Change: Modify header file name.
* Cause: Optimize.
********************************************************************************
* Version: 3.2
* Author/Date: SongQW/2021.12.17
* Change: Add the 0x29 service.
* Cause: Update.
********************************************************************************
* Version: 3.3
* Author/Date: ChenQJ/2022.11.24
* Change: Check Dcm_OpStatusType before define.
* Cause: Bugfix.
********************************************************************************
* Version: 3.4
* Author/Date: WuHW/2023.03.01
* Change: Delete the definition of Dcm_OpStatusType.
* Cause: Bugfix.
********************************************************************************
*/
#ifndef DCM_TYPES_H_
#define DCM_TYPES_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "../Type/Std_Types.h"
#include  "../Type/Platform_Types.h"
// #include "Rte_Dcm_Type.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#ifndef DCM_E_AUTHENTICATIONREQUIRED
#define DCM_E_AUTHENTICATIONREQUIRED                  (0x34U)
#endif

/* Certificate verification failed - Invalid Time Period */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDITP
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDITP       (0x50U)
#endif

/* Certificate verification failed - Invalid Signature */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDIS
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDIS       (0x51U)
#endif

/* Certificate verification failed - Invalid Chain of Trust */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDICOT
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDICOT       (0x52U)
#endif

/* Certificate verification failed - Invalid Type */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDIT
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDIT       (0x53U)
#endif

/* Certificate verification failed - Invalid Format */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDIF
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDIF       (0x54U)
#endif

/* Certificate verification failed - Invalid Content */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDIC
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDIC       (0x55U)
#endif

/* Certificate verification failed - Invalid Scope */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDISC
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDISC       (0x56U)
#endif

/* Certificate verification failed ¨CInvalid Certificate (revoked) */
#ifndef DCM_E_CRETIFICATEVERIFICATIONFAILEDICR
#define DCM_E_CRETIFICATEVERIFICATIONFAILEDICR       (0x57U)
#endif

/* Ownership verification failed */
#ifndef DCM_E_OWNERSHIIPVERIFICATIONFAILED
#define DCM_E_OWNERSHIIPVERIFICATIONFAILED           (0x58U)
#endif

/* Challenge calculation failed */
#ifndef DCM_E_CHALLENGECALULATIONFAILED
#define DCM_E_CHALLENGECALULATIONFAILED              (0x59U)
#endif

/* Setting Access Rights failed */
#ifndef DCM_E_SETTINGACCESSRIGHTSFAILED
#define DCM_E_SETTINGACCESSRIGHTSFAILED              (0x5AU)
#endif

/* Session key creation/derivation failed */
#ifndef DCM_E_SESSIONKEYCREATIONFAILED
#define DCM_E_SESSIONKEYCREATIONFAILED              (0x5BU)
#endif

/* Configuration data usage failed */
#ifndef DCM_E_CONFIGURATIONDATAUSAGEFAILED
#define DCM_E_CONFIGURATIONDATAUSAGEFAILED          (0x5CU)
#endif

/* DeAuthentication failed */
#ifndef DCM_E_DEAUTHENTICATIONFAILED
#define DCM_E_DEAUTHENTICATIONFAILED                (0x5DU)
#endif

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef uint8 Dcm_ProtocolType;
typedef uint8 Dcm_SesCtrlType;
typedef uint8 Dcm_DidSupportedType;
#ifndef Rte_TypeDef_Dcm_OpStatusType
typedef uint8 Dcm_OpStatusType;
#endif
typedef uint8 Dcm_SecLevelType;
typedef uint8 Dcm_NegativeResponseCodeType;
typedef struct Dcm_CONFIGTYPE_TAG
{
    uint8 NoConfig;
} Dcm_ConfigType;

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#ifndef COMM_NO_COMMUNICATION
#define COMM_NO_COMMUNICATION        (0U)
#endif

#ifndef COMM_SILENT_COMMUNICATION
#define COMM_SILENT_COMMUNICATION    (1U)
#endif

#ifndef COMM_FULL_COMMUNICATION
#define COMM_FULL_COMMUNICATION      (2U)
#endif



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

#endif  /* DCM_TYPES_H_ */
