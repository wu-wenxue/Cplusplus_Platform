#ifndef C11_THREAD_H
#define C11_THREAD_H
#include <thread>

class Task
{
public:
    virtual void run(void* arg) = 0;
};

class Cxx11Thread
{
public:
    Cxx11Thread(Task* task)
    {
        m_task = task;
        m_running = 1;
    }

    void start()
    {
        t = std::thread(std::bind(&Cxx11Thread::run,this));
    }

    void thread_detach()
    {
        t.detach();
    }

    void thread_stop()
    {
        if(true == t.joinable())
        {
            m_running = false;
            t.join();
        }
    }



protected:

    void run()
    {

        m_task->run(&m_running);
    }

private:
    Task *m_task;
    std::thread t;
    int m_running;
};

#endif // C11_THREAD_H
