
while(1)
{
    pthread_mutex_lock(&g_mutex);
    while(nready == 0)
    {
        pthread_cond_wait(&g_cond,&g_mutex);
    }
    --nready;
    pthread_mutex_unlock(&g_mutex);
    sleep(1);
}


while(1)
{
    pthread_mutex_lock(&g_mutex);

    ++nready;
    if(nready > 0)
    {
        pthread_cond_signal(&g_cond);
    }
    pthread_mutex_unlock(&g_mutex);
    sleep(5);
}

pthread_cond_wait 内部做的三件事情：
1.对g_mutex解锁
2.等待条件，直到有线程发起通知
3.对g_mutex解锁

pthread_cond_signal
向第一个等待条件的线程发起通知，如果没有任何一个线程处理等待条件的状态，这个通知奖杯忽略

pthrad_conn_brodcast
向所有等待线程发起通知


