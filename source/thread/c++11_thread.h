#ifndef C11_THREAD_H
#define C11_THREAD_H
#include <thread>


class Task1
{
public:
    virtual void run(void* arg) = 0;
};

class Cxx11Thread
{
public:
    Cxx11Thread(Task1* task);
    ~Cxx11Thread();

    void start();

    void thread_detach();

    void thread_stop();

protected:

    void run();

private:
    Task1 *m_task;
    std::thread t;
    int m_running;
};

#endif // C11_THREAD_H
