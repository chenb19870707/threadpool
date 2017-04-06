#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

int main()
{
    for(int i = 0; i < 10000;i++)
    {
        int sockfd;
        if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
        {
            sleep(4);
        ERR_EXIT("socket");
        }

        struct sockaddr_in serveraddr;
        memset(&serveraddr,0,sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(5188);
        serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
        {
            ERR_EXIT("connect");
        }

        struct sockaddr_in localaddr;
        socklen_t addrlen = sizeof(localaddr);
        if((getsockname(sockfd,(struct sockaddr*)&localaddr,&addrlen)) < 0)
        {
        ERR_EXIT("getsockname");
        }

        printf("connection index=>%d local addr %s port %d \n",i,inet_ntoa(localaddr.sin_addr),ntohs(localaddr.sin_port));

    }
    return 0;
}