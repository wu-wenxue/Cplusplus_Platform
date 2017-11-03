#pragma once

// ���ȼ�
namespace
{
	enum  PRIORITY
	{

		MIN = 1, NORMAL = 25, MAX = 50
	};
}
// �����࣬������������ȼ�����һ������Run������������Ҫ����Task����Ҫ��ɵ�����д��Run������
class Task
{
	
public:
	Task()
	{

	}
	// �����̵߳����ȼ�����ֵ��1-50֮�䣬ֵԽ�����ȼ�Խ��
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
	// �߳�ִ�еķ������û���Ҫ��дΪ�Լ��ķ���
	virtual void Run() = 0;
protected:
	int priority_;
};
