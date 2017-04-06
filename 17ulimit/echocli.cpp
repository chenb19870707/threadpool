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


void echo_cli(int sockfd)
{
   fd_set rset;
   FD_ZERO(&rset);

   int nready = 0;
   int fd_stdin = fileno(stdin);
   int maxfd = sockfd>fd_stdin?sockfd:fd_stdin;
   char sendbuf[1024] = {0};
   char recvbuf[1024] = {0};
   while(1)
   {
       FD_SET(sockfd,&rset);
       FD_SET(fd_stdin,&rset);
       nready = select(maxfd + 1, &rset,NULL,NULL,NULL);
       if(nready == -1) ERR_EXIT("select");

       if(nready == 0) continue;

       if(FD_ISSET(sockfd,&rset))
       {
            int recvlen = readline(sockfd,recvbuf,sizeof(recvbuf));
            if(recvlen == -1) 
            {
                ERR_EXIT("readline");
            }

            if(recvlen  == 0)
            {
                printf("server closed \n");
                break;
            }

            fputs(recvbuf,stdout);
            memset(&recvbuf,0,sizeof(recvbuf));
       }

      if(FD_ISSET(fd_stdin,&rset))
      {
          memset(sendbuf,0,sizeof(sendbuf));
          if(fgets(sendbuf,sizeof(sendbuf),stdin) == NULL) break;

          writen(sockfd,sendbuf,strlen(sendbuf));
     }
   }

   close(sockfd);
}

void handle_pipe(int sig)
{
    printf("handle_pipe \n");
}

int main()
{

    signal(SIGPIPE,handle_pipe);

    //signal(SIGPIPE,SIG_IGN;

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

    struct sockaddr_in localaddr;
    socklen_t addrlen = sizeof(localaddr);
    if((getsockname(sockfd,(struct sockaddr*)&localaddr,&addrlen)) < 0)
    {
      ERR_EXIT("getsockname");
    }

     printf("local addr %s port %d \n",inet_ntoa(localaddr.sin_addr),ntohs(localaddr.sin_port));

     echo_cli(sockfd);

  
    return 0;
}