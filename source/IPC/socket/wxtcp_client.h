#ifndef WXTCP_CLIENT_H
#define WXTCP_CLIENT_H

#include <string>
#include "tcp_client.h"
#include <thread>

class Notify_Abstract
{
public:
    virtual void recvHandle(std::string message) = 0;
};

struct ServerInfo
{
    std::string server_ip;
    int port;
};

class WxTcpClient
{
public:
    WxTcpClient(const std::string server_ip, int port);
    ~WxTcpClient();

    void init();

    void setServerInfo(ServerInfo si);
    void getServerInfo(ServerInfo& si);

    int sendMessage_sync(const std::string& send,std::string& recv);

    int sendMessage_async(const std::string& send);

    void registerNotify(Notify_Abstract* notify);

    static void recvAsync(void* arg);

    void closeClient();


private:
    TCPClient* sync_client;
    TCPClient* async_client;

    ServerInfo m_si;
    Notify_Abstract* m_notify;
    std::thread async_recv_thread;
    bool m_running;
};

#endif // WXTCP_CLIENT_H
