#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

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

int main()
{
    mqd_t mqid = mq_open("/abc",O_RDONLY);
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

    Student stu;
    memset(&stu,0,sizeof(stu));
    unsigned pri;

    if(mq_receive(mqid,(char *)&stu,attr.mq_msgsize,&pri) < 0)
    {
        ERR_EXIT("mq_receive");       
    }

    printf("Student name = %s,age=%d\n",stu.name,stu.age);

    mq_close(mqid);

    return 0;
}