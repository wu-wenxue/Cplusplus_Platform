#include "MyThread.h"
#include "MyThreadPool.h"
#include <iostream>
using namespace std;
int MyThread::s_threadnumber = 0;
MyThread::MyThread(MyThreadPool *pool) :mythreadpool_(pool), isdetach_(true)
{
	s_threadnumber++;
	threadid_ = s_threadnumber;
}

void MyThread::setisdetach(bool detach)
{
	isdetach_ = detach;
}
void MyThread::Assign(Task *t)
{
	task_ =t;

}
void MyThread::Run()
{
	cout <<"Thread:"<< threadid_ << " run ";
	task_->Run();
	mythreadpool_->RemoveThreadFromBusy(this);
}

int MyThread::getthreadid()
{
	return threadid_;
}
void MyThread::StartThread()
{
//	将MyThread的Run方法与thread_相绑定，this表示类的Run方法的第一个隐含的参数
//		然后根据isdetach的值，判断是否detach() or join()
	thread_ = thread(&MyThread::Run, this);
	if (isdetach_ == true)
		thread_.detach();
	else
		thread_.join();
}

bool operator==(MyThread my1, MyThread my2)
{
	return my1.threadid_ == my2.threadid_;
}
bool operator!=(MyThread my1, MyThread my2)
{
	return !(my1.threadid_ == my2.threadid_);
}