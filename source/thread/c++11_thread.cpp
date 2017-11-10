#include "c++11_thread.h"
#include <iostream>


Cxx11Thread::Cxx11Thread(Task1* task)
{
    m_task = task;
    m_running = 1;
}

Cxx11Thread::~Cxx11Thread()
{
    thread_stop();
}

void Cxx11Thread::start()
{
    t = std::thread(std::bind(&Cxx11Thread::run,this));
}

void Cxx11Thread::thread_detach()
{
    t.detach();
}

void Cxx11Thread::thread_stop()
{
    if(true == t.joinable())
    {
        m_running = false;
        t.join();
    }
}

void Cxx11Thread::run()
{

    m_task->run(&m_running);
}
