#ifndef TEST_HPP
#define TEST_HPP
#include "logger/wxlogger.h"
#include "ping/ping.h"
#include "thread/thread_linux.h"
#include "thread/thread_windows.h"
#include "test_zlib.hpp"

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
#ifdef _WIN32
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
#endif

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
#ifdef _WIN32
    R r;
    CThread *t = NULL;
    t = new CThread(&r);
    t->Start();
    t->Join();
#endif
}




#include "IPC/socket/tcp_client.h"

void test_socket_client()
{
#ifdef WIN32
    TCPClient* client = new TCPClient("192.168.8.111",80);
    client->Connect();
    string str = "GET /FTP/SBox-3G_-LE_-20171101120000.tar.gz HTTP/1.1\nHost: 192.168.8.111:81\n  User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:56.0) Gecko/20100101 Firefox/56.0  \            Accept: */*  \
            Accept-Language: zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3  \
            Accept-Encoding: gzip, deflate  \
            Connection: keep-alive  \
            \
            \
            ";
    client->onSendMessage(str);
#endif
}



#include "json_test.hpp"

#include "test_zlib2.hpp"
#include "file_test.hpp"
#include "common/common.h"
#include "zip_test/test_zip.hpp"
#include "test_socket.hpp"
#include "test_thread.hpp"


void test2()
{
//    test_log();

//    test_ping();

//    test_thread_windows();

//    jsontest();

//    test_zlib();

//    test_main1();

//    test_file();

//    test_zip();

//    test_socket();

    test_thread();


}

#endif // TEST_HPP

