#pragma once

#include <vector>

class MyThread;
class MyThreadPool;
class IdleThreadContainer
{
	
public:
	IdleThreadContainer();
	// �����������������е��߳�
	~IdleThreadContainer();
	std::vector<MyThread*>::size_type size();
	// ��һ���̷߳Żؿ���������
	void push(MyThread *m);
	// ����n���߳����̳߳�m��������̷߳������������
	void assign(int n,MyThreadPool* m);	
	// ����λ�ڿ����������˵��߳�
	MyThread* top();
	// ���������������˵��߳�
	void pop();
	// ɾ��һ��ָ�����߳�
	void erase(MyThread *m);
private:
	std::vector<MyThread*> idle_thread_container_;
	typedef std::vector<MyThread*> Container;
	typedef Container::iterator Iterator;
};

