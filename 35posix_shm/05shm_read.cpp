#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

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
    int shmid = shm_open("/abc", O_RDONLY,0);
    if(shmid ==  -1 )
    {
        ERR_EXIT("mq_open");
    }

    printf("shm_open sucess %d\n",shmid);

    struct stat buf;
    if(fstat(shmid,&buf) < 0)
    {
           ERR_EXIT("fstat");         
    }

    printf("size=%ld,mode=%o\n",buf.st_size,buf.st_mode & 07777);

    Student *p = (Student *)mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,shmid,0);
    if(p == MAP_FAILED)
    {
           ERR_EXIT("mmap");         
    }

    printf("name=%s,age=%d\n",p->name,p->age);

    close(shmid);

    return 0;
}