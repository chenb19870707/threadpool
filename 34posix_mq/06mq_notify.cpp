#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define ERR_EXIT(m)                 \
            do                      \
            {                       \
                perror(m);          \     
                exit (EXIT_FAILURE);\
            }while(0)          


struct Student
{
    char name[32];
    int age;
};

size_t msg_size;
mqd_t mqid;
struct sigevent sevp;

void handle_sigusr1(int sig)
{
    printf("recv signal %d\n",sig);

    mq_notify(mqid,&sevp);
    Student stu;
    memset(&stu,0,sizeof(stu));
    unsigned pri;

    if(mq_receive(mqid,(char *)&stu,msg_size,&pri) < 0)
    {
        ERR_EXIT("mq_receive");       
    }

    printf("Student name = %s,age=%d\n",stu.name,stu.age);


}

int main()
{
    mqid = mq_open("/abc",O_RDONLY);
    if(mqid == (mqid) -1 )
    {
        ERR_EXIT("mq_open");
    }

    printf("mq_open sucess %d\n",mqid);

    signal(SIGUSR1,handle_sigusr1);

    mq_attr attr;
    if(mq_getattr(mqid,&attr) < 0)
    {
        ERR_EXIT("mq_getattr");        
    }
    msg_size = attr.mq_msgsize;


    sevp.sigev_notify = SIGEV_SIGNAL;
    sevp.sigev_signo = SIGUSR1;

    mq_notify(mqid,&sevp);

    for(;;)
        pause();
    mq_close(mqid);

    return 0;
}