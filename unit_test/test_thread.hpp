#ifndef TEST_THREAD_HPP
#define TEST_THREAD_HPP

#include "thread/c++11_thread.h"
#include <iostream>
#include <string>
#include <common/common.h>

using namespace std;

class MyTask2: public Task1
{
public:
    virtual void run(void* arg)
    {
        int* running = (int*)arg;
        while(*running)
        {
            cout << "MyTask thread id : " << std::this_thread::get_id() << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    }
};


void test_thread1()
{
    MyTask2* mt = new MyTask2();

    Cxx11Thread* ct = new Cxx11Thread(mt);

    ct->start();

//    std::this_thread::sleep_for(std::chrono::seconds(10));

    thread_sleep(10);
    ct->thread_stop();
    thread_sleep(5);

}

void test_thread()
{
    test_thread1();
}

#include "thread/thread_linux.h"
#include "thread/thread_windows.h"

class R:public Runnable
{
public:
    ~R()
    {
        std::cout << "~R" << endl;
    }
    void Run()
    {
        std::cout << "Hello World" << endl;
    }
};

void test_thread_windows()
{
#ifdef _WIN32
    R r;
    CThread *t = NULL;
    t = new CThread(&r);
    t->Start();
    t->Join();
#endif
}





#endif // TEST_THREAD_HPP
