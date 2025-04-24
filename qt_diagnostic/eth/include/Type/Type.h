

#ifndef TYPE_H_
#define  TYPE_H_


#include "Platform_Types.h"


#define DOIP_NACK_APPEND_REQ (STD_ON)

typedef uint16 PduIdType;

typedef uint32 PduLengthType;

typedef uint8 Std_ReturnType;	/* SWS_Std_00005 */

typedef uint8 DoIP_ActLineStateMachineType;
typedef uint8 DoIP_RoutingActivationNumType;
typedef uint8 DoIP_FurtherActionByteType;
typedef uint8 DoIP_StateType;
typedef uint8 DoIP_ActivationLineLocalType;
typedef uint8 DoIP_ActivationLineType;
typedef uint8 DoIP_RoutActivStateType;
typedef uint8 DoIP_IpAddrReqStateType;
typedef uint8 DoIP_IpAddrAssignmentType;
typedef uint8 DoIP_PowerStateType;
typedef uint8* SduDataPtrType;
typedef uint16 SoAd_SoConIdType;



#endif