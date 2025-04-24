/* File Name: client.c */
 
#include "../../include/TcpIP/client.h"
#include <signal.h>

#define MAXLINE 0xFFFF
#define SOCKET_ERROR (-1)
#define TCP_ESTABLISHED 1
#define TCP_DISCONNECT 0

int socketTcpInit(struct sockaddr_in *servaddr)
{
   // printf("execute function:socketinit\n");
    int sockfd;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
      return 0;
    }
    //printf("socket = %d\n",sockfd);
    
#if( DOIP_SUPPORT_TCP_CLIENT_CONNECTION == STD_OFF )
    boolean bReuseaddr = TRUE;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(boolean));
    
    fcntl(sockfd,F_SETFL,O_NONBLOCK);
    struct sockaddr_in saddr;//服务器端、客户端
    memset(&saddr,0,sizeof(saddr));//把saddr全部置为0，即就是置空
    saddr.sin_family=AF_INET;//成员设置地址族
    saddr.sin_port=htons(13400);//主机转网络段整形，端口号，使用5000以上的端口,
    saddr.sin_addr.s_addr=inet_addr(EntitysetIP);//回环地址，自己给自己发
    
    int res=bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));//绑定套接字，专用强转成通用套接字地址 //给套接字指定，使用saddr中给的IP地址和端口
    if(res==-1)//失败了，端口号（6000）被占用了；IP地址写错
    {
        printf("bind err\n");
        printf("create bind error: %s(errno: %d)\n", strerror(errno),errno);
        close(sockfd);//关闭套接字
        return 0;
       // exit(1);//出错退出
    }
 
    //3.创建监听队列
    res=listen(sockfd,5);//5是循环复用的，不代表只能接受五个客户端消息
    if(res==-1)//失败了
    {
        close(sockfd);//如果忘记关闭，进程退出后也会自动关闭
        return 0;
        //exit(1);
    }
#endif
   // printf("execute function:socketinit success\n");
    return sockfd;
}

int socketUdpInit(struct sockaddr_in *servaddrUDP)
{
    int sockFD = socket(AF_INET,SOCK_DGRAM,0);
    if(sockFD == -1)
    {
      printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
      return 0;
    }
    int broadCast = 1;
    int ret = setsockopt(sockFD,SOL_SOCKET,SO_BROADCAST,&broadCast,sizeof(broadCast));
    if(ret < 0)
    {
        printf("create socket broadCast error: %s(errno: %d)\n", strerror(errno),errno);
        return 0; 
    }
    memset(servaddrUDP, 0, sizeof(*servaddrUDP));
    servaddrUDP->sin_family = AF_INET;
    servaddrUDP->sin_port = htons(13400);
    //servaddrUDP->sin_addr.s_addr = inet_addr("10.10.193.255");
    if(inet_pton(AF_INET,DoIPTestersetIP,&servaddrUDP->sin_addr) <= 0)
    {
       printf("inet_pton error for %s\n",DoIPTestersetIP);
       return 0;        
    }
    struct sockaddr_in *localaddrUDP;
    localaddrUDP = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    memset(localaddrUDP, 0, sizeof(*localaddrUDP));
    localaddrUDP->sin_family = AF_INET;
    localaddrUDP->sin_port = htons(13400);
    if(inet_pton(AF_INET,EntitysetIP,&localaddrUDP->sin_addr) <= 0)
    {
       printf("inet_pton error for %s\n",EntitysetIP);
       return 0;        
    }
    if(bind(sockFD,localaddrUDP,sizeof(*localaddrUDP)) < 0)
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;  
    }
    printf("creat UDPSocket success:%d\n",sockFD);
    return sockFD;
}

void setSocketcon(int sockfd)
{
  int   keepAlive = 1;       //设定KeepAlive
  int   keepIdle = 5;        //首次探测开始前的tcp无数据收发空闲时间
  int   keepInterval = 3;  //每次探测的间隔时间
  int   keepCount = 2;     //探测次数        
  boolean bReusedAdr = TRUE;
  boolean bDontLinger = FALSE;

//   if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(const char*)&bReusedAdr,sizeof(boolean) == SOCKET_ERROR))
//   {
//     printf("Call setsockopt error, errno is %d/n", errno);
//   }

  if(setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,(void*)&keepAlive,sizeof(keepAlive)) == SOCKET_ERROR)

    printf("Call setsockopt error, errno is %d/n", errno);


  if(setsockopt(sockfd,IPPROTO_TCP,TCP_KEEPIDLE,(void   *)&keepIdle,sizeof(keepIdle)) == SOCKET_ERROR)

    printf("Call setsockopt error, errno is %d/n", errno);

  if(setsockopt(sockfd,IPPROTO_TCP,TCP_KEEPINTVL,(void   *)&keepInterval,sizeof(keepInterval)) == SOCKET_ERROR)

    printf("Call setsockopt error, errno is %d/n", errno);
               
  if(setsockopt(sockfd,IPPROTO_TCP,TCP_KEEPCNT,(void   *)&keepCount,sizeof(keepCount)) == SOCKET_ERROR)

    printf("Call setsockopt error, errno is %d/n", errno);
}

int isConnectTcp(int* sockfd)
{
    struct tcp_info_M info;
    int len = sizeof(info);
    getsockopt(sockfd,IPPROTO_TCP,TCP_INFO,&info,(socklen_t*)(&len));
    if ((info.tcpi_state == TCP_ESTABLISHED))
    {
        return TCP_ESTABLISHED;
    }
    else
    {
        return TCP_DISCONNECT;
    }
    
}
int sendMsg(int* sockfd,PduInfoType* PduInfoPtr)
{  
    signal(SIGPIPE,SIG_IGN);
    if(send(sockfd, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength, 0) < 0)
    {
       printf("send msg error pthread: %s(errno: %d)\n", strerror(errno), errno);
       if(errno == 32 || errno == 104)
       {
           return 2;
       }
       return 1;
    }

#pragma region printDebug
            time_t now;
    	    struct tm *local_time;
    	    now = time(NULL);
   		    local_time = localtime(&now);
    	    printf("[%d-%02d-%02d %02d:%02d:%02d]Request:", 
                local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
                local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
            if((PduInfoPtr->SduDataPtr[2] << 8 | PduInfoPtr->SduDataPtr[3]) == 0x0005)
            {
                printf("RoutingActivite\n");
            }
            else
            {
                for(int i = 12;i < PduInfoPtr->SduLength;i++)
		        {
		        	printf("%02x ",PduInfoPtr->SduDataPtr[i]);
		        }
		        printf("\n");
            }

#pragma endregion

    return 0;
}

int receive(uint16 *sockfd,PduInfoType* PduInfoPtr)
{
    long  rec_len = 0;
    char buf[MAXLINE];
   //char *buf = NULL;
   //buf = (char*)malloc(0xFFFFFF);
    long handleLen = 0;
    long lastRecLen = 0;
    long data = 0;
    char handleData[4] = {0x00};
    //handleData = (char*)malloc(4);
    long waitDataLen = 0;
    boolean EnterFlag = TRUE;
    
    //do
 //   {
       lastRecLen = rec_len;
       rec_len = recv(*sockfd, buf, MAXLINE,0);
    //   printf("Received length = %d\n",rec_len);
    //   printf("Error: %s\n",strerr1or(errno));
    //    if(rec_len == 0 && strerror(errno) == EWOULDBLOCK) 
    //    {
    //      //close(sockfd); //close socket between Sever and Client Communicate
    //      return 0;
    //    }
       
       if(rec_len > 0)
       {
        
        memcpy(PduInfoPtr->SduDataPtr,buf,rec_len);
            PduInfoPtr->SduLength = rec_len;
                return 1;
        // data += rec_len;
        // if(EnterFlag)
        // {
        //     if(rec_len < 100)
        //     {
        //         memcpy(PduInfoPtr->SduDataPtr,buf,rec_len);
        //         PduInfoPtr->SduLength = rec_len;
        //         return 1;
        //     }
        //     memcpy(handleData,&buf[4],4);
        //     GET_UINT32(handleData,0,handleLen);
        //     handleLen += 8;
        // }
        //    buf[rec_len]  = '\0';
        //    waitDataLen = (handleLen) - rec_len;
        //    if(EnterFlag)
        //    {
        //       PduInfoPtr->SduLength = handleLen;
        //    }
        //    memcpy(PduInfoPtr->SduDataPtr + lastRecLen,buf,rec_len);
        }
        else 
        {
            return 0;
        }
       EnterFlag = FALSE;
  //  } while (data != handleLen);
    data = 0;
    fflush(stdout);
    return 1;
}

int get_mac(int* sock,char * mac, int len_limit)    //返回值是实际写入char * mac的字符个数（不包括'\0'）
{
    struct ifreq ifreq;

    strcpy (ifreq.ifr_name, "enp111s0");    //Currently, only get eth0

    if (ioctl (*sock, SIOCGIFHWADDR, &ifreq) < 0)
    {
        perror ("ioctl");
        return -1;
    }
    
    return snprintf (mac, len_limit, "%X:%X:%X:%X:%X:%X", (unsigned char) ifreq.ifr_hwaddr.sa_data[0], (unsigned char) ifreq.ifr_hwaddr.sa_data[1], (unsigned char) ifreq.ifr_hwaddr.sa_data[2], (unsigned char) ifreq.ifr_hwaddr.sa_data[3], (unsigned char) ifreq.ifr_hwaddr.sa_data[4], (unsigned char) ifreq.ifr_hwaddr.sa_data[5]);
}

