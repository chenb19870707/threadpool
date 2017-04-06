#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)          


int main()
{
    mqd_t mqid = mq_unlink("/abc");
    if(mqid == (mqid) -1 )
    {
        ERR_EXIT("mq_unlink");
    }

    printf("mq_unlink sucess %d\n",mqid);

    return 0;
}