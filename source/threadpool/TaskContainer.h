#pragma once
#include <queue>
class Task;
class TaskContainer
{
public:
	TaskContainer();
	~TaskContainer();
	// ��һ�������������������
	void push(Task *);
	// ���������������˵�����
	Task* top();
	// �������������˵��̵߳���
	void pop();
	// �������������Ĵ�С
	std::priority_queue<Task*>::size_type size();
private:
	std::priority_queue<Task*> task_container_;
};

