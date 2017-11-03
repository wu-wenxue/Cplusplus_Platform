#pragma once
#include <list>


class MyThread;

class BusyThreadContainer
{
	
public:
	BusyThreadContainer();
	~BusyThreadContainer();
	// ��һ���̷߳��빤��������
	void push(MyThread *m);
	// ���ع��������Ĵ�С
	std::list<MyThread*>::size_type size();
	// ɾ��һ��ָ�����߳�
	void erase(MyThread *m);

private:
	std::list<MyThread*> busy_thread_container_;
	typedef std::list<MyThread*> Container;
	typedef Container::iterator Iterator;
};

