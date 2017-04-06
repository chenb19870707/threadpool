#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

struct packet
{
    int len;
    char buff[1024];
};

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

void do_service(int conn)
{
        struct packet recvbuf;
        while(1)
        {
            memset(&recvbuf,0,sizeof(recvbuf));
            int recvlen = readn(conn,&recvbuf.len,4);
            if(recvlen == -1) 
            {
                ERR_EXIT("readn");
            }

            if(recvlen < 4)
            {
                printf("client closed \n");
                break;
            }

            int n = ntohl(recvbuf.len);
            int ret = readn(conn,recvbuf.buff,n);
            if(ret == -1) 
            {
                ERR_EXIT("readn");
            }

            if(ret < n)
            {
                printf("client closed \n");
                break;
            }

            fputs(recvbuf.buff,stdout);
            writen(conn,&recvbuf,4+n);
        }
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

   pid_t pid;
   while(1)
   {
    if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen)) < 0)
    {
        ERR_EXIT("accept");
    }

    printf("cli addr %s port %d \n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));

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