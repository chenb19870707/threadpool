#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <fcntl.h>


#include <vector>
#include <algorithm>

typedef std::vector<struct epoll_event> EventList;

#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

void activate_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd,F_GETFL);
    if(flags == -1)
        ERR_EXIT("fcntl");

    flags |= O_NONBLOCK;
    ret = fcntl(fd,F_SETFL,flags);
    if(flags == -1)
        ERR_EXIT("fcntl");
}

void deactivate_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd,F_GETFL);
    if(flags == -1)
        ERR_EXIT("fcntl");

    flags &= ~O_NONBLOCK;
    ret = fcntl(fd,F_SETFL,flags);
    if(flags == -1)
        ERR_EXIT("fcntl");
}

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
    signal(SIGCHLD,SIG_IGN);
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

   std::vector<int> client;
   int epollfd = epoll_create1(EPOLL_CLOEXEC);

   struct epoll_event event;
   event.data.fd = listenfd;
   event.events = EPOLLIN | EPOLLET;
   epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&event);

   EventList events(16);
   struct sockaddr_in peeraddr;
   socklen_t peerlen;
   int conn;

   int nready;

   while(1)
   {
       nready = epoll_wait(epollfd,&*events.begin(),static_cast<int>(events.size()),-1);
        if(nready == -1) 
        {
            if(errno == EINTR) 
                continue;

            ERR_EXIT("epoll_wait");
        }

       if(nready == 0) continue;

       if((size_t)nready == events.size())
       {
           events.resize(2*events.size());
       }

       for(int i = 0;i < nready;i++)
       {
           if(events[i].data.fd == listenfd)
           {
                peerlen = sizeof(peeraddr);
                if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen)) < 0)
                {
                    ERR_EXIT("accept");
                }

                printf("cli addr %s port %d \n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));

                client.push_back(conn);

                activate_nonblock(conn);

                event.data.fd = conn;
                event.events = EPOLLIN | EPOLLET;
                epoll_ctl(epollfd,EPOLL_CTL_ADD,conn,&event);
                
                if(--nready <= 0) continue;
           }
           else if(events[i].events & EPOLLIN)
           {
                conn = events[i].data.fd;
                if(conn < 0)
                    continue;
                
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
                    
                    event =events[i];
                    epoll_ctl(epollfd,EPOLL_CTL_DEL,conn,&event);

                    client.erase(std::remove(client.begin(),client.end(),conn),client.end());

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