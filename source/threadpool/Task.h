#pragma once

// 优先级
namespace
{
	enum  PRIORITY
	{

		MIN = 1, NORMAL = 25, MAX = 50
	};
}
// 任务类，内有任务的优先级，和一个纯虚Run方法，我们需要派生Task，将要完成的任务写到Run方法中
class Task
{
	
public:
	Task()
	{

	}
	// 设置线程的优先级，数值在1-50之间，值越大，优先级越高
	void SetPriority(int priority)
	{
		if (priority>(PRIORITY::MAX))
		{
			priority = (PRIORITY::MAX);
		}
		else if (priority>(PRIORITY::MAX))
		{
			priority = (PRIORITY::MIN);
		}
	}
	// 线程执行的方法，用户需要重写为自己的方法
	virtual void Run() = 0;
protected:
	int priority_;
};
