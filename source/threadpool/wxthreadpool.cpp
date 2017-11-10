#include "wxthreadpool.h"

WxThreadPool::WxThreadPool()
{

}

WxThreadPool::WxThreadPool(int num)
{
    issurvive = true;
    thread_count = num;
    for(int i = 0;i < num; i++)
    {
        std::thread *t = new std::thread(std::bind(&WxThreadPool::start,this));
        vec_thread.push_back(t);
//        t->detach();
    }
}

WxThreadPool::~WxThreadPool()
{
    issurvive = false;
    for(std::thread* t : vec_thread)
    {
        if(t->joinable()  == true)
        {
            t->join();
        }
    }
}

void WxThreadPool::start()
{
    while(true)
    {
        if(issurvive == false)
        {
            break;
        }
        task_mutex.lock();
        if(task_q.size() > 0)
        {
            WxTask* task = task_q.top();
            task_q.pop();
            WXLOG_WARN(logger,"(" << std::this_thread::get_id() << ") " << "task_q size : " << task_q.size());
            task_mutex.unlock();
            task->run();
        }
        task_mutex.unlock();

    }
}

void WxThreadPool::addTask(WxTask* task)
{
    task_mutex.lock();
    task_q.push(task);
    task_mutex.unlock();
}

WxTask* WxThreadPool::getTask()
{
    WxTask* task = task_q.top();
    task_q.pop();
    return task;
}

void WxThreadPool::endThreadPoll()
{

}
