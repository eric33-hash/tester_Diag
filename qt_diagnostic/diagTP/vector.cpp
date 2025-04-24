#include "vectorCan.h"
#include <QDebug>
#include <stdint.h>
char            g_AppName[XL_MAX_APPNAME+1]  = "xlCANdemo";               //!< Application name which is displayed in VHWconf
XLportHandle    g_xlPortHandle              = XL_INVALID_PORTHANDLE;      //!< Global porthandle (we use only one!)
XLdriverConfig  g_xlDrvConfig;                                            //!< Contains the actual hardware configuration
XLaccess        g_xlChannelMask             = 0;                          //!< Global channelmask (includes all founded channels)
XLaccess        g_xlPermissionMask          = 0;                          //!< Global permissionmask (includes all founded channels)
static unsigned int    g_BaudRate                  = 500000;                     //!< Default baudrate
static int             g_silent                    = 0;                          //!< flag to visualize the message events (on/off)
static unsigned int    g_TimerRate                 = 0;                          //!< Global timerrate (to toggel)
static unsigned int    g_canFdSupport              = 0;                          //!< Global CAN FD support flag
static unsigned int    g_canFdModeNoIso            = ENABLE_CAN_FD_MODE_NO_ISO;  //!< Global CAN FD ISO (default) / no ISO mode flag

static XLhandle        g_hMsgEvent;
static   HANDLE           m_hThread;

static XLaccess      xlChanMaskTx = 0;
static TStruct       g_th;
DWORD     WINAPI RxThread( PVOID par );
DWORD     WINAPI RxCanFdThread( PVOID par );
uint8_t getLengthFromDLC(uint8_t DLC);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
VCANMsg MessageBuffer = {NULL};
// tread variables
XLstatus InitDriver(unsigned int *pxlChannelIndex,int channel)
{

  XLstatus          xlStatus;
  unsigned int      i;
  XLaccess          xlChannelMaskFd = 0;
  XLaccess          xlChannelMaskFdNoIso = 0;

  // ------------------------------------
  // open the driver
  // ------------------------------------
  xlStatus = xlOpenDriver ();

  // ------------------------------------
  // get/print the hardware configuration
  // ------------------------------------
  if(XL_SUCCESS == xlStatus) {
    xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
  }

  if(XL_SUCCESS == xlStatus) {
    CANoePrintConfig();

    printf("Usage: xlCANdemo <BaudRate> <ApplicationName> <Identifier>\n\n");

    // ------------------------------------
    // select the wanted channels
    // ------------------------------------
    g_xlChannelMask = 0;
    i = channel;
   // for (i=0; i < g_xlDrvConfig.channelCount; i++)
    {
      // we take all hardware we found and supports CAN
      if (g_xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN) {

        if (!xlChanMaskTx) {
          xlChanMaskTx = g_xlDrvConfig.channel[i].channelMask;
          *pxlChannelIndex  = g_xlDrvConfig.channel[i].channelIndex;
        }

        // check if we can use CAN FD - the virtual CAN driver supports CAN-FD, but we don't use it
        if ((g_xlDrvConfig.channel[i].channelCapabilities & XL_CHANNEL_FLAG_CANFD_ISO_SUPPORT)
           && (g_xlDrvConfig.channel[i].hwType != XL_HWTYPE_VIRTUAL)) {
          xlChannelMaskFd |= g_xlDrvConfig.channel[i].channelMask;

          // check CAN FD NO ISO support
          if (g_xlDrvConfig.channel[i].channelCapabilities & XL_CHANNEL_FLAG_CANFD_BOSCH_SUPPORT) {
            xlChannelMaskFdNoIso |= g_xlDrvConfig.channel[i].channelMask;
          }
        }
        else {
          g_xlChannelMask |= g_xlDrvConfig.channel[i].channelMask;
        }

      }
    }

    // if we found a CAN FD supported channel - we use it.
    if (xlChannelMaskFd && !g_canFdModeNoIso) {
      g_xlChannelMask = xlChannelMaskFd;
      printf("- Use CAN-FD for   : CM=0x%I64x\n", g_xlChannelMask);
      g_canFdSupport = 1;
    }

    if (xlChannelMaskFdNoIso && g_canFdModeNoIso) {
      g_xlChannelMask = xlChannelMaskFdNoIso;
      printf("- Use CAN-FD NO ISO for   : CM=0x%I64x\n", g_xlChannelMask);
      g_canFdSupport = 1;
    }

    if (!g_xlChannelMask) {
      printf("ERROR: no available channels found! (e.g. no CANcabs...)\n\n");
      xlStatus = XL_ERROR;
    }
  }

  g_xlPermissionMask = g_xlChannelMask;
  // ------------------------------------
  // open ONE port including all channels
  // ------------------------------------
  if(XL_SUCCESS == xlStatus) {

    // check if we can use CAN FD
    if (g_canFdSupport) {
      xlStatus = xlOpenPort(&g_xlPortHandle, g_AppName, g_xlChannelMask, &g_xlPermissionMask, RX_QUEUE_SIZE_FD, XL_INTERFACE_VERSION_V4, XL_BUS_TYPE_CAN);
    }
    // if not, we make 'normal' CAN
    else {
      xlStatus = xlOpenPort(&g_xlPortHandle, g_AppName, g_xlChannelMask, &g_xlPermissionMask, RX_QUEUE_SIZE, XL_INTERFACE_VERSION, XL_BUS_TYPE_CAN);

    }
     printf("- OpenPort         : CM=0x%I64x, PH=0x%02X, PM=0x%I64x, %s\n",
              g_xlChannelMask, g_xlPortHandle, g_xlPermissionMask, xlGetErrorString(xlStatus));

  }

  if ( (XL_SUCCESS == xlStatus) && (XL_INVALID_PORTHANDLE != g_xlPortHandle) ) {

    // ------------------------------------
    // if we have permission we set the
    // bus parameters (baudrate)
    // ------------------------------------
    if (g_xlChannelMask == g_xlPermissionMask) {

      if(g_canFdSupport) {
        XLcanFdConf fdParams;

        memset(&fdParams, 0, sizeof(fdParams));

        // arbitration bitrate
        fdParams.arbitrationBitRate = 500000;
        fdParams.tseg1Abr           = 6;
        fdParams.tseg2Abr           = 3;
        fdParams.sjwAbr             = 2;

        // data bitrate
        fdParams.dataBitRate = fdParams.arbitrationBitRate*4;
        fdParams.tseg1Dbr    = 6;
        fdParams.tseg2Dbr    = 3;
        fdParams.sjwDbr      = 2;

        if (g_canFdModeNoIso) {
          fdParams.options = CANFD_CONFOPT_NO_ISO;
        }

        xlStatus = xlCanFdSetConfiguration(g_xlPortHandle, g_xlChannelMask, &fdParams);
        printf("- SetFdConfig.     : ABaudr.=%u, DBaudr.=%u, %s\n", fdParams.arbitrationBitRate, fdParams.dataBitRate, xlGetErrorString(xlStatus));

      }
      else {
        xlStatus = xlCanSetChannelBitrate(g_xlPortHandle, g_xlChannelMask, g_BaudRate);
        printf("- SetChannelBitrate: baudr.=%u, %s\n",g_BaudRate, xlGetErrorString(xlStatus));
      }
    }
    else {
      printf("-                  : we have NO init access!\n");
    }
  }
  else {

    xlClosePort(g_xlPortHandle);
    g_xlPortHandle = XL_INVALID_PORTHANDLE;
    xlStatus = XL_ERROR;
  }

  xlStatus = xlActivateChannel(g_xlPortHandle, g_xlChannelMask, XL_BUS_TYPE_CAN, XL_ACTIVATE_RESET_CLOCK);
      printf("- ActivateChannel  : CM=0x%I64x, %s\n", g_xlChannelMask, xlGetErrorString(xlStatus));
  return xlStatus;

}

XLstatus connectDriver(unsigned int *pxlChannelIndex,int channel,XLportHandle *handle)
{
    XLstatus          xlStatus;
    unsigned int      i;
    XLaccess          xlChannelMaskFd = 0;
    XLaccess          xlChannelMaskFdNoIso = 0;
    XLaccess          xlChannelMask             = 0;
    XLaccess          xlPermissionMask          = 0;
    // ------------------------------------
    // get/print the hardware configuration
    // ------------------------------------
    if(XL_SUCCESS == xlStatus) {
      xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }

    if(XL_SUCCESS == xlStatus) {

      xlChannelMask = channel+1;
      i = channel+1;
     // for (i=0; i < g_xlDrvConfig.channelCount; i++)
      {
        // we take all hardware we found and supports CAN
        if (g_xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN) {

          if (!xlChanMaskTx) {
            xlChanMaskTx = g_xlDrvConfig.channel[i].channelMask;
            *pxlChannelIndex  = g_xlDrvConfig.channel[i].channelIndex;
          }

          // check if we can use CAN FD - the virtual CAN driver supports CAN-FD, but we don't use it
          if ((g_xlDrvConfig.channel[i].channelCapabilities & XL_CHANNEL_FLAG_CANFD_ISO_SUPPORT)
             && (g_xlDrvConfig.channel[i].hwType != XL_HWTYPE_VIRTUAL)) {
            xlChannelMaskFd |= g_xlDrvConfig.channel[i].channelMask;

            // check CAN FD NO ISO support
            if (g_xlDrvConfig.channel[i].channelCapabilities & XL_CHANNEL_FLAG_CANFD_BOSCH_SUPPORT) {
              xlChannelMaskFdNoIso |= g_xlDrvConfig.channel[i].channelMask;
            }
          }
          else {
            xlChannelMask |= g_xlDrvConfig.channel[i].channelMask;
          }

        }
      }

      // if we found a CAN FD supported channel - we use it.
      if (xlChannelMaskFd && !g_canFdModeNoIso) {
        xlChannelMask = xlChannelMaskFd;
        printf("- Use CAN-FD for   : CM=0x%I64x\n", xlChannelMask);
        g_canFdSupport = 1;
      }

      if (xlChannelMaskFdNoIso && g_canFdModeNoIso) {
        xlChannelMask = xlChannelMaskFdNoIso;
        printf("- Use CAN-FD NO ISO for   : CM=0x%I64x\n", xlChannelMask);
        g_canFdSupport = 1;
      }

      if (!xlChannelMask) {
        printf("ERROR: no available channels found! (e.g. no CANcabs...)\n\n");
        xlStatus = XL_ERROR;
      }
    }

    xlPermissionMask = xlChannelMask;
    // ------------------------------------
    // open ONE port including all channels
    // ------------------------------------
    if(XL_SUCCESS == xlStatus) {

      // check if we can use CAN FD
      if (g_canFdSupport) {
        xlStatus = xlOpenPort(handle, g_AppName, xlChannelMask, &xlPermissionMask, RX_QUEUE_SIZE_FD, XL_INTERFACE_VERSION_V4, XL_BUS_TYPE_CAN);
      }
      // if not, we make 'normal' CAN
      else {
        xlStatus = xlOpenPort(handle, g_AppName, xlChannelMask, &xlPermissionMask, RX_QUEUE_SIZE, XL_INTERFACE_VERSION, XL_BUS_TYPE_CAN);

      }
       printf("- OpenPort         : CM=0x%I64x, PH=0x%02X, PM=0x%I64x, %s\n",
                xlChannelMask, *handle, xlPermissionMask, xlGetErrorString(xlStatus));

    }

    if ( (XL_SUCCESS == xlStatus) && (XL_INVALID_PORTHANDLE != *handle) ) {

      // ------------------------------------
      // if we have permission we set the
      // bus parameters (baudrate)
      // ------------------------------------
      if (xlChannelMask == xlPermissionMask) {

        if(g_canFdSupport) {
          XLcanFdConf fdParams;

          memset(&fdParams, 0, sizeof(fdParams));

          // arbitration bitrate
          fdParams.arbitrationBitRate = 500000;
          fdParams.tseg1Abr           = 3;
          fdParams.tseg2Abr           = 1;
          fdParams.sjwAbr             = 1;

          // data bitrate
          fdParams.dataBitRate = fdParams.arbitrationBitRate*4;
          fdParams.tseg1Dbr    = 3;
          fdParams.tseg2Dbr    = 1;
          fdParams.sjwDbr      = 1;

          if (g_canFdModeNoIso) {
            fdParams.options = CANFD_CONFOPT_NO_ISO;
          }

          xlStatus = xlCanFdSetConfiguration(*handle, xlChannelMask, &fdParams);
          printf("- SetFdConfig.     : ABaudr.=%u, DBaudr.=%u, %s\n", fdParams.arbitrationBitRate, fdParams.dataBitRate, xlGetErrorString(xlStatus));

        }
        else {
          xlStatus = xlCanSetChannelBitrate(*handle, xlChannelMask, g_BaudRate);
          printf("- SetChannelBitrate: baudr.=%u, %s\n",g_BaudRate, xlGetErrorString(xlStatus));
        }
      }
      else {
        printf("-                  : we have NO init access!\n");
      }
    }
    else {

      xlClosePort(*handle);
      *handle = XL_INVALID_PORTHANDLE;
      xlStatus = XL_ERROR;
    }
    xlStatus = xlActivateChannel(*handle, xlChannelMask, XL_BUS_TYPE_CAN, XL_ACTIVATE_RESET_CLOCK);
        printf("- ActivateChannel  : CM=0x%I64x, %s\n", xlChannelMask, xlGetErrorString(xlStatus));
    return xlStatus;

}
void CANoePrintConfig(void) {

  unsigned int i;
  char         str[100];

  printf("----------------------------------------------------------\n");
  printf("- %02d channels       Hardware Configuration               -\n", g_xlDrvConfig.channelCount);
  printf("----------------------------------------------------------\n");

  for (i=0; i < g_xlDrvConfig.channelCount; i++) {

    printf("- Ch:%02d, CM:0x%03I64x,",
      g_xlDrvConfig.channel[i].channelIndex, g_xlDrvConfig.channel[i].channelMask);

    strncpy_s(str, 100, g_xlDrvConfig.channel[i].name, 23);
    printf(" %23s,", str);

    memset(str, 0, sizeof(str));

    if (g_xlDrvConfig.channel[i].transceiverType != XL_TRANSCEIVER_TYPE_NONE) {
      strncpy_s( str, 100, g_xlDrvConfig.channel[i].transceiverName, 13);
      printf("%13s -\n", str);
    }
    else printf("    no Cab!   -\n");


  }

  printf("----------------------------------------------------------\n\n");

}

uint8_t getLengthFromDLC(uint8_t DLC)
{
    switch (DLC) {
    case 9:return 12;
    case 10:return 16;
    case 11:return 20;
    case 12:return 24;
    case 13:return 32;
    case 14:return 48;
    case 15:return 64;
    default:return DLC;
    }
}
XLstatus CAN_Transmit(VCANMsg* MessageBuffer)
{
    XLstatus             xlStatus;
    unsigned int         messageCount = 1;
    static XLevent       xlEvent;
    char          tmp[100];
    memset(&xlEvent, 0, sizeof(xlEvent));

    xlEvent.tag                 = XL_TRANSMIT_MSG;
    xlEvent.tagData.msg.id      = MessageBuffer->ID;
    xlEvent.tagData.msg.dlc     = MessageBuffer->LEN;
    xlEvent.tagData.msg.flags   = 0;
    memcpy(&xlEvent.tagData.msg.data[0],&MessageBuffer->DATA[0],MessageBuffer->LEN);

    xlStatus = xlCanTransmit(g_xlPortHandle, xlChanMaskTx, &messageCount, &xlEvent);
//    sprintf_s(tmp, sizeof(tmp), "%s", xlGetEventString(&xlEvent));
//    qDebug() << tmp;
//    xlFlushReceiveQueue(g_xlPortHandle);
    return xlStatus;
}
XLstatus CAN_Transmit_Send(VCANMsg* MessageBuffer,XLportHandle channle)
{
    XLstatus             xlStatus;
    unsigned int         messageCount = 1;
    static XLevent       xlEvent;
    char          tmp[100];
    memset(&xlEvent, 0, sizeof(xlEvent));

    xlEvent.tag                 = XL_TRANSMIT_MSG;
    xlEvent.tagData.msg.id      = MessageBuffer->ID;
    xlEvent.tagData.msg.dlc     = MessageBuffer->LEN;
    xlEvent.tagData.msg.flags   = 0;
    memcpy(&xlEvent.tagData.msg.data[0],&MessageBuffer->DATA[0],MessageBuffer->LEN);

    xlStatus = xlCanTransmit(g_xlPortHandle, xlChanMaskTx, &messageCount, &xlEvent);
//    sprintf_s(tmp, sizeof(tmp), "%s", xlGetEventString(&xlEvent));
//    qDebug() << tmp;
//    xlFlushReceiveQueue(g_xlPortHandle);
    return xlStatus;
}

XLstatus CAN_TransmitFD(VCANMsg* MessageBuffer,int flag = 0)
{
    XLstatus             xlStatus;
    unsigned int         messageCount = 1;
    unsigned int         cntSend;
    XLcanTxEvent  canTxEvt;
    XLcanRxEvent         xlEvent;
    char          tmp[100];
    memset(&canTxEvt, 0, sizeof(canTxEvt));
    canTxEvt.tag = XL_CAN_EV_TAG_TX_MSG;

    canTxEvt.tagData.canMsg.canId     = MessageBuffer->ID;
    if(flag == 0)
    {
//        canTxEvt.tagData.canMsg.msgFlags  =  XL_CAN_TXMSG_FLAG_EDL | XL_CAN_TXMSG_FLAG_BRS;
        canTxEvt.tagData.canMsg.msgFlags  =  XL_CAN_TXMSG_FLAG_EDL;
    }

    canTxEvt.tagData.canMsg.dlc       = MessageBuffer->LEN;
    memcpy(&canTxEvt.tagData.canMsg.data[0],&MessageBuffer->DATA[0],getLengthFromDLC(canTxEvt.tagData.canMsg.dlc));
    xlStatus = xlCanTransmitEx(g_xlPortHandle, xlChanMaskTx, messageCount, &cntSend, &canTxEvt);
    return xlStatus;
}

XLstatus CAN_TransmitFD_Send(VCANMsg* MessageBuffer,XLportHandle channle)
{
    XLstatus             xlStatus;
    unsigned int         messageCount = 1;
    unsigned int         cntSend;
    XLcanTxEvent  canTxEvt;
    char          tmp[100];
    memset(&canTxEvt, 0, sizeof(canTxEvt));
    canTxEvt.tag = XL_CAN_EV_TAG_TX_MSG;

    canTxEvt.tagData.canMsg.canId     = MessageBuffer->ID;
    //canTxEvt.tagData.canMsg.msgFlags  =  XL_CAN_TXMSG_FLAG_EDL;
    canTxEvt.tagData.canMsg.dlc       = MessageBuffer->LEN;
    memcpy(&canTxEvt.tagData.canMsg.data[0],&MessageBuffer->DATA[0],getLengthFromDLC(canTxEvt.tagData.canMsg.dlc));
    xlStatus = xlCanTransmitEx(channle, channle + 1, messageCount, &cntSend, &canTxEvt);
    return xlStatus;
}

XLstatus canCreateRxThread()
{

  XLstatus      xlStatus = XL_ERROR;
  DWORD         ThreadId=0;
  char          tmp[100];

  if (g_xlPortHandle!= XL_INVALID_PORTHANDLE) {

    // Send a event for each Msg!!!
    xlStatus = xlSetNotification (g_xlPortHandle, &g_hMsgEvent, 1);
    sprintf_s(tmp, sizeof(tmp), "SetNotification '%p', xlStatus: %d", g_hMsgEvent, xlStatus);
    qDebug() << tmp;

    // for the RxThread
    g_th.xlPortHandle = g_xlPortHandle;
    g_th.hMsgEvent    = g_hMsgEvent;

    if (g_canFdSupport) {
      m_hThread = CreateThread(0, 0x1000, RxCanFdThread, (LPVOID)  &g_th, 0, &ThreadId);
    }
    else {
      m_hThread = CreateThread(0, 0x1000, RxThread, (LPVOID)&g_th, 0, &ThreadId);
    }

//    m_hThread = CreateThread(0, 0x1000, RxThread, (LPVOID) &g_th, 0, &ThreadId);
    sprintf_s(tmp, sizeof(tmp), "CreateThread %p", m_hThread);
    qDebug() << tmp;

  }
  return xlStatus;
}

DWORD WINAPI RxCanFdThread(LPVOID par)
{
  XLstatus        xlStatus = XL_SUCCESS;
  DWORD           rc;
  XLcanRxEvent    xlCanRxEvt;

  UNUSED_PARAM(par);

  TStruct *pTh;

  pTh = (TStruct*) par;


  while (true) {
    rc = WaitForSingleObject(pTh->hMsgEvent, 10);
 //   if(rc != WAIT_OBJECT_0) continue;

    do {
      xlStatus = xlCanReceive(pTh->xlPortHandle, &xlCanRxEvt);
      if(xlStatus==XL_ERR_QUEUE_IS_EMPTY ) {
        break;
      }
      else
      {
          qDebug("%s", xlCanGetEventString(&xlCanRxEvt));
      }
    } while(XL_SUCCESS == xlStatus);
  }

  return(NO_ERROR);
}

DWORD WINAPI RxThread(LPVOID par)
{

  XLstatus        xlStatus;

  unsigned int    msgsrx = 1;
  XLevent         xlEvent;
  char            tmp[110];
  QString         str;


  TStruct *pTh;

  pTh = (TStruct*) par;

  sprintf_s(tmp, sizeof(tmp), "thread: SetNotification '%p'", pTh->hMsgEvent);
  qDebug() << tmp;

  while (true) {

    WaitForSingleObject(pTh->hMsgEvent,10);

    xlStatus = XL_SUCCESS;

    while (!xlStatus) {

    msgsrx = 1;
    xlStatus = xlReceive(pTh->xlPortHandle, &msgsrx, &xlEvent);
    while (xlEvent.tagData.msg.flags != 0) {
        msgsrx = 1;
        xlStatus = xlReceive(pTh->xlPortHandle, &msgsrx, &xlEvent);
    }
    if ( xlStatus!=XL_ERR_QUEUE_IS_EMPTY ) {
        pthread_mutex_lock(&mutex);
        MessageBuffer.ID = xlEvent.tagData.msg.id;
        MessageBuffer.LEN = xlEvent.tagData.msg.dlc;
        memcpy(&MessageBuffer.DATA[0],&xlEvent.tagData.msg.data[0],MessageBuffer.LEN);
        sprintf_s(tmp, sizeof(tmp), "%s", xlGetEventString(&xlEvent));
        qDebug() << tmp;
        pthread_mutex_unlock(&mutex);

      }

    }

  }
  return NO_ERROR;
}

XLstatus CAN_Receive(VCANMsg* MessageBuffer)
{
    XLstatus             xlStatus;
    XLevent              xlEvent;
    unsigned int         msgsrx = 1;

    xlStatus = xlReceive(g_xlPortHandle, &msgsrx, &xlEvent);
    while (xlEvent.tagData.msg.flags != 0) {
        msgsrx = 1;
        xlStatus = xlReceive(g_xlPortHandle, &msgsrx, &xlEvent);
    }
    if ( xlStatus != XL_ERR_QUEUE_IS_EMPTY)
    {
        MessageBuffer->ID = xlEvent.tagData.msg.id;
        MessageBuffer->LEN = xlEvent.tagData.msg.dlc;
        memcpy(&MessageBuffer->DATA[0],&xlEvent.tagData.msg.data[0],MessageBuffer->LEN);
    }
    return xlStatus;

}

XLstatus CAN_ReceiveFD(VCANMsg* MessageBuffer,uint32_t rx_id)
{
    XLstatus             xlStatus;
    XLcanRxEvent         xlEvent;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned int initTime = tv.tv_sec*1000 + tv.tv_usec/1000;

    xlStatus = xlCanReceive(g_xlPortHandle, &xlEvent);
    unsigned int endTime = initTime;
//    while((xlEvent.tag != XL_CAN_EV_TAG_RX_OK) )
//   // while((xlEvent.tag != XL_CAN_EV_TAG_RX_OK) && (endTime - initTime <= 1600))
//    {
//        xlStatus = xlCanReceive(g_xlPortHandle, &xlEvent);
//        gettimeofday(&tv,NULL);
//        endTime = tv.tv_sec*1000 + tv.tv_usec/1000;
//    }
//    if(xlEvent.tag != XL_CAN_EV_TAG_RX_OK)
//    {
//        xlStatus = xlCanReceive(g_xlPortHandle, &xlEvent);
////        break;
////        if(xlEvent.tag != XL_CAN_EV_TAG_RX_OK)
////            break;
//    }

    while(endTime - initTime <= 5000)
    {
        xlStatus = xlCanReceive(g_xlPortHandle, &xlEvent);
        if((xlEvent.tag == XL_CAN_EV_TAG_RX_OK) && (xlStatus != XL_ERR_QUEUE_IS_EMPTY))
        {
            if(xlEvent.tagData.canRxOkMsg.canId == rx_id)
            {
                MessageBuffer->ID = xlEvent.tagData.canRxOkMsg.canId;
                MessageBuffer->LEN = xlEvent.tagData.canRxOkMsg.dlc;
                memcpy(&MessageBuffer->DATA[0],&xlEvent.tagData.canRxOkMsg.data[0],MessageBuffer->LEN);
                return xlStatus;
            }
        }
        gettimeofday(&tv,NULL);
        endTime = tv.tv_sec*1000 + tv.tv_usec/1000;
    }
    return XL_ERR_QUEUE_IS_EMPTY;
//    if ( xlStatus != XL_ERR_QUEUE_IS_EMPTY)
//    {
//        MessageBuffer->ID = xlEvent.tagData.canRxOkMsg.canId;
//        MessageBuffer->LEN = xlEvent.tagData.canRxOkMsg.dlc;
//        memcpy(&MessageBuffer->DATA[0],&xlEvent.tagData.canRxOkMsg.data[0],MessageBuffer->LEN);
//    }

//    return xlStatus;
}


XLstatus cleanUpDriver()
{
     XLstatus          xlStatus;
     xlStatus = xlDeactivateChannel(g_xlPortHandle, g_xlChannelMask);
     if (g_xlPortHandle != XL_INVALID_PORTHANDLE) {
       xlStatus = xlClosePort(g_xlPortHandle);
       printf("- ClosePort        : PH(0x%x), %s\n", g_xlPortHandle, xlGetErrorString(xlStatus));
     }

     g_xlPortHandle = XL_INVALID_PORTHANDLE;
     xlCloseDriver();
     return XL_SUCCESS;
}
