#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include "sysutil.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main()
{
    int sockfd;
    if((sockfd=socket(PF_INET,SOCK_STREAM,0)) < 0)
    {
     ERR_EXIT("socket");
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5188);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

   int ret = connect_timeout(sockfd,&serveraddr,5);
   
   if(ret == -1 && errno == ETIMEDOUT)
   {
       printf("timeout .....\n");
       return 1;
   }
   else if(ret == -1)
   {
       ERR_EXIT("connect_timeout");
   }

    struct sockaddr_in localaddr;
    socklen_t addrlen = sizeof(localaddr);
    if((getsockname(sockfd,(struct sockaddr*)&localaddr,&addrlen)) < 0)
    {
      ERR_EXIT("getsockname");
    }

     printf("local addr %s port %d \n",inet_ntoa(localaddr.sin_addr),ntohs(localaddr.sin_port));

  
    return 0;
}