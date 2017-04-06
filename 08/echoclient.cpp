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
    int sockfd;
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
     ERR_EXIT("socket");
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5188);
    //serveraddr.sin_addr.s_addr =  htonl(INADDR_ANY);
   serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   //inet_aton("127.0.0.1",&serveraddr.sin_addr.s_addr);


   if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
   {
     ERR_EXIT("connect");
   }

   char sendbuffer[1024] = {0};
   char recvbuffer[1024] = {0};
   while(fgets(sendbuffer,sizeof(sendbuffer),stdin) != NULL)
   {
       memset(recvbuffer,0,sizeof(recvbuffer));
       write(sockfd,sendbuffer,strlen(sendbuffer));

       read(sockfd,recvbuffer,sizeof(recvbuffer));

       fputs(recvbuffer,stdout);

   }

   close(sockfd);

    return 0;
}