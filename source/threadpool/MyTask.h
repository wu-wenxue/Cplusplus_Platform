#pragma once
#include "Task.h"

class MyTask :public Task
{
	// 用于确定任务在任务容器中的位置
	friend bool operator<(MyTask  &lv,MyTask &rv)
	{
		return lv.priority_ < rv.priority_;
	}
public:
	MyTask();
	~MyTask();
	// 自定义的Run方法
	virtual void Run();
	// 设置数据
	void setdata(int d);
private:
	int data_;
};

