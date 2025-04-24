#ifndef VECTORCAN_H
#define VECTORCAN_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_Windows) || defined(_MSC_VER) || defined (__GNUC__)
 #define  STRICT
 #include <windows.h>
#endif

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define UNUSED_PARAM(a) { a=a; }

#define RECEIVE_EVENT_SIZE         1        // DO NOT EDIT! Currently 1 is supported only
#define RX_QUEUE_SIZE              4096     // internal driver queue size in CAN events
#define RX_QUEUE_SIZE_FD           16384    // driver queue size for CAN-FD Rx events
#define ENABLE_CAN_FD_MODE_NO_ISO  0        // switch to activate no iso mode on a CAN FD channel
#define VCANMessageType              BYTE


#include "vxlapi.h"

typedef struct VectorCANMsg
{
    DWORD             ID;      // 11/29-bit message identifier
    VCANMessageType   MSGTYPE; // Type of the message
    BYTE              LEN;     // Data Length Code of the message (0..8)
    BYTE              DATA[64]; // Data of the message (DATA[0]..DATA[7])
} VCANMsg;

typedef struct VectorCANMsgFD
{
    DWORD             ID;       // 11/29-bit message identifier
    VCANMessageType   MSGTYPE;  // Type of the message
    BYTE              DLC;      // Data Length Code of the message (0..15)
    BYTE              DATA[64]; // Data of the message (DATA[0]..DATA[63])
} VCANMsgFD;

typedef struct {
    XLportHandle xlPortHandle;
    HANDLE       hMsgEvent;
} TStruct;

extern VCANMsg MessageBuffer;
extern pthread_mutex_t mutex;
extern char            g_AppName[XL_MAX_APPNAME+1];
extern XLportHandle    g_xlPortHandle;
extern XLdriverConfig  g_xlDrvConfig;
extern XLaccess        g_xlChannelMask;
extern XLaccess        g_xlPermissionMask;
XLstatus InitDriver(unsigned int *pxlChannelIndex,int channel);
XLstatus connectDriver(unsigned int *pxlChannelIndex,int channel,XLportHandle *hanle);
void CANoePrintConfig(void);

XLstatus CAN_Transmit(VCANMsg* MessageBuffer);

XLstatus CAN_TransmitFD(VCANMsg* MessageBuffe,int flag);

XLstatus CAN_TransmitFD_Send(VCANMsg* MessageBuffer,XLportHandle channle);

XLstatus CAN_Receive(VCANMsg* MessageBuffer);

XLstatus CAN_ReceiveFD(VCANMsg* MessageBuffer,uint32_t rx_id);

XLstatus canCreateRxThread();

XLstatus getCANoeConfig();

XLstatus cleanUpDriver();

#ifdef __cplusplus
}
#endif
#endif // VECTORCAN_H
