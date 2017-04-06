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
    mqd_t mqid = mq_open("/abc",O_WRONLY);
    if(mqid == (mqid) -1 )
    {
        ERR_EXIT("mq_open");
    }

    printf("mq_open sucess %d\n",mqid);

    Student stu;
    strcpy(stu.name,"chen");
    stu.age = 20;

    mq_send(mqid,(const char *)&stu,sizeof(Student),1);
    mq_close(mqid);

    return 0;
}