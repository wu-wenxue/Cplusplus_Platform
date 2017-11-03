#include "MyThreadPool.h"
#include <iostream>
using namespace std;
MyThreadPool::MyThreadPool(int number)
{
//	MyThreadPool�Ĺ��캯��������number�������߳�����������У�
//		ͬʱ���������߳�thread_this�����ڽ����̳߳����̵߳ĵ���
	issurvive_ = true;
	number_of_thread_ = number;
	idle_thread_container_.assign(number, this);
	thread_this_ =thread(&MyThreadPool::Start, this);
	thread_this_.detach();
}
MyThreadPool::~MyThreadPool()
{

}
void MyThreadPool::EndMyThreadPool()
{
	issurvive_ =false;
}

void  MyThreadPool::AddIdleThread(int n)
{
	idle_mutex_.lock();
	idle_thread_container_.assign(n, this);
	number_of_thread_ += n;
	idle_mutex_.unlock();
}
void MyThreadPool::Start()
{
//	�����̶߳�Ӧ��Start����������һ����ѭ������ͣ���ж������������Ƿ������񣬺��Ƿ��п����߳���ִ���������У��������
//		����������������ӿ����߳�����ȡ��һ�������߳�����󶨣�ִ�и�����ͬʱ�����̴߳ӿ��������ƶ������������С�
//		���̳߳���Ҫ��������ʱ����surviveΪfalseʱ������Ҫ�жϹ��������Ƿ�Ϊ�գ�����Ϊ�գ���������������ڱ��߳�ִ�У��̳߳ز��ܽ�������
//		������Խ����̳߳ص����У�������ѭ��
	while (true)
	{
		if (issurvive_==false)
		{
			busy_mutex_.lock();
			if (busy_thread_container_.size()!=0)
			{
				busy_mutex_.unlock();
				continue;
			}
			busy_mutex_.unlock();
			break;
		}
		idle_mutex_.lock();
		if (idle_thread_container_.size() == 0)
		{
			idle_mutex_.unlock();
			continue;
		}
		idle_mutex_.unlock();
		task_mutex_.lock();
		if (task_container_.size() == 0)
		{
			task_mutex_.unlock();
			continue;
		}
		Task *b = task_container_.top();;
		task_container_.pop();
		task_mutex_.unlock();
		
		idle_mutex_.lock();
		MyThread *mythread = idle_thread_container_.top();;
		idle_thread_container_.pop();
		mythread->Assign(b);
		idle_mutex_.unlock();

		busy_mutex_.lock();
		busy_thread_container_.push(mythread);
		busy_mutex_.unlock();
		mythread->StartThread();
	}
}
void MyThreadPool::AddTask(Task *Task, int priority = (PRIORITY::NORMAL))
{
	
	Task->SetPriority(priority);
	task_mutex_.lock();
	task_container_.push(Task);
	task_mutex_.unlock();
}
void MyThreadPool::RemoveThreadFromBusy(MyThread *myThread)
{
//	��һ���̴߳������������Ƴ���������Żؿ��������У�
//		ʹ��busy_mutex_��idle_mutex_���м����ͽ�����ȷ�����ݵ�һ����
	busy_mutex_.lock();
	cout << "Thread:" << myThread->getthreadid()<< " remove from busylist" << endl;
	busy_thread_container_.erase(myThread);
	busy_mutex_.unlock();

	idle_mutex_.lock();
	idle_thread_container_.push(myThread);
	idle_mutex_.unlock();
}