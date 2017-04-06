#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>


#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)               \

int main()
{
     struct rlimit rl;
    if(getrlimit(RLIMIT_NOFILE,&rl) < 0 )
        ERR_EXIT("getrlimit");

    printf("%ld %ld \n",rl.rlim_cur,rl.rlim_max);
}