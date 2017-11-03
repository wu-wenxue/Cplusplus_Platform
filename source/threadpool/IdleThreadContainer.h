#pragma once

#include <vector>

class MyThread;
class MyThreadPool;
class IdleThreadContainer
{
	
public:
	IdleThreadContainer();
	// 负责析构空闲容器中的线程
	~IdleThreadContainer();
	std::vector<MyThread*>::size_type size();
	// 将一个线程放回空闲容器中
	void push(MyThread *m);
	// 创建n个线程与线程池m相关联的线程放入空闲容器中
	void assign(int n,MyThreadPool* m);	
	// 返回位于空闲容器顶端的线程
	MyThread* top();
	// 弹出空闲容器顶端的线程
	void pop();
	// 删除一个指定的线程
	void erase(MyThread *m);
private:
	std::vector<MyThread*> idle_thread_container_;
	typedef std::vector<MyThread*> Container;
	typedef Container::iterator Iterator;
};

