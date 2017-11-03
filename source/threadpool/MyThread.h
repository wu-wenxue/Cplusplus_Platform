#pragma once

#include "Task.h"
#include <thread>


class MyThreadPool;
class Task;

//�߳��࣬��װ��C++11��thread��ÿһ���߳̿��Թ���һ��Task����ִ����Run����
class MyThread
{
	friend bool operator==(MyThread my1, MyThread my2);
	friend bool operator!=(MyThread my1, MyThread my2);
public:
	// ����һ��MyThread���󣬽��Լ���ָ�����̳߳����������
	MyThread(MyThreadPool *pool);
	// ��һ����������߳����������
	void Assign(Task *Task);
	// ������Task��Run������ͬʱ��Task��Run�����������Լ��ӹ��������ƻؿ�������
	void Run();
	// ִ���̵߳�Run��������ִ����Task��Run����
	void StartThread();
	// ��ȡ�̵߳�id��
	int getthreadid();
	// �����߳������е�ʱ����join����detach��
	void setisdetach(bool isdetach);	
private:
	MyThreadPool *mythreadpool_;
	static int  s_threadnumber;
	bool isdetach_;
	Task *task_;
	int threadid_;
	std::thread thread_;
};




