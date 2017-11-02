#include "tcp_linux.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

TCPClient::TCPClient(std::string server_ip,int port)
{
    m_serverIp = server_ip;
    m_port = port;
    Init();
}

TCPClient::~TCPClient()
{

}

bool TCPClient::Init()
{


    memset(&addrSrv,0,sizeof(addrSrv));
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(m_port);
    addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");

    sockClient = socket(AF_INET,SOCK_STREAM,0);
    if(0 == sockClient)
    {
        return false;
    }

    return true;
}

bool TCPClient::Connect()
{
    if (connect(sockClient, (struct sockaddr *)&addrSrv, sizeof(addrSrv)) < 0)
    {

        return false;
    }

    return true;
}

void TCPClient::onSendMessage(std::string message)
{
    std::cout << "send : " << message.c_str() << std::endl;
    send(sockClient, message.data(), message.length(), 0);
}


void TCPClient::onRecvMessage(void* instance)
{
    std::cout << "recv thread is start ...." << std::endl;
    TCPClient* client = static_cast<TCPClient*>(instance);
    char recv_buf[1024];
    while (1)
    {
        std::string message = "";
        while (1)
        {
            memset(recv_buf, 0, sizeof(recv_buf));
            int len = recv(client->GetSocket(), recv_buf, sizeof(recv_buf)-1, 0);
            recv_buf[len] = '\0';
            message += recv_buf;
            if (len < sizeof(recv_buf))
            {
                if (len == 0)
                {
                    std::cout << "connect is break....." << std::endl;
                    break;
                }
                break;
            }
        }

        std::cout << "socket recv : " << recv_buf << std::endl;
    }
}

int TCPClient::Recv(std::string& recv_message)
{
    char recv_buf[1024] = { 0 };
    int count = 0;
    while (1)
    {
        memset(recv_buf, 0, sizeof(recv_buf));
        int len = recv(sockClient, recv_buf, sizeof(recv_buf)-1, 0);
        recv_buf[len] = '\0';
        count += len;
        recv_message += recv_buf;
        if (len < (sizeof(recv_buf)-1))
            break;
    }
    return count;
}

void TCPClient::Close()
{

    close(sockClient);

}

int TCPClient::GetSocket()
{
    return sockClient;
}



TCPServer::TCPServer(int port)
{
    m_port = port;
    Init();
    Bind();
    Listen();
}

TCPServer::~TCPServer()
{

}

void TCPServer::Init()
{
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(m_port); //1024以上的端口号
    addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);

    //创建用于监听的套接字
    sockSrv = socket(AF_INET, SOCK_STREAM, 0);
}

void TCPServer::Bind()
{
    int retVal = bind(sockSrv, (sockaddr*)&addrSrv, sizeof(addrSrv));
    if (retVal == -1){
        printf("Failed bind:%d\n", -1);
        return;
    }
}

void TCPServer::Listen()
{
    if (listen(sockSrv, 10) == -1){
        printf("Listen failed:%d", -1);
        return;
    }
}

void TCPServer::Accept()
{
    sockaddr_in addrClient;
    int len = sizeof(sockaddr);
    char recv_buf[1024] = { 0 };
//	while (1)
//	{
        //等待客户请求到来
        sockConn = accept(sockSrv, (sockaddr *)&addrClient, (socklen_t*)&len);
        if (sockConn == -1){
            printf("Accept failed:%d", -1);
//			break;
        }
//		break;

        printf("Accept client IP:[%s]\n", inet_ntoa(addrClient.sin_addr));

/*
    while (1)
    {
        std::string str;
        std::cin >> str;
        onSendMessage(str);

        memset(recv_buf, 0, sizeof(recv_buf));
        //发送数据
        std::cin >> recv_buf;
        int iSend = send(sockConn, recv_buf, sizeof(recv_buf), 0);
        if (iSend == SOCKET_ERROR){
            printf("send failed");
            break;
        }


        char recvBuf[100];
        memset(recvBuf, 0, sizeof(recvBuf));
        //      //接收数据
        recv(sockConn, recvBuf, sizeof(recvBuf), 0);
        printf("%s\n", recvBuf);

//		closesocket(sockConn);
    }
    */

}

void TCPServer::onSendMessage(std::string message)
{
    int iSend = send(sockConn, message.c_str(), message.length(), 0);
}

void TCPServer::Close()
{
    close(sockSrv);

}

int TCPServer::getClientSocket()
{
    return sockConn;
}
