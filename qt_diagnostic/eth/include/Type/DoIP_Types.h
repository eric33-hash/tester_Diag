/*
*******************************************************************************
*
*  File name: DoIP_Types.h
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
* Change: New created.
* Cause: New
*******************************************************************************
* Version: 3.1
* Author/Date : HongYQ/2020.09.13
* Change: Modify VehicleAnnounmentWaitTime and VehicleAnnounmentCount parameter
*         definition of Alive Check.
* Cause: improve readability.
*******************************************************************************
* Version: 3.2
* Author/Date : HongYQ/2020.09.16
* Change: Convert the definition of the function pointer to the style
*             of AUTOSAR code.
* Cause: In order to be in accordance with style of AUTOSAR code.
*******************************************************************************
* Version: 3.3
* Author/Date: WangC/2021.11.11
* Change: Modify header file reference.
* Cause: Optimization.
********************************************************************************
* Version: 3.14
* Author/Date: LiuHJ/2022.05.26
* Change: Add gateway function.
* Cause: New function.
********************************************************************************
* Version: 3.15
* Author/Date: LiuHJ/2022.07.07
* Change: Bugfix for CCOREDBUG-833.
* Cause: Bugfix.
********************************************************************************
* Version: 3.16
* Author/Date: LiuZY/2022.12.29
* Change: Modify the value of DOIP_ROUT_ACTIV_REQ_MAX_LEN_BYTE.
* Cause: Bugfix.
********************************************************************************
* Version: 3.17
* Author/Date: LiuZY/2023.01.09
* Change: Modify the value of DOIP_ROUT_ACTIV_ACK_MAX_LEN_BYTE.
* Cause: Bugfix.
********************************************************************************
*/
#ifndef DOIP_TYPES_H_
#define DOIP_TYPES_H_

/*
*******************************************************************************
*    Includes
*******************************************************************************
*/
//#include "ComStack_Types.h"
//#include "DoIP_Cfg.h"
//#include "SoAd.h"
//#include "TcpIp.h"
//#include "Dcm_Cbk.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Compiler/Compiler.h"
#include "Platform_Types.h"
#include "Type.h"
#include "../DoIP/DoIP_Lcfg.h"
/*
*******************************************************************************
*    Global Macros
*******************************************************************************
*/
#define DOIP_E_OK                                       (E_OK)
#define DOIP_E_NOT_OK                                   (E_NOT_OK)
#define DOIP_E_PENDING                                  (0x10U)

#define DOIP_ZERO                                       (0U)
#define DOIP_ONE                                        (1U)
#define DOIP_TWO                                        (2U)
#define DOIP_THREE                                      (3U)
#define DOIP_FOUR                                       (4U)
#define DOIP_FIVE                                       (5U)
#define DOIP_SIX                                        (6U)
#define DOIP_SEVEN                                      (7U)
#define DOIP_EIGHT                                      (8U)
#define DOIP_NINE                                       (9U)
#define DOIP_TEN                                        (10U)
#define DOIP_ELEVEN                                     (11U)
#define DOIP_TWELVE                                     (12U)
#define DOIP_THIRTEEN                                   (13U)
#define DOIP_FOURTEEN                                   (14U)
#define DOIP_FIFTEEN                                    (15U)
#define DOIP_SIXTEEN                                    (16U)
#define DOIP_TWENTYFOUR                                 (24U)

#define DOIP_PATTEN                                     (0x10U)
#define DOIP_ROUTACTV_VALIDNUM                          (0xE0U)
#define DOIP_FF                                         (0xFFU)
#define DOIP_FFFF                                       (0xFFFFU)

#define DOIP_UNUSED_PARAM                               (0U)
#define DOIP_IDENT_RES_NUM                              (1U)

#define DOIP_TPPDU                                      (0x00U)
#define DOIP_IFPDU                                      (0x01U)

#define DOIP_ACTIVATION_LINE_LOCAL_INACTIVE             (0U)
#define DOIP_ACTIVATION_LINE_LOCAL_ACTIVE               (1U)
#define DOIP_ACTIVATION_LINE_LOCAL_INACTIVE_TO_ACTIVE   (2U)
#define DOIP_ACTIVATION_LINE_LOCAL_ACTIVE_TO_INACTIVE   (3U)

#define DOIP_ACTIVATION_LINE_INACTIVE                   (0U)
#define DOIP_ACTIVATION_LINE_ACTIVE                     (1U)
#define DOIP_ACTIVATION_LINE_INACTIVE_TO_ACTIVE         (2U)
#define DOIP_ACTIVATION_LINE_ACTIVE_TO_INACTIVE         (3U)

#define DOIP_IP_ADDR_REQ_STATE_NONE                     (0x00U)
#define DOIP_IP_ADDR_REQ_STATE_REQUESTED                (0x01U)
#define DOIP_IP_ADDR_REQ_STATE_ASSIGNED                 (0x02U)
#define DOIP_IP_ADDR_REQ_STATE_RELEASE                  (0x04U)
#define DOIP_IP_ADDR_REQ_STATE_REQUESTED_INV            (0xFEU)
#define DOIP_IP_ADDR_REQ_STATE_ASSIGNED_INV             (0xFDU)
#define DOIP_IP_ADDR_REQ_STATE_RELEASE_INV              (0xFBU)

#define DOIP_IPADDR_ASSIGN_PATTERN_STATIC               (1U)
#define DOIP_IPADDR_ASSIGN_PATTERN_LINKLOCAL_DOIP       (2U)
#define DOIP_IPADDR_ASSIGN_PATTERN_DHCP                 (4U)
#define DOIP_IPADDR_ASSIGN_PATTERN_LINKLOCAL            (8U)
#define DOIP_IPADDR_ASSIGN_PATTERN_IPV6_ROUTER          (16U)

#define DOIP_IPADDR_ASSIGN_TRIGGER_DISABLE              (0U)
#define DOIP_IPADDR_ASSIGN_TRIGGER_ENABLE               (1U)

#define DOIP_POWER_MODE_NOT_READY                       (0x00U)
#define DOIP_POWER_MODE_READY                           (0x01U)
#define DOIP_POWER_MODE_NOT_SUPPORTED                   (0x02U)

/* DoIP protocol versions [SWS_DoIP_00005] [SWS_DoIP_00006]*/
#define DOIP_PROTOCOL_VERSION_2012                (uint8)(0x02U)
#define DOIP_PROTOCOL_VERSION_DEFAULT             (uint8)(0xFFU)
#define DOIP_PROTOCOL_VERSION                     (DOIP_PROTOCOL_VERSION_2012)
#define DOIP_ADDR_ANY                             ((uint16)0xFFFFU)

#define DOIP_MIN_HOST_NAME_SIZE                   (5U)
#define DOIP_VIN_PREFIX_LEN_BYTE                  (3U)
#define DOIP_VIN_LEN_BYTE                         (17U)
#define DOIP_GID_LEN_BYTE                         (6U)
#define DOIP_EID_LEN_BYTE                         (6U)
#define DOIP_ADDR_LEN_BYTE                        (2U)

/*Dummy function*/
#ifndef DOIP_DUMMY_STATEMENT
#define DOIP_DUMMY_STATEMENT(v)                   (v)=(v)
#endif

/*Det error id*/
#define DOIP_E_NO_ERROR                           (0x00U)
#define DOIP_E_UNINIT                             (0x01U)
#define DOIP_E_PARAM_POINTER                      (0x02U)
#define DOIP_E_INVALID_PDU_SDU_ID                 (0x03U)
#define DOIP_E_INVALID_PARAMETER                  (0x04U)
#define DOIP_E_INIT_FAILED                        (0x05U)
#define DOIP_E_ACTIVATION_LINE                    (0xECU)
#define DOIP_E_SOAD_CALL_FAILED                   (0xEDU)
#define DOIP_E_UNEXPECTED_ASSIGNMENT              (0xEEU)
#define DOIP_E_NOBUFS                             (0xEFU)

#define DOIP_GATEWAY                              (0x00U)
#define DOIP_NODE                                 (0x01U)

/* DoIP Initial state*/
#define DOIP_INITSTATE_UNINIT                     (0x00U)
#define DOIP_INITSTATE_INIT                       (0x01U)
#define DOIP_INITSTATE_SHUTDOWN                   (0x02U)

/* DoIP state */
#define DOIP_STATE_UNINIT                         (0x00U)
#define DOIP_STATE_INIT                           (0x01U)
#define DOIP_STATE_SHUTDOWN                       (0x02U)

#define DOIP_INSTANCE_ID_DET                      (0x00U)   /*Instance ID*/

/* DoIP ApiIds */
#define DOIP_API_ID_GET_VERSION_INFO              (0x00U)
#define DOIP_API_ID_INIT                          (0x01U)
#define DOIP_API_ID_MAIN_FUNCTION                 (0x02U)
#define DOIP_API_ID_TP_TRANSMIT                   (0x03U)
#define DOIP_API_ID_TP_CANCEL_TRANSMIT            (0x04U)
#define DOIP_API_ID_TP_CANCEL_RECEIVE             (0x05U)
#define DoIP_API_ID_ACTIVATION_LINE_SWITCH        (0x06U)
#define DOIP_API_ID_SO_CON_MODE_CHG               (0x0BU)
#define DOIP_API_ID_LOC_IP_ADDR_ASSIGN_CHG        (0x0CU)
#define DOIP_API_ID_ACTIVE_LINE_SWITCH            (0x0EU)
#define DOIP_API_ID_INACTIVE_LINE_SWITCH          (0x0FU)
#define DOIP_API_ID_IF_TX_CONFIRMATION            (0x40U)
#define DOIP_API_ID_IF_RX_INDICATION              (0x42U)
#define DOIP_API_ID_TP_COPY_TX_DATA               (0x43U)
#define DOIP_API_ID_TP_COPY_RX_DATA               (0x44U)
#define DOIP_API_ID_TP_RX_INDICATION              (0x45U)
#define DOIP_API_ID_TP_START_OF_RECEPTION         (0x46U)
#define DOIP_API_ID_TP_TX_CONFIRMATION            (0x48U)
#define DOIP_API_ID_IF_TRANSMIT                   (0x49U)
#define DOIP_API_ID_IF_CANCEL_TRANSMIT            (0x4AU)
#define DOIP_API_ID_VACT_LINE_STATE_TRANS_TO_ACT  (0xEBU)
#define DOIP_API_ID_ENABLE_PDU_SIZE_ROUTING       (0xECU)
#define DOIP_API_ID_DISABLE_PDU_SIZE_ROUTING      (0xEDU)
#define DOIP_API_ID_UDP_SINGLE_TRANSMIT           (0xEEU)
#define DOIP_API_ID_TCP_TRANSMIT                  (0xEFU)

#define DOIP_GEN_HDR_NACK_CODE_LEN_BYTE           (0x01U)
#define DOIP_GEN_HDR_TYPE_IDX                     (0x02U)
#define DOIP_GEN_HDR_LEN_BYTE                     (0x08U)

/* DoIP generic nack codes */
#define DOIP_GEN_NACK_FORMAT                      (0x00U)
#define DOIP_GEN_NACK_TYPE                        (0x01U)
#define DOIP_GEN_NACK_MAX_LEN                     (0x02U)
#define DOIP_GEN_NACK_OUT_OF_MEM                  (0x03U)
#define DOIP_GEN_NACK_INV_LEN                     (0x04U)
#define DOIP_GEN_NACK_OK                          (0xFFU)

/* DoIP diagnostic request nack codes */
#define DOIP_DIAG_MSG_RES_CODE_ACK                (uint8)(0x00U)
#define DOIP_DIAG_MSG_RES_CODE_UNKNOWN_SRC_ADDR   (uint8)(0x01U)
#define DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR   (uint8)(0x02U)
#define DOIP_DIAG_MSG_RES_CODE_UNKNOWN_TGT_ADDR   (uint8)(0x03U)
#define DOIP_DIAG_MSG_RES_CODE_MSG_TOO_LARGE      (uint8)(0x04U)
#define DOIP_DIAG_MSG_RES_CODE_OUT_OF_MEMORY      (uint8)(0x05U)
#define DOIP_DIAG_MSG_RES_CODE_TGT_UNREACHABLE    (uint8)(0x06U)
#define DOIP_DIAG_MSG_RES_CODE_UNKNOWN_NETWORK    (uint8)(0x07U)
#define DOIP_DIAG_MSG_RES_CODE_NETWORK_TRANSPROT  (uint8)(0x08U)

/* DoIP header types */
#define DOIP_HDR_TYPE_GEN_NACK                    (uint16)(0x0000U)
#define DOIP_HDR_TYPE_VEHICLE_IDENT_REQ           (uint16)(0x0001U)
#define DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_EID       (uint16)(0x0002U)
#define DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN       (uint16)(0x0003U)
#define DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT        (uint16)(0x0004U)
#define DOIP_HDR_TYPE_ROUT_ACTIV_REQ              (uint16)(0x0005U)
#define DOIP_HDR_TYPE_ROUT_ACTIV_ACK              (uint16)(0x0006U)
#define DOIP_HDR_TYPE_ALIVE_CHECK_REQ             (uint16)(0x0007U)
#define DOIP_HDR_TYPE_ALIVE_CHECK_ACK             (uint16)(0x0008U)
#define DOIP_HDR_TYPE_ENTITY_STATE_REQ            (uint16)(0x4001U)
#define DOIP_HDR_TYPE_ENTITY_STATE_ACK            (uint16)(0x4002U)
#define DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_REQ    (uint16)(0x4003U)
#define DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_ACK    (uint16)(0x4004U)
#define DOIP_HDR_TYPE_DIAG_REQ                    (uint16)(0x8001U)
#define DOIP_HDR_TYPE_DIAG_ACK                    (uint16)(0x8002U)
#define DOIP_HDR_TYPE_DIAG_NACK                   (uint16)(0x8003U)
#define DOIP_HDR_TYPE_OEM_SPECIFIC                (uint16)(0xEEEEU)
#define DOIP_HDR_TYPE_INVALID                     (uint16)(0xEFFFU)

#define DOIP_ROUT_ACTIV_STATE_NONE                (0x00U)
#define DOIP_ROUT_ACTIV_STATE_AUTH_PENDING        (0x01U)
#define DOIP_ROUT_ACTIV_STATE_CONF_PENDING        (0x02U)
#define DOIP_ROUT_ACTIV_STATE_ACTIVATED           (0x03U)
#define DOIP_ROUT_ACTIV_STATE_ACTIVATING          (0x04U)
#define DOIP_ROUT_ACTIV_STATE_TOACTIVATE          (0x05U)

#define DOIP_INV_TESTER_IDX                       (0xFFU)
#define DOIP_INV_ROUT_ACT_IDX                     (0xFFU)
#define DOIP_INV_ADDR_IDX                         (0xFFU)
#define DOIP_INV_PDU_ID                           (0xFFFFU)

#define DOIP_ROUT_ACTIV_REQ_MIN_LEN_BYTE          (0x07U)
#define DOIP_ROUT_ACTIV_REQ_MAX_LEN_BYTE          (0x0BU)
#define DOIP_ROUT_ACTIV_REQ_TYPE_LEN_BYTE         (0x01U)
#define DOIP_ROUT_ACTIV_REQ_RSVD_LEN_BYTE         (0x04U)
#define DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE          (0x04U)
#define DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE          (0x09U)
#define DOIP_ROUT_ACTIV_ACK_MAX_LEN_BYTE          (0x0DU)
#define DOIP_ROUT_ACTIV_ACK_RSVD_LEN_BYTE         (0x04U)
#define DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE          (0x04U)

/* DoIP routing activation nack codes */
#define DOIP_ROUT_ACTIV_RES_CODE_UNKNOWN_TESTER   (uint8)(0x00U)
#define DOIP_ROUT_ACTIV_RES_CODE_SOCKETS_IN_USE   (uint8)(0x01U)
#define DOIP_ROUT_ACTIV_RES_CODE_DIFFERENT_TESTER (uint8)(0x02U)
#define DOIP_ROUT_ACTIV_RES_CODE_ALREADY_ACTIV    (uint8)(0x03U)
#define DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT  (uint8)(0x04U)
#define DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED (uint8)(0x05U)
#define DOIP_ROUT_ACTIV_RES_CODE_INV_ACTIV_TYPE   (uint8)(0x06U)
#define DOIP_ROUT_ACTIV_RES_CODE_SUCCESS          (uint8)(0x10U)
#define DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REQUIRED (uint8)(0x11U)

#define DOIP_REQ_LEN_BYTE_TOTAL                    (0x00400U)
#define DOIP_MAX_REQUEST_BYTES                    (DOIP_REQ_LEN_BYTE_TOTAL)
#define DOIP_DIAG_HDR_LEN_BYTE                    (0x04U)
#define DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE            (0x04U)
#define DOIP_DIAG_MSG_ACK_LEN_BYTE                (0x05U)
#define DOIP_DIAG_MSG_NACK_LEN_BYTE               (0x05U)
#define DOIP_HWID_LEN_BYTE                        (6U)    /* MAC address length */


#define DOIP_GET_UINT8(Buffer, Offset, Variable) \
                                      ( (Variable) = (uint8)((Buffer)[(Offset)]) )

#define DOIP_GET_UINT16(Buffer, Offset, Variable) \
             ( (Variable) = (uint16)((uint16)(((uint16)((Buffer)[Offset])) << 8U) | \
                                        ((uint16)((Buffer)[(Offset) + 1U]))) )

#define DOIP_GET_UINT32(Buffer, Offset, Variable) \
    ( (Variable) = (uint32)(((uint32)((uint32)((Buffer)[Offset]) << 24U)) | \
                               ((uint32)((uint32)((Buffer)[(Offset) + 1U]) << 16U)) | \
                               ((uint32)((uint32)((Buffer)[(Offset) + 2U]) <<  8U)) | \
                               ((uint32)((Buffer)[(Offset) + 3U]))) )

#if( DOIP_VIN_GID_SYNC == STD_ON )
#define DOIP_ACK_VEHICLE_IDENT_LEN_BYTE     (33U)
#else
#define DOIP_ACK_VEHICLE_IDENT_LEN_BYTE     (32U)
#endif /* ( DOIP_VIN_GID_SYNC == STD_ON ) */

#if( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON )
#define DOIP_ACK_ENTITY_STATE_LEN_BYTE      (7U)
#else
#define DOIP_ACK_ENTITY_STATE_LEN_BYTE      (3U)
#endif /* ( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON ) */

/* For DoIP_ActLineStateMachineType. */
#define DOIP_ACTLINE_STA_INIT                           (0U)
#define DOIP_ACTLINE_INACT_TO_ACT_STA_GETSOCONID        (1U)
#define DOIP_ACTLINE_INACT_TO_ACT_STA_REQADDRASSGN      (2U)
#define DOIP_ACTLINE_INACT_TO_ACT_STA_REQADDRASSGN_WAIT (3U)
#define DOIP_ACTLINE_INACT_TO_ACT_STA_OPENSOCON         (4U)
#define DOIP_ACTLINE_INACT_TO_ACT_STA_TXVEHANN          (5U)
#define DOIP_ACTLINE_ACT_TO_INACT_STA_GETSOCONID        (6U)
#define DOIP_ACTLINE_ACT_TO_INACT_STA_RELEASEADDR       (7U)
#define DOIP_ACTLINE_ACT_TO_INACT_STA_CLOSESOCON        (9U)



#define DOIP_NODE_TYPE (DOIP_NODE)

// #define DOIP_INIT_INACTIV_WAIT                    (2000U)
// #define DOIP_GEN_INACTIV_WAIT                     (300000U)
// #define DOIP_MAX_TESTER_CONNECTIONS               (2U)


#define DOIP_DEV_ERROR_DETECT (STD_ON)
#define DOIP_DHCP_OPTION_VIN_USE_ENABLED (STD_ON)
#define DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE (STD_ON)
#define DOIP_USE_EID_AS_GID (STD_ON)
#define DOIP_USE_MAC_ADDR_FOR_IDENT (STD_ON)
#define DOIP_VIN_GID_SYNC (STD_ON)
#define DOIP_VERSIONINFOAPI (STD_ON)
#define DOIP_VIN_GID_MASTER (STD_ON)
#define DOIP_ACTIV_LINE_CALLBACK_ENABLED (STD_ON)
#define DOIP_GID_SYNC_ENABLED (STD_OFF)
#define DOIP_GID_AVAILABLE (STD_ON)
#define DOIP_TESTER_WITH_CEN_SEC_AVAILABLE (STD_OFF)



#define DOIP_NODE_TYPE (DOIP_NODE)
/*
*******************************************************************************
*    Global Types
*******************************************************************************
*/





typedef struct
{
   uint8   testAddr[DOIP_ADDR_LEN_BYTE];    /* Logical address of Diagnostic Tester */
   uint8   activType[DOIP_ROUT_ACTIV_REQ_TYPE_LEN_BYTE];    /* Routing Activation Type */
   uint8   reserved[DOIP_ROUT_ACTIV_REQ_RSVD_LEN_BYTE];    /* Reserved by DoIP specification */
   uint8   oem[DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE];    /* OEM specific extension */
} DoIP_RoutActiveReqType_st;

typedef struct
{
    uint8   ver;        /* Version */
    uint8   invVer;     /* Bit-Inverted version */
    uint8   type[2];    /* Payload type */
    uint8   lenByte[4]; /* Payload length */
} DoIP_GenHdrType_st;

typedef struct
{
    DoIP_GenHdrType_st genHdr;
    uint8        nackCode;
} DoIP_HdrNackType_st;

typedef struct
{
    DoIP_GenHdrType_st genHdr;
    uint8 diagPowerMode;
} DoIP_PowerModeAckType_st;

typedef struct
{
    DoIP_GenHdrType_st genHdr;
    uint8 nodeType;       /* DOIP_GATEWAY / DOIP_NODE */
    uint8 maxTcpSockCnt;  /* Max number of concurrent TCP sockets */
    uint8 tcpSockCnt;     /* Current number of open TCP sockets */
#if( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON )
    uint8 maxDataSize[4]; /* Maximum size of one logical request that this DoIP entity can process */
#endif /* ( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON ) */
} DoIP_EntityStateAckType_st;

typedef struct
{
   uint8   con2SoConState;      /* The DoIP connection to socket connection state. */
   uint8   con2SoConClosing;    /* The DoIP connection to socket connection close state. */
   uint8   con2SoConId;         /* The DoIP connection to socket connection ID. */
   SoAd_SoConIdType   con2IpAddrState;      /* The DoIP connection to IP address. */
} DoIP_ConnectionVarType;

typedef enum
{
    SOAD_SOCON_ONLINE = 0U,
    SOAD_SOCON_RECONNECT,
    SOAD_SOCON_OFFLINE,
} SoAd_SoConModeType;

typedef struct
{
   uint8   testAddr[DOIP_ADDR_LEN_BYTE];      /* Logical Address Tester */
   uint8   entityAddr[DOIP_ADDR_LEN_BYTE];    /* Logical address of DoIP entity */
   uint8   ackCode;                           /* Routing activation response code */
   uint8   reserved[DOIP_ROUT_ACTIV_ACK_RSVD_LEN_BYTE];    /* Reserved by ISO */
   uint8   oem[DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE];          /* OEM specific */
} DoIP_RoutActiveAckType_st;

typedef struct
{
  uint8   srcAddr[DOIP_ADDR_LEN_BYTE]; /* Logical address of Gateway */
  uint8   tgtAddr[DOIP_ADDR_LEN_BYTE]; /* Logical address of Diagnostic Tester */
} DoIP_DiagReqType_st;





typedef uint16 SoAd_DomainType;

typedef struct
{
    SoAd_DomainType domain;
} SoAd_SockAddrType;




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
/**
* \name:TcpIp_IpAddrStateType
* \brief: Specifies the state of local IP address assignment.
* \req: SWS_TCPIP_00082
*/
#if ((defined TCPIP_DEBUG) && (TCPIP_STD_ON == TCPIP_DEBUG))
enum e_TcpIp_IpAddrStateType
{
TCPIP_IPADDR_STATE_ASSIGNED = (0x01U), /* Local IP address is assigned. */
TCPIP_IPADDR_STATE_ONHOLD = (0x02U), /* Local IP address is assigned, but cannot be used as the network is not active. */
TCPIP_IPADDR_STATE_UNASSIGNED = (0x03U) /* Local IP address is unassigned. */
};
typedef enum e_TcpIp_IpAddrStateType TcpIp_IpAddrStateType;
#else /* #if ((defined TCPIP_DEBUG) && (TCPIP_STD_ON == TCPIP_DEBUG)) */
#define TCPIP_IPADDR_STATE_ASSIGNED (TcpIp_IpAddrStateType)0
#define TCPIP_IPADDR_STATE_ONHOLD (TcpIp_IpAddrStateType)1
#define TCPIP_IPADDR_STATE_UNASSIGNED (TcpIp_IpAddrStateType)2
typedef uint8 TcpIp_IpAddrStateType;
#endif /* #if ((defined TCPIP_DEBUG) && (TCPIP_STD_ON == TCPIP_DEBUG)) */

#define TCPIP_IPADDR_ASSIGNMENT_ALL             (TcpIp_IpAddrAssignmentType)0x05U
typedef uint8 TcpIp_IpAddrAssignmentType;
/*
*******************************************************************************
*    Global Functions
*******************************************************************************
*/

#endif /* DOIP_TYPES_H_ */

