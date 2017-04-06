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
    mqd_t mqid = mq_open("/abc",O_RDWR);
    if(mqid == (mqid) -1 )
    {
        ERR_EXIT("mq_open");
    }

    printf("mq_open sucess %d\n",mqid);

    mq_attr attr;
    if(mq_getattr(mqid,&attr) < 0)
    {
        ERR_EXIT("mq_getattr");        
    }

    printf("mq_flags=%ld,mq_maxmsg=%ld,mq_msgsize=%ld,mq_curmsgs=%ld\n",attr.mq_flags,attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);

    mq_close(mqid);

    return 0;
}