#include "wxtcp_client.h"
#include <thread>

WxTcpClient::WxTcpClient(const std::string server_ip,int port)
{
    m_si.server_ip = server_ip;
    m_si.port = port;
    m_running = false;
}

WxTcpClient::~WxTcpClient()
{

}

void WxTcpClient::init()
{
    sync_client = new TCPClient(m_si.server_ip,m_si.port);
    async_client = new TCPClient(m_si.server_ip,m_si.port);

    m_running = true;
    async_recv_thread = std::thread(recvAsync,this);


}

void WxTcpClient::setServerInfo(ServerInfo si)
{
    m_si.server_ip = si.server_ip;
    m_si.port = si.port;
}

int WxTcpClient::sendMessage_sync(const std::string& send,std::string& recv)
{
    sync_client->onSendMessage(send);
    recv.clear();
    sync_client->onRecvMessage(recv);
}

int WxTcpClient::sendMessage_async(const std::string& send)
{
    async_client->onSendMessage(send);
}

void WxTcpClient::registerNotify(Notify_Abstract* notify)
{
    m_notify = notify;
}


void WxTcpClient::recvAsync(void *arg)
{
    WxTcpClient *client = static_cast<WxTcpClient*>(arg);
    std::string recv_msg;
    while(client->m_running)
    {
        recv_msg.clear();
        client->async_client->onRecvMessage(recv_msg);
        client->m_notify->recvHandle(recv_msg);
    }
}


void WxTcpClient::closeClient()
{
    sync_client->close();
    m_running = false;
    async_recv_thread.join();
    async_client->close();


}
