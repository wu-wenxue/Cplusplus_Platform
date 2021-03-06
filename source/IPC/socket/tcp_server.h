#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef _WIN32
#include <WinSock2.h>  


#pragma comment(lib, "ws2_32.lib")  
namespace wwx
{
	class Server
	{
	public:
		Server(int port);
		~Server();

		void Init();

		void Bind();

		void Listen();

		void Accept();

		void onSendMessage(std::string message);

		void Close();

		SOCKET GetClientSocket();
	private:
		WSADATA wsaData;
		SOCKADDR_IN addrClient;
		SOCKADDR_IN addrSrv;
		SOCKET sockSrv;
		SOCKET sockConn;
		int m_port;
	};
}

#endif
