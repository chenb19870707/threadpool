#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>



#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

void do_service(int conn)
{
      char buffer[1024];
        while(1)
        {
            memset(buffer,0,sizeof(buffer));
            int recvlen = read(conn,buffer,sizeof(buffer));
            if(recvlen == 0)
            {
                printf("client closed \n");
                break;
            }
            else if(recvlen == -1)
            {
                    ERR_EXIT("recvlen"); 
            }

            printf("from client %d \n",conn);
            fputs(buffer,stdout);
            write(conn,buffer,recvlen);
        }
}

int main()
{
    int listenfd;
    if((listenfd=socket(AF_UNIX,SOCK_STREAM,0)) < 0)
    {
     ERR_EXIT("socket");
    }

    unlink("test_socket");
    struct sockaddr_un serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path,"test_socket");

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

   pid_t pid;
   while(1)
   {
    if((conn = accept(listenfd,NULL,NULL)) < 0)
    {
        ERR_EXIT("accept");
    }

    pid = fork();
    if(pid == -1)
    {
       ERR_EXIT("pid");
    }

    if(pid == 0)
    {
        close(listenfd);
        do_service(conn);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(conn);
    }


   }

    return 0;
}