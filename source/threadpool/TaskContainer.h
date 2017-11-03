#pragma once
#include <queue>
class Task;
class TaskContainer
{
public:
	TaskContainer();
	~TaskContainer();
	// 将一个任务放入任务容器中
	void push(Task *);
	// 返回任务容器顶端的任务
	Task* top();
	// 将任务容器顶端的线程弹出
	void pop();
	// 返回任务容器的大小
	std::priority_queue<Task*>::size_type size();
private:
	std::priority_queue<Task*> task_container_;
};

