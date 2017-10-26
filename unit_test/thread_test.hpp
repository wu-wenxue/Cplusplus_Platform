#ifndef THREAD_TEST_HPP
#define THREAD_TEST_HPP

#include "thread/thread_linux.h"
#include "logger/wxlogger.h"

class T : public Runnable
{
public:
    T(){d = 0;}
    virtual ~T(){d = 0;}
    void *Run(void* arg);

private:
    T(const T& t);
    T& operator=(const T& t);
    int d;
};

void* T::Run(void *arg)
{
    do
    {
        ++d;
    }while(d < 1000);
    std::cout << d << std::endl;

}

int test()
{
    T t;
    CThread *thread = new CThread();
    thread->Start(&t,NULL);
    std::cout << "OK" << std::endl;
    thread->Stop();
    sleep(1);

    T t2;
    thread->Start(&t2,NULL);
    thread->Stop();
    sleep(1);

    return 0;
}

#endif // THREAD_TEST_HPP

