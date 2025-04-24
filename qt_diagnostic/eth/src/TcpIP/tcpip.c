#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
// int main()
// {
//     printf("Sever创建套接字\n");
//     //1.创建套接字
//     int sockfd=socket(AF_INET,SOCK_STREAM,0);//AF_INET是IPV4协议族
//     if (sockfd==-1)
//     {
//         printf("创建套接字失败\n");
//         exit(1);
//     }//创建套接字失败了
 
//     //2.设置IP端口
//     struct sockaddr_in saddr,caddr;//服务器端、客户端
//     memset(&saddr,0,sizeof(saddr));//把saddr全部置为0，即就是置空
//     saddr.sin_family=AF_INET;//成员设置地址族
//     saddr.sin_port=htons(6000);//主机转网络段整形，端口号，使用5000以上的端口,
//     saddr.sin_addr.s_addr=inet_addr("127.0.0.1");//回环地址，自己给自己发
 
//     int res=bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));//绑定套接字，专用强转成通用套接字地址 //给套接字指定，使用saddr中给的IP地址和端口
//     if(res==-1)//失败了，端口号（6000）被占用了；IP地址写错
//     {
//         printf("bind err\n");
//         close(sockfd);//关闭套接字
//         exit(1);//出错退出
//     }
 
//     //3.创建监听队列
//     res=listen(sockfd,5);//5是循环复用的，不代表只能接受五个客户端消息
//     if(res==-1)//失败了
//     {
//         close(sockfd);//如果忘记关闭，进程退出后也会自动关闭
//         exit(1);
//     }
 
//     //4.客户端申请连接

//     while(1)
//     {
//         int len=sizeof(caddr);//计算申请连接的客户端的套接字地址
//         int c=accept(sockfd,(struct sockaddr*)&caddr,&len);//可能会阻塞
//         if(c==-1)//或者c<0
//         {
//             close(sockfd);//如果忘记关闭，进程退出后也会自动关闭
//             exit(1);
//         }
         
//         printf("accept client ip:%s,port=%d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
//         while(1)
//         {
//             char buff[128]={0};
//             //5.服务器端接收连接
//             int n=recv(c,buff,127,0);//也可以用read，读取期望从c客户端的buff中读取127个字符
//             //recv也可能会阻塞，客户端不发数据
//             printf("recv:(%d):%s\n",n,buff);
     
//             if(n)
//             {
//                 send(c,"ok",2,0);//回复c客户端，2个字符的内容：“OK”，标志位为0
//             }
//             else
//             {
//                 printf("client is closed \n");
//                 close(c);
//                 break;
//             }
//             //7.关闭连接
//             //close(c);//关闭
//         }
//     }
    
//      int x = 10;
 
// }