#pragma once

#include <thread>
#include <mutex>
#include "Task.h"
#include "MyThread.h"
#include "BusyThreadContainer.h"
#include "IdleThreadContainer.h"
#include "TaskContainer.h"

class MyThread;
// �̳߳��࣬���ڴ��û���ȡ���񣬹�������ʵ�ֶ��̳߳����̵߳ĵ���
class MyThreadPool
{
public:
	
	MyThreadPool(){}
	// ����MyThreadPool����������number���̵߳Ŀ�������
	MyThreadPool(int number);
	~MyThreadPool();
	// ���һ�����ȼ�Ϊpriority����������������
	void AddTask(Task *Task,int priority);  // �������
	// �ڴ���n�������̵߳�����������
	void AddIdleThread(int n);    // ��ӿ����߳�
	// ��һ���̴߳ӹ���������ɾ�������ƻؿ���������
	void RemoveThreadFromBusy(MyThread *myThread);  //  �Ƴ�ִ������߳� 
	// �ж��Ƿ��п����̣߳����н�����Ӵ����������������������������У��ȴ�ִ��
	void Start(); 
	// �����̳߳ص�����
	void EndMyThreadPool();
private:
	// ���������࣬����std::list<MyThread*>ʵ�֣����湤��״̬���߳�
	BusyThreadContainer busy_thread_container_;
	// ���������࣬����std::vector<MyThread*>ʵ�֣����洦�ڿ���״̬���߳�
	IdleThreadContainer idle_thread_container_;
	bool issurvive_;
	//���������࣬����priority_queue<Task*>ʵ��,���������û����δִ�е�����
	TaskContainer task_container_;
	std::thread thread_this_;
	std::mutex busy_mutex_;
	std::mutex idle_mutex_;
	std::mutex task_mutex_;
	int number_of_thread_;
};
