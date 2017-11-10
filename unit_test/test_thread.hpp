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

#endif // TEST_THREAD_HPP
