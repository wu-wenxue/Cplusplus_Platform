#ifndef TEST_HPP
#define TEST_HPP
#include "logger/wxlogger.h"
#include "ping/ping.h"
//#include "thread/thread_linux.h"
#include "thread/thread_windows.h"

int test_log()
{
    std::cout << "Hello World" << endl;
    Wxlogger *logger = Wxlogger::getInstance();
    std::cout << "Hello World" << endl;
//    logger.WxLog(INFO,"testlog : " << 123456);
    ostringstream os;
    os << "testlog : " << 123456;
//    logger->WxLog(INFO,os);

    WXLOG_INFO(logger,"testlog : " << 123456);

    WXLOG_WARN(logger,"testlog WARN : " << 121455);

    WXLOG_ERROR(logger,"testlog ERROR : " << 121575);

    WXLOG_FATAL(logger,"testlog FATAL : " << 125674);

    return 0;
}

int test_ping()
{
    Ping objPing;

    char *szDestIP = "192.168.8.1";
    PingReply reply;

    printf("Pinging %s with %d bytes of data:\n", szDestIP, DEF_PACKET_SIZE);
    for(int i=0;i< 5;i++)
    {
        objPing.DoPing(szDestIP, &reply);
        printf("Reply from %s: bytes=%d time=%ldms TTL=%ld\n", szDestIP, reply.m_dwBytes, reply.m_dwRoundTripTime, reply.m_dwTTL);
        Sleep(500);
    }

    return 0;
}

class R:public Runnable
{
public:
    ~R()
    {
        std::cout << "~R" << endl;
    }
    void Run()
    {
        std::cout << "Hello World" << endl;
    }
};

void test_thread_windows()
{
    R r;
    CThread *t = NULL;
    t = new CThread(&r);
    t->Start();
    t->Join();

}


void test2()
{
    test_log();
    std::cout << "Hello World" << endl;
    test_ping();

    test_thread_windows();
}

#endif // TEST_HPP

