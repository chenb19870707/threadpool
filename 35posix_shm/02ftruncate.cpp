#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

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
    int shmid = shm_open("/abc",O_CREAT | O_RDWR,0666);
    if(shmid ==  -1 )
    {
        ERR_EXIT("mq_open");
    }

    printf("shm_open sucess %d\n",shmid);

    if(ftruncate(shmid,sizeof(Student)) < 0)
    {
        ERR_EXIT("ftruncate");        
    }

    struct stat buf;
    if(fstat(shmid,&buf) < 0)
    {
           ERR_EXIT("fstat");         
    }

    printf("size=%ld,mode=%o\n",buf.st_size,buf.st_mode & 07777);

    close(shmid);

    return 0;
}