#include <unistd.h>
#include <sys/types.h>
 #include <pthread.h>

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

void* thread_routine(void *)
{
    for(int i=0;i < 20;i++)
    {
        printf("B");
        fflush(stdout);
        usleep(10);

        if( i == 4) pthread_exit((void*)"ABC");
    }

    sleep(1);
    return 0;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,thread_routine,NULL);
    if(ret != 0)
    {
        fprintf(stderr,"pthread_create:%s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }

    for(int i=0;i < 20;i++)
    {
        printf("A");
        fflush(stdout);
        usleep(10);
    }

    void *value;
    if((ret = pthread_join(tid,&value)) != 0)
    {
        fprintf(stderr,"pthread_join:%s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }

    printf("\n");

    printf("ret msg=%s\n",(char*)value);
    return 0;
}