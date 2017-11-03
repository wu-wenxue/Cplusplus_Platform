#ifndef EPOLL_SERVER_H
#define EPOLL_SERVER_H

#if defined(__unix__) || defined(unix)

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class EpollServer
{
public:
    EpollServer();
    virtual ~EpollServer();
    bool init(int port,int sock_count);
    bool init(const char* ip,int port, int sock_count);
    int epoll_server_wait(int timeout);
    int accept_new_client();
    int recv_data(int sock,char* recv_buf);
    int send_data(int sock,char* send_buf,int buf_len);
    void run(int timeout);

private:
    int m_listen_sock;
    int m_epoll_fd;
    int m_max_count;

    struct epoll_event* m_epoll_events;
};

#endif
#endif // EPOLL_SERVER_H
