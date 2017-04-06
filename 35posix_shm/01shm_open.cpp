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


int main()
{
    int shmid = shm_open("/abc",O_CREAT | O_RDWR,0666);
    if(shmid ==  -1 )
    {
        ERR_EXIT("mq_open");
    }

    printf("shm_open sucess %d\n",shmid);

    close(shmid);

    return 0;
}