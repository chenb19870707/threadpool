#include <unistd.h>
#include <sys/types.h>
 #include <pthread.h>
 #include <semaphore.h>

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

#define CONSUMERS_COUNT 1
#define PRODUCERS_COUNT 1      

pthread_mutex_t g_mutex;
pthread_cond_t g_cond;

pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT];

int nready = 0;

void* consume(void* arg)
{
    int num = (long)arg;
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        while(nready == 0)
        {
            printf("%d thread begin wait condition \n",num);
            pthread_cond_wait(&g_cond,&g_mutex);
        }
        printf("%d thread end wait condition \n",num);
        --nready;
        pthread_mutex_unlock(&g_mutex);
        sleep(1);
    }
    return NULL;
}

void* produce(void* arg)
{
    int num = (long)arg;
    while(1)
    {
        pthread_mutex_lock(&g_mutex);

        printf("%d thread  signal \n",num);
        ++nready;
        pthread_cond_signal(&g_cond);
        pthread_mutex_unlock(&g_mutex);
        sleep(5);
    }

    return NULL;
}

int main()
{

    pthread_mutex_init(&g_mutex,NULL);
    pthread_cond_init(&g_cond,NULL);

    for(int i = 0 ; i < CONSUMERS_COUNT;i++)
    {
        pthread_create(&g_thread[i],NULL,consume,(void*)i);
    }

    for(int i = 0 ; i < PRODUCERS_COUNT;i++)
    {
        pthread_create(&g_thread[i + CONSUMERS_COUNT],NULL,produce,(void*)(i + CONSUMERS_COUNT));
    }

    for(int i = 0 ; i < CONSUMERS_COUNT +  PRODUCERS_COUNT;i++)
    {
        pthread_join(g_thread[i],NULL);
    }

    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_cond);
    return 0;
}