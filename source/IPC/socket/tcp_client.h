#pragma once
#include <iostream>

#ifdef WIN32
#include <windows.h>
#include <WinSock2.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib") 



class TCPClient
{
public:
    TCPClient(std::string server_ip, int port);
    ~TCPClient();

    bool Init();

    bool Connect();

    void onSendMessage(std::string message);

    //	void StartRecvProcess(WebSocket_Client* ws_client);

    static void onRecvMessage(void* instance);

    int Recv(std::string& recv_message);
    void close();

    SOCKET GetSocket();

private:

    std::string m_server_ip;
    int m_port;

    WSADATA wsaData;
    SOCKADDR_IN addrSrv;
    SOCKET sockClient;


};

#endif

