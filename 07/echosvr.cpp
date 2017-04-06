#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

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
   //serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   //inet_aton("127.0.0.1",&serveraddr.sin_addr.s_addr);

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

   char buffer[1024];
   while(1)
   {
       memset(buffer,0,sizeof(buffer));
       int recvlen = read(conn,buffer,sizeof(buffer));

       printf("%s\n",buffer);
       write(conn,buffer,recvlen);
   }

   close(listenfd);

    return 0;
}