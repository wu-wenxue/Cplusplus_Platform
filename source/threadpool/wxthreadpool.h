#ifndef WXTHREADPOOL_H
#define WXTHREADPOOL_H

#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include "logger/wxlogger.h"

class WxTask
{
public:
    virtual void run() = 0;
};

class WxThread
{
public:

};

class WxThreadPool
{
public:
    WxThreadPool();
    WxThreadPool(int num);
    ~WxThreadPool();

    void start();

    void addTask(WxTask* task);

    WxTask *getTask();

    void endThreadPoll();

private:
    std::vector<std::thread*> vec_thread;
    std::priority_queue<WxTask*> task_q;

    bool issurvive;
    int thread_count;
    std::mutex task_mutex;
    Wxlogger* logger = Wxlogger::getInstance();
};

#endif // WXTHREADPOOL_H
