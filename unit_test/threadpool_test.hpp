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


#endif // THREADPOOL_TEST_HPP
