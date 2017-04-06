#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "condition.h"

//任务结构体，讲任务放入队列由线程池中的线程执行
struct tast_t
{
    void *(*run)(void *arg);        //任务回调函数
    void *arg;                      //回调函数参数
    tast_t *next;
};

//线程池结构体
struct thread_pool_t
{
    condition_t ready;          //任务准备就绪或者线程池销毁通知
    tast_t *first;              //队列头指针
    tast_t *last;               //队列尾指针
    int counter;                //线程池中当前线程数
    int idle;                   //线程池中当前正在等待任务的线程数
    int max_threads;            //线程池中最大允许的线程数
    int quit;                   //销毁线程池的时候置1
};

//初始化线程池
void threadpool_init(thread_pool_t* pool,int threads);

//往线程池添加任务
void threadpool_add_task(thread_pool_t* pool,void *(*run)(void *arg),void *arg);

//销毁线程池
void threadpool_destroy(thread_pool_t* pool);

#endif