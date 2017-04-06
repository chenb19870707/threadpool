#include "threadpool.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

void *thread_routine(void *arg)
{
    printf("thread 0x%x is starting\n",(int)pthread_self());
    thread_pool_t *pool = (thread_pool_t*)arg;
    struct timespec abstime;
    while (1)
    {
        int timeout = 0;
        condition_lock(&pool->ready);
        
        //等待队列由任务到来或者线程池销毁通知
        while(pool->first == NULL && !pool->quit)
        {
            clock_gettime(CLOCK_REALTIME,&abstime);
            abstime.tv_sec += 2;
            int status = condition_timewait(&pool->ready,&abstime);
            if(status == ETIMEDOUT)
            {
                printf("thread 0x%x is wait timeout\n",(int)pthread_self());
                timeout = 1;
                break;
            }
        }

        pool->idle--;
        if(pool->first != NULL)
        {
            //执行任务需要一定的时间，所以先解锁，以便生产者线程能添加任务
            tast_t* t = pool->first;
            pool->first = t->next;

            condition_unlock(&pool->ready);
            t->run(t->arg);
            delete t;
            condition_lock(&pool->ready);
        }

        //如果等待到线程池销毁通知,且任务都执行完毕了
        if(pool->quit && pool->first == NULL)
        {
            pool->counter --;
            if(pool->counter == 0)
            {
                condition_signal(&pool->ready);
            }
            condition_unlock(&pool->ready);
            break;
        }

        if(timeout&& pool->first == NULL)
        {
            pool->counter --;
            if(pool->counter == 0)
            {
                condition_signal(&pool->ready);
            }
            condition_unlock(&pool->ready);
            break;
        }

        condition_unlock(&pool->ready);
    }

    printf("thread 0x%x is exiting\n",(int)pthread_self());
    return NULL;
}

//初始化线程池
void threadpool_init(thread_pool_t* pool,int threads)
{
    condition_init(&pool->ready);
    pool->first = NULL;
    pool->last = NULL;
    pool->counter = 0;
    pool->idle = 0;
    pool->max_threads = threads;
    pool->quit = 0;
}

//往线程池添加任务
void threadpool_add_task(thread_pool_t* pool,void *(*run)(void *arg),void *arg)
{
    tast_t *newtask = new tast_t();
    newtask->run = run;
    newtask->arg = arg;
    newtask->next = NULL;

    condition_lock(&pool->ready);
    if(pool->first == NULL)
    {
        pool->first = newtask;
    }
    else
    {
        pool->last->next = newtask;
    }

    pool->last = newtask;

    if(pool->idle > 0)
    {
        condition_signal(&pool->ready);
    }
    else if(pool->counter < pool->max_threads)
    {
        //没有等待线程，并且当前线程数不超过最大线程数，则创建一个新线程
       pthread_t tid; 
       pthread_create(&tid,NULL,thread_routine,pool);
       pool->counter++;
    }

    condition_unlock(&pool->ready);
}

//销毁线程池
void threadpool_destroy(thread_pool_t* pool)
{
        if(pool->quit) 
            return;

        condition_lock(&pool->ready);
        pool->quit = 1;
        if(pool->counter > 0)
        {
            if(pool->idle > 0)
            {
                condition_broadcast(&pool->ready);
            }

            //处于执行任务状态的线程，不会受到广播
            //线程池需要执行等待任务中的线程全部退出
            while(pool->counter > 0)
            {
                condition_wait(&pool->ready);
            }
        }

        condition_unlock(&pool->ready);
        condition_destroy(&pool->ready);
}

void* mytask(void *arg)
{
    int *para = (int*)arg;
    printf("thread 0x%x is working on task %d\n",(int)pthread_self(),*para);
    sleep(5);
    delete para;
    return NULL;
}

int main()
{
    thread_pool_t pool;
    threadpool_init(&pool,3);
    for(int i =0;i < 10;i++)
    {
        int *arg = new int;
        *arg = i;
        threadpool_add_task(&pool,mytask,arg);
    }

    threadpool_destroy(&pool);
    return 0;
}
