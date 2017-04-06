#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include "sysutil.h"

int main()
{
       int listenfd;
    if((listenfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
     ERR_EXIT("socket");
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5188);
    serveraddr.sin_addr.s_addr =  htonl(INADDR_ANY);

   int on = 1;
   if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) < 0)
   {
    ERR_EXIT("setsockopt");
   }

   if(bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
   {
    ERR_EXIT("bind");
   }

   if(listen(listenfd,SOMAXCONN))
   {
    ERR_EXIT("listen");
   }

    struct sockaddr_in peeraddr;
   socklen_t peerlen = sizeof(peeraddr);
   int conn;
   if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen)) < 0)
   {
     ERR_EXIT("accept");
   }

   printf("cli addr %s port %d \n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));

    return 0;
}