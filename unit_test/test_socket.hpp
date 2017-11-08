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

#endif // TEST_SOCKET_HPP
