#ifndef CLIENT_H_
#define CLIENT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/tcp.h>
#include<pthread.h>
#include<unistd.h>
#include "../Type/Platform_Types.h"
#include "../DoIP/DoIP_Lcfg.h"
#include <sys/ioctl.h>
#include "netif.h"
#include <unistd.h>
#include <fcntl.h>
#include "sys/epoll.h"

//#include "tcpif.h"

#define GET_UINT32(Buffer, Offset, Variable) \
    ( (Variable) = (uint32)(((uint32)((uint32)((Buffer)[Offset]) << 24U)) | \
                               ((uint32)((uint32)((Buffer)[(Offset) + 1U]) << 16U)) | \
                               ((uint32)((uint32)((Buffer)[(Offset) + 2U]) <<  8U)) | \
                               ((uint32)((Buffer)[(Offset) + 3U]))) )
                               
extern int socketTcpInit(struct sockaddr_in *servaddr);

extern int socketUdpInit(struct sockaddr_in *servaddrUDP);

extern void setSocketcon(int sockfd);

extern int sendMsg(int* sockfd,PduInfoType* PduInfoPtr);

extern int receive(uint16* sockfd,PduInfoType* PduInfoPtr);

extern int get_mac(int* sock,char * mac, int len_limit);

extern int isConnectTcp(int* sockfd);

extern int epfd;

extern struct epoll_event ev,events[20];

extern int nfds;

#endif

