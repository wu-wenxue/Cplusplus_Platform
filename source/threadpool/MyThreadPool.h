#pragma once

#include <thread>
#include <mutex>
#include "Task.h"
#include "MyThread.h"
#include "BusyThreadContainer.h"
#include "IdleThreadContainer.h"
#include "TaskContainer.h"

class MyThread;
// 线程池类，用于从用户获取任务，管理任务，实现对线程池中线程的调度
class MyThreadPool
{
public:
	
	MyThreadPool(){}
	// 构造MyThreadPool，创建包含number个线程的空闲容器
	MyThreadPool(int number);
	~MyThreadPool();
	// 添加一个优先级为priority的任务到任务容器中
	void AddTask(Task *Task,int priority);  // 添加任务
	// 在创建n个空闲线程到空闲容器中
	void AddIdleThread(int n);    // 添加空闲线程
	// 将一个线程从工作容器中删除，并移回空闲容器中
	void RemoveThreadFromBusy(MyThread *myThread);  //  移除执行完的线程 
	// 判断是否有空闲线程，如有将任务从从任务容器中提出，放入空闲容器中，等待执行
	void Start(); 
	// 结束线程池的运行
	void EndMyThreadPool();
private:
	// 工作容器类，采用std::list<MyThread*>实现，储存工作状态的线程
	BusyThreadContainer busy_thread_container_;
	// 空闲容器类，采用std::vector<MyThread*>实现，储存处于空闲状态的线程
	IdleThreadContainer idle_thread_container_;
	bool issurvive_;
	//任务容器类，采用priority_queue<Task*>实现,储存所有用户添加未执行的任务
	TaskContainer task_container_;
	std::thread thread_this_;
	std::mutex busy_mutex_;
	std::mutex idle_mutex_;
	std::mutex task_mutex_;
	int number_of_thread_;
};
