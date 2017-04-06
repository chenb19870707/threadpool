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

  pid_t pid = fork();
   if(pid == -1)
   {
     ERR_EXIT("fork"); 
   }

   if(pid == 0)
   {
        char recvbuffer[1024] = {0};
        while(1)
        {
            memset(recvbuffer,0,sizeof(recvbuffer));
            int recvlen = read(sockfd,recvbuffer,sizeof(recvbuffer));
            if(recvlen == -1)
            {
                ERR_EXIT("read"); 
            }
            else if(recvlen == 0)
            {
                printf("peer closed\n");
                break;
            }

            fputs(recvbuffer,stdout);
        }

      printf("child exit\n");
      kill(getppid(),SIGUSR1);
      close(sockfd);
      exit(EXIT_SUCCESS);
   }
   else
   {
       signal(SIGUSR1,handler);
       char sendbuff[1024] = {0};
       while (fgets(sendbuff,sizeof(sendbuff),stdin) != NULL)
       {
           write(sockfd,sendbuff,strlen(sendbuff));
           memset(sendbuff,0,sizeof(sendbuff));
       }

       printf("parent exit\n");
       exit(EXIT_SUCCESS);
   }



    return 0;
}