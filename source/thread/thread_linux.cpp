#include "thread_linux.h"

CThread::CThread()
{
    tid = 0;
    pid = 0;
}

void CThread::Start(Runnable* r,void* arg)
{
    runnable = r;
    data = arg;
    if(CreateThread(&tid,(void*)CThread::hook,(void*)this) < 0)
    {
        std::cout << "create pthread err \n";
    }
    else
    {
        std::cout << "pthread start : " << tid << std::endl;
    }
}

void CThread::Stop()
{
    if(tid)
    {
        pthread_join(tid,NULL);
        tid = 0;
        pid = 0;
    }
}

int CThread::getpid()
{
    return pid;
}

int CThread::getthreadid()
{
    return tid;
}

int CThread::CreateThread(pthread_t *threadid,void *pfunction, void* arg)
{
    int ret = 0;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    {
        ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
        if(ret < 0)
        {
            pthread_attr_destroy(&attr);
            return ret;
        }
    }

    pthread_create(threadid,&attr,(void*(*)(void*))pfunction, arg);

    pthread_attr_destroy(&attr);

    return ret;
}

void* CThread::hook(void* arg)
{
    CThread* thread = (CThread*)arg;
    thread->pid = gettid();
    if(thread->runnable)
    {
        thread->runnable->Run(arg);
    }
    return (void*)NULL;
}

pid_t CThread::gettid()
{
    return syscall(__NR_gettid);
}
