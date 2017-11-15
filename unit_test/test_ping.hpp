#ifndef TEST_PING_HPP
#define TEST_PING_HPP

#include "ping/ping.h"

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


#endif // TEST_PING_HPP
