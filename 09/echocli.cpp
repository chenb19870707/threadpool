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

   struct packet sendbuf;
   struct packet recvbuf;
   memset(&sendbuf,0,sizeof(sendbuf));
   memset(&recvbuf,0,sizeof(recvbuf));
   while(fgets(sendbuf.buff,sizeof(sendbuf.buff),stdin) != NULL)
   {
       int n = strlen(sendbuf.buff);
       sendbuf.len = htonl(n);
       writen(sockfd,&sendbuf,n + 4);

        int recvlen = readn(sockfd,&recvbuf.len,4);
        if(recvlen == -1) 
        {
            ERR_EXIT("readn");
        }

        if(recvlen < 4)
        {
            printf("client closed \n");
            break;
        }

        n = ntohl(recvbuf.len);
        int ret = readn(sockfd,recvbuf.buff,n);
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

        memset(&sendbuf,0,sizeof(sendbuf));
        memset(&recvbuf,0,sizeof(recvbuf));
   }

   close(sockfd);

    return 0;
}