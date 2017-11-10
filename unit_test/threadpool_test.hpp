#ifndef THREADPOOL_TEST_HPP
#define THREADPOOL_TEST_HPP

#include "threadpool/MyThreadPool.h"
#include "threadpool/MyTask.h"
#include <iostream>

using namespace std;



//创建了一个含有10个空闲线程的线程池，和50个MyTask任务，并将其放入线程池中等待运行
//在循环中，用户输入100可以再添加一个任务到线程池中等待运行，输入 - 1结束线程池的运行。


int threadpool_test()
{
    MyThreadPool mythreadPool(10);

    MyTask j[50];
    for (int i = 0; i < 50;i++)
    {
        j[i].setdata(i);
    }
    for (int i = 0; i < 50; i++)
    {
        mythreadPool.AddTask(&j[i],i);
    }
    int i;
    //按100添加一个任务
    //按-1结束线程池
    while (true)
    {
        cin >> i;
        if (i == 100)
        {
            MyTask j;
            j.setdata(i);
            mythreadPool.AddTask(&j, i);
        }
        if (i == -1)
        {
            mythreadPool.EndMyThreadPool();
            break;
        }
    }
    system("pause");
}

#include "threadpool/wxthreadpool.h"
#include "logger/wxlogger.h"
#include "common/common.h"

Wxlogger* logger = Wxlogger::getInstance();

class MyWxTask : public WxTask
{
public:
    MyWxTask(int n)
    {
        m_num = n;
    }

    virtual void run()
    {
        Wxlogger* logger = Wxlogger::getInstance();
        for(int i = 0;i < m_num; i++)
        {
//            thread_sleep(1);
            WXLOG_WARN(logger,"(" << std::this_thread::get_id() << ") " << " this task is running " << i);
        }
    }

private:
    int m_num;
};

void test_wxthreadpool()
{

    WxThreadPool* tp = new WxThreadPool(4);

    for(int i = 0; i < 20; i++)
    {
        MyWxTask* task = new MyWxTask(100000);
        tp->addTask(task);
    }

    thread_sleep(100);
}

#endif // THREADPOOL_TEST_HPP
