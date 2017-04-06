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
    if(shm_unlink("/abc") < 0)
    {
        ERR_EXIT("mq_unlink");
    }

    return 0;
}