#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \


void handler(int sig)
{
    printf("recv a sig=%d\n",sig);
    exit(EXIT_SUCCESS);
}

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

   pid_t pid = fork();
   if(pid == -1)
   {
     ERR_EXIT("fork"); 
   }

   if(pid == 0)
   {
        signal(SIGUSR1,handler);
       char sendbuff[1024] = {0};
       while (fgets(sendbuff,sizeof(sendbuff),stdin) != NULL)
       {
           write(conn,sendbuff,strlen(sendbuff));
           memset(sendbuff,0,sizeof(sendbuff));
       }

      printf("child exit\n");
       exit(EXIT_SUCCESS);
   }
   else
   {
        char buffer[1024];
        while(1)
        {
            memset(buffer,0,sizeof(buffer));
            int recvlen = read(conn,buffer,sizeof(buffer));
            if(recvlen == -1)
            {
                ERR_EXIT("read"); 
            }
            else if(recvlen == 0)
            {
                printf("peer closed\n");
                break;
            }

            fputs(buffer,stdout);
            //write(conn,buffer,recvlen);
        }

        close(conn);
        kill(pid,SIGUSR1);
        printf("parent exit\n");
        exit(EXIT_SUCCESS);
   }


   close(conn);
   close(listenfd);

    return 0;
}