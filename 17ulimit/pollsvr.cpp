#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>


#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

ssize_t readn(int fd, void *buf, size_t count)
{
   size_t nleft = count;
   size_t nread;
   char *bufp = (char*)buf;

   while(nleft > 0)
   {
       if( (nread = read(fd,bufp,nleft)) < 0)
       {
           if(errno == EINTR) continue;
           return -1;
       }
       else if(nread == 0)
       {
          return count -nleft;
       }

       bufp += nread;
       nleft -= nread;
   } 

   return count;
};

ssize_t writen(int fd, const void *buf, size_t count)
{
   size_t nleft = count;
   int nwritten;
   char *bufp = (char*)buf;

   while(nleft > 0)
   {
       if( (nwritten = write(fd,bufp,nleft)) < 0)
       {
           if(errno == EINTR) continue;
           return -1;
       }
       else if(nwritten == 0) continue;

       bufp += nwritten;
       nleft -= nwritten;
   } 

   return count; 
}

ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
   while(1)
   {
      int ret = recv(sockfd,buf,len,MSG_PEEK);
      if(ret == -1 && errno == EINTR) continue;

      return ret;
   } 
}

ssize_t readline(int sockfd, void *buf, size_t maxline)
{
   int ret;
   int nread;
   char *bufp =(char*) buf;
   int nleft = maxline;
   while(1)
   {
       ret = recv_peek(sockfd,bufp,nleft);
       if(ret < 0)
       {
            return ret;
       } 
       else if(ret == 0)
       {
           return ret;
       }

       nread = ret;
       for(int i = 0;i < nread;i++)
       {
           if(bufp[i] == '\n')
           {
               ret = readn(sockfd,bufp,i+1);
               if(ret != i+1) exit(EXIT_FAILURE);

               return ret;
           }
       }

       if(nread > nleft)  exit(EXIT_FAILURE);

       nleft -=nread;
       ret =readn(sockfd,bufp,nread);
      if(ret != nread) exit(EXIT_FAILURE);

      bufp+= nread;
   }

   return -1;
}

void echo_svr(int conn)
{
        char recvbuf[1024];
        while(1)
        {
            memset(&recvbuf,0,sizeof(recvbuf));
            int recvlen = readline(conn,recvbuf,sizeof(recvbuf));
            if(recvlen == -1) 
            {
                ERR_EXIT("readline");
            }

            if(recvlen  == 0)
            {
                printf("client closed \n");
                break;
            }

            fputs(recvbuf,stdout);
            writen(conn,recvbuf,strlen(recvbuf));
        }
}

void handle_sigchld(int sig)
{
    //wait(NULL);

    printf("handle_sigchld\n");
    while(waitpid(-1,NULL,WNOHANG) > 0);
}

int main()
{
    //signal(SIGCHLD,SIG_IGN);

    signal(SIGCHLD,handle_sigchld);

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
   socklen_t peerlen;
   int conn;

   sruct pollfd client[2048];
   int maxi = 0;
   for(int i = 0;i < 2047;i++)
   {
       client[i].fd = -1;
   }

   int nready;
   client[0].fd = listenfd;
   client[0].event = POLLIN;

   while(1)
   {
       nready = poll(client,maxi + 1,-1);
        if(nready == -1) 
        {
            if(errno == EINTR) 
                continue;

            ERR_EXIT("poll");
        }

       if(nready == 0) continue;

       if(client[0].revent & POLLIN )
        {  
            peerlen = sizeof(peeraddr);
            if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen)) < 0)
            {
                ERR_EXIT("accept");
            }

            int i = 0; 
            for(i = 0;i < 2048;i++)
            {
                if(client[i].fd < 0)
                {
                    client[i].fd = conn;
                    client[i].event = POLLIN;
                    maxi = i>maxi?i:maxi;
                    break;
                }
            }

            if(i == 2048)
            {
                ERR_EXIT("too many connections");
            }

            printf("cli addr %s port %d \n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));

            if(--nready <= 0) continue;
        }    

        for(int i = 1; i <= maxi;i++)
        {
            conn = client[i].fd;

            if(conn == -1) continue;
            
            if(client[i].revent & POLLIN)
            {
                char recvbuf[1024];
                memset(&recvbuf,0,sizeof(recvbuf));
                int recvlen = readline(conn,recvbuf,sizeof(recvbuf));
                if(recvlen == -1) 
                {
                    ERR_EXIT("readline");
                }

                if(recvlen  == 0)
                {
                    printf("client closed \n");
                    client[i].fd = -1;
                    break;
                }

                fputs(recvbuf,stdout);
                writen(conn,recvbuf,strlen(recvbuf));

                if(--nready <= 0) break;
            }
        }   
   }

    return 0;
}