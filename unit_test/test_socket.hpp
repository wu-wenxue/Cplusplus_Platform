#ifndef TEST_SOCKET_HPP
#define TEST_SOCKET_HPP

#include "IPC/socket/wxtcp_client.h"
#include "logger/wxlogger.h"
#include "common/common.h"

class MyHandle:public Notify_Abstract
{
public:
    virtual void recvHandle(std::string message)
    {
        Wxlogger* logger = Wxlogger::getInstance();
        WXLOG_WARN(logger,"async socket recv message : " << message);
    }
};

void test_socket1()
{
    WxTcpClient *client = new WxTcpClient("192.168.1.187",6000);
    client->init();
    MyHandle* handle = new MyHandle();
    client->registerNotify(handle);

    string recv_msg;
//    client->sendMessage_sync("hello",recv_msg);

    client->sendMessage_async("hello2");

    wxsleep(5);

    client->closeClient();

    wxsleep(5);
}

void test_socket()
{
    test_socket1();
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

#endif // TEST_SOCKET_HPP
