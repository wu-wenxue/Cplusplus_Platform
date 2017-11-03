#pragma once
#include <list>


class MyThread;

class BusyThreadContainer
{
	
public:
	BusyThreadContainer();
	~BusyThreadContainer();
	// 将一个线程放入工作容器中
	void push(MyThread *m);
	// 返回工作容器的大小
	std::list<MyThread*>::size_type size();
	// 删除一个指定的线程
	void erase(MyThread *m);

private:
	std::list<MyThread*> busy_thread_container_;
	typedef std::list<MyThread*> Container;
	typedef Container::iterator Iterator;
};

