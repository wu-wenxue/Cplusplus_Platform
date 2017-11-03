#ifndef TCP_LINUX_H
#define TCP_LINUX_H

#if defined(__unix__) || defined(unix)
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <sys/shm.h>
#include <pthread.h>


class TCPClient
{
public:

    TCPClient(std::string server_ip,int port);
    ~TCPClient();

    bool Init();

    bool Connect();

    void onSendMessage(std::string message);

    static void onRecvMessage(void* instance);

    int Recv(std::string& recv_msg);

    void Close();

    int GetSocket();

private:
    std::string m_serverIp;
    int m_port;

    int sockClient;
    sockaddr_in addrSrv;

};



class TCPServer
{
public:
    TCPServer(int port);
    ~TCPServer();

    void Init();
    void Bind();
    void Listen();
    void Accept();
    void onSendMessage(std::string message);
    void Close();

    int getClientSocket();

private:
    sockaddr_in addrCli;
    sockaddr_in addrSrv;
    int sockSrv;
    int sockConn;
    int m_port;
};

#endif
#endif // TCP_LINUX_H
