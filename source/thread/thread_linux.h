#ifndef THREAD_LINUX_H
#define THREAD_LINUX_H

#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <iostream>

class Runnable
{
public:
    virtual ~Runnable(){}
    virtual void* Run(void* arg) = 0;
};

class CThread
{
public:
    CThread();
    virtual ~CThread(){}
    void Start(Runnable* r,void* arg);
    void Stop();
    int getpid();
    int getthreadid();

private:
    int CreateThread(pthread_t* threadid, void* pfunction, void* arg);

    static void* hook(void* arg); //global function

private:
    static pid_t gettid();
    pthread_t tid;  // thread id
    int pid;  // process id
    void *data;

    Runnable* runnable;
};


#endif // THREAD_LINUX_H
