#ifndef _SYS_UTIL_H_
#define _SYS_UTIL_H_

#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>　
#include <stdlib.h>
#include <fcntl.h>


#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

int read_timeout(int fd,unsigned int wait_seconds);

int write_timeout(int fd,unsigned int wait_seconds);

int accept_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);

int connect_timeout(int fd,struct sockaddr_in *addr,unsigned int wait_seconds);

#endif