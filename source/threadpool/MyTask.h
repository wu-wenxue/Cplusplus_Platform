#pragma once
#include "Task.h"

class MyTask :public Task
{
	// ����ȷ�����������������е�λ��
	friend bool operator<(MyTask  &lv,MyTask &rv)
	{
		return lv.priority_ < rv.priority_;
	}
public:
	MyTask();
	~MyTask();
	// �Զ����Run����
	virtual void Run();
	// ��������
	void setdata(int d);
private:
	int data_;
};

