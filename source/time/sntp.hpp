#ifndef SNTP_HPP
#define SNTP_HPP

//SNTP协议，用于时间同步
//Download by http://www.NewXing.com
#pragma comment(lib,"ws2_32.lib")
#ifndef WIN32
#include <unistd.h>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <time.h>
//#include "common.h"

#ifdef WIN32

#include <winsock.h>
#define socklen_t unsigned long
#define close closesocket
#define tz 1
#define __PACKED_ALIGN__
#pragma pack(1)

BOOL EnableSetTimePriviledge()
{
  HANDLE hToken;
  TOKEN_PRIVILEGES tokenPriv;
  if( OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) == FALSE )
  {
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
      // Must be running on 95 or 98 not NT. In that case just ignore the error
      SetLastError(ERROR_SUCCESS);
      return TRUE;
    }
    printf("Failed to get Adjust priviledge token\n");
    return FALSE;
  }
  memset(&tokenPriv, 0, sizeof(TOKEN_PRIVILEGES));
  if (!LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &tokenPriv.Privileges[0].Luid))
  {
    printf("Failed in callup to lookup priviledge\n");
    return FALSE;
  }
  tokenPriv.PrivilegeCount = 1;
  tokenPriv.Privileges[0].Attributes |= SE_PRIVILEGE_ENABLED;

  if( AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, 0, NULL, 0) == FALSE )
  {
    printf("Failed to adjust SetTime priviledge\n");
    return FALSE;
  } else {
    printf("Set Privileges OK\r\n");
    return TRUE;
  }
}

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#define WM_USER 0
#define WINAPI
#define __PACKED_ALIGN__    __attribute__((packed))

#endif
int g_bRunning;
#define SNTP_DBG
#define MSG_SNTP_QUIT                   (WM_USER+100) /* 退出SNTP 线程 */
#define MSG_SNTP_SERVER                 (WM_USER+101) /* 设置SNTP 服务器地址*/
#define MSG_SNTP_MODE                   (WM_USER+102) /* 设置SNTP 模式 */

typedef struct NTP_TIME_FMT
{
    time_t seconds;
    time_t fractional;
} __PACKED_ALIGN__ NTP_TIME_FMT;

typedef struct NTP_PKT_BASE
{
  unsigned char liVnMode; /* LeapSecond(2bits:0), VersionNumber(3bits: 3), Mode(3bits: Client=3, Server=4) */
  unsigned char stratum; /* 时间层级 （0-15） */
  unsigned char poll; /* 表示连续信息间的最大间隔，8 bits，以2的x次幂秒的形式表示。实际填0即可 */
  unsigned char precision; /* 时间精度，以2的负x次幂秒表示，8 bits。服务器返回时会填写实际精度 */
  unsigned long rootDelay; /* 到主参考时间源的往返总延迟。32 bits固定小数点数，小数点在bit 15和bit 16之间 */
  unsigned long rootDispersion; /* 相对于主参考时间源的正常离差。32 bits固定小数点数，小数点在bit 15和bit 16之间 */
  char referenceID[4]; /* 用于识别特殊的参考源 */
  NTP_TIME_FMT referenceTimestamp; /* 本地时中最后一次设置或修正时的时间，64bits，timestamp格式 */
  NTP_TIME_FMT originateTimestamp; /* 客户端发送请求的时间 */
  NTP_TIME_FMT receiveTimestamp; /* 服务器接收到请求的时间 */
  NTP_TIME_FMT transmitTimestamp; /* 服务器发送响应的时间 */
} __PACKED_ALIGN__ NTP_PKT_BASE;

//The optional part of an NTP packet
typedef struct NTP_PKT_AUTHINFO
{
  unsigned long keyID;
  unsigned char messageDigest[128];
} __PACKED_ALIGN__ NTP_PKT_AUTHINFO;

//The Full NTP packet
typedef struct NTP_PKT
{
  NTP_PKT_BASE basic;
  NTP_PKT_AUTHINFO auth; /* 可选项。一般不填 */
} __PACKED_ALIGN__ NTP_PKT;


#ifdef WIN32
#pragma pack()
#endif
#undef __PACKED_ALIGN__

#define SECONDS_FROM_1900_1970 (86400U*(365U*70U+17U)) /* 1900-1-1 00:00:00 到1970-1-1 00:00:00 经过的秒数 */

#ifdef WIN32
DWORD WINAPI
#else
void*
#endif
 SntpService(void* pParam)
{
    fd_set r;
    struct timeval tv;
    NTP_TIME_FMT ct, lastTime = { 0 };
    NTP_PKT pkt;
    char tmpBuf[256], ntpServer[80+1];

    char ntpMode, bServer = 0, bClient = 1;
    struct sockaddr_in addr, addrReceive;
    int ret, sock = socket(PF_INET, SOCK_DGRAM, 0);
    socklen_t addrlen;

    if(sock==-1) {
        printf("SntpService: create sock failed.(%s)\r\n", strerror(errno));
        return NULL;
    }

    addr.sin_family = PF_INET;
    addr.sin_port = htons(123);
    addr.sin_addr.s_addr = 0;
    if(bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr))==-1) {
        printf("Bind socket on port %d fail\r\n", 123);
        close(sock);
        return NULL;
    }

    memset(ntpServer, 0, sizeof(ntpServer));
    if(pParam) {
        strncpy(ntpServer, (char*)pParam, sizeof(ntpServer)-1);
        if(ntpServer[0]) bClient = 1;
    }

#ifdef SNTP_DBG
    printf("SntpService starting, mode = %d ...\r\n", bServer | (bClient<<1));
#endif


    addr.sin_addr.s_addr = 0;
    while(1) {

#ifdef WIN32
        MSG msg;
        while (PeekMessage(&msg, NULL,  0, 0, PM_REMOVE)) {
            switch(msg.message){
            case MSG_SNTP_QUIT:
                {
                    //
                }
                break;
            case MSG_SNTP_MODE:
                {
                    //
                }
                break;
            case MSG_SNTP_SERVER:
                {
                    //
                }
                break;
            }
        }

#else
        int tz = GetTimeZone();
        if(MessageGet(MSG_SNTP_QUIT, NULL, 0, 0)>=0) break;

        if(MessageGet(MSG_SNTP_MODE, &ntpMode, 1, 0)==1) {
            bServer = ntpMode & 0x01;
            bClient = ntpMode & 0x02;
            lastTime.seconds = 0;
            printf("SNTP service mode = %d ...\r\n", bServer | (bClient<<1));
        }

        memset(tmpBuf, 0, sizeof(tmpBuf));
        if(MessageGet(MSG_SNTP_SERVER, tmpBuf, sizeof(tmpBuf)-1, 0)>=0) {
            memset(ntpServer, 0, sizeof(ntpServer));
            strncpy(ntpServer, tmpBuf, sizeof(ntpServer)-1);
            if(ntpServer[0]=='\0') bClient = 0;
            addr.sin_addr.s_addr = 0;
            lastTime.seconds = 0;
            printf("SNTP server = %s ...\r\n", ntpServer);
        }
#endif
        if(bClient) {
            /* send request every minute */
            ct.seconds = time(NULL);
            if(ct.seconds<lastTime.seconds || (ct.seconds-lastTime.seconds)>=60) {
                if(addr.sin_addr.s_addr==0) {
                    if(ntpServer[0]) {
                        struct hostent* pHost = gethostbyname(ntpServer);
                        if(pHost) addr.sin_addr.s_addr = ((struct in_addr*)pHost->h_addr_list[0])->s_addr;
                    }
                }
                if(addr.sin_addr.s_addr) {
                    lastTime.seconds = ct.seconds;
                    memset(&pkt, 0, sizeof(pkt));
                    pkt.basic.liVnMode=0x1b;
                    pkt.basic.transmitTimestamp.seconds = htonl(ct.seconds+SECONDS_FROM_1900_1970-tz*3600);
                    pkt.basic.transmitTimestamp.fractional = 0;
#ifdef SNTP_DBG
                    printf("NTP-CLIENT sending %d bytes on socket %d to port %d ...\r\n", sizeof(pkt.basic), sock, ntohs(addr.sin_port));
#endif
                    sendto(sock, (char*)&pkt.basic, sizeof(pkt.basic), 0, (struct sockaddr*)&addr, sizeof(struct sockaddr));
                }
            }
        }

        FD_ZERO(&r);
        FD_SET(sock, &r);
        tv.tv_sec = tv.tv_usec = 1;
        ret = select(sock+1, &r, NULL, NULL, &tv);
        if(ret<0) break;
        if(ret==0) continue;
        addrlen = sizeof(struct sockaddr);
        memset(&pkt, 0, sizeof(pkt));
        ret = recvfrom(sock, (char*)&pkt, sizeof(pkt), 0, (struct sockaddr*)&addrReceive, &addrlen);
        if(ret<=0) break;

        ct.seconds = time(NULL);
        ct.fractional = 0;
        if(pkt.basic.receiveTimestamp.seconds==0) {
            if(bServer) {
                /* response to client */
                NTP_TIME_FMT orgTime;

                orgTime.seconds=pkt.basic.transmitTimestamp.seconds;
                orgTime.fractional=pkt.basic.transmitTimestamp.fractional;

                memset(&pkt, 0, sizeof(pkt));
                pkt.basic.liVnMode = 0x1C;
                pkt.basic.stratum=10;
                memcpy(pkt.basic.referenceID, "WMR", 4);
                pkt.basic.referenceTimestamp.seconds = htonl(ct.seconds+SECONDS_FROM_1900_1970-tz*3600);
                pkt.basic.referenceTimestamp.fractional = htonl(ct.fractional);
                pkt.basic.originateTimestamp.seconds = orgTime.seconds;
                pkt.basic.originateTimestamp.fractional = orgTime.fractional;
                pkt.basic.transmitTimestamp.seconds = pkt.basic.receiveTimestamp.seconds = pkt.basic.referenceTimestamp.seconds;
                pkt.basic.transmitTimestamp.fractional = pkt.basic.receiveTimestamp.fractional = pkt.basic.referenceTimestamp.fractional;
#ifdef SNTP_DBG
                printf("NTP-SERVER response %d bytes ...\r\n", ret);
#endif
                ret = sendto(sock, (char*)&pkt, ret, 0, (struct sockaddr*)&addrReceive, addrlen);
            }
        } else {
            if(bClient) {
                /* read time info */
                int trip;
                struct tm* ptm;
#ifdef SNTP_DBG
                printf("LiVnMode = %d\r\n", (unsigned char)pkt.basic.liVnMode);
                printf("Stratum = %d\r\n", (unsigned char)pkt.basic.stratum);
                printf("poll = %d\r\n", (unsigned char)pkt.basic.poll);
                printf("precision = %d\r\n", (unsigned char)pkt.basic.precision);
                pkt.basic.rootDelay = ntohl(pkt.basic.rootDelay);
                printf("RootDelay = %lu\r\n", pkt.basic.rootDelay);
                pkt.basic.rootDispersion = ntohl(pkt.basic.rootDispersion);
                printf("RootDispersion = %lu\r\n", pkt.basic.rootDispersion);
                printf("RefrenceID = %02X %02X %02X %02X\r\n", pkt.basic.referenceID[0], pkt.basic.referenceID[1], pkt.basic.referenceID[2], pkt.basic.referenceID[3]);
#endif
                pkt.basic.referenceTimestamp.seconds = ntohl(pkt.basic.referenceTimestamp.seconds)-SECONDS_FROM_1900_1970+tz*3600;
                pkt.basic.referenceTimestamp.fractional = ntohl(pkt.basic.referenceTimestamp.fractional);
#ifdef SNTP_DBG
                ptm = gmtime(&pkt.basic.referenceTimestamp.seconds);
                if(ptm) printf("ReferenceTime = %d-%02d-%02d %02d:%02d:%02d\r\n", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
#endif
                pkt.basic.originateTimestamp.seconds = ntohl(pkt.basic.originateTimestamp.seconds)-SECONDS_FROM_1900_1970+tz*3600;
                pkt.basic.originateTimestamp.fractional = ntohl(pkt.basic.originateTimestamp.fractional);
#ifdef SNTP_DBG
                ptm = gmtime(&pkt.basic.originateTimestamp.seconds);
                if(ptm) printf("OriginateTime = %d-%02d-%02d %02d:%02d:%02d\r\n", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
#endif
                pkt.basic.receiveTimestamp.seconds = ntohl(pkt.basic.receiveTimestamp.seconds)-SECONDS_FROM_1900_1970+tz*3600;
                pkt.basic.receiveTimestamp.fractional = ntohl(pkt.basic.receiveTimestamp.fractional);
#ifdef SNTP_DBG
                ptm = gmtime(&pkt.basic.receiveTimestamp.seconds);
                if(ptm) printf("ReceiveTime = %d-%02d-%02d %02d:%02d:%02d\r\n", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
#endif
                pkt.basic.transmitTimestamp.seconds = ntohl(pkt.basic.transmitTimestamp.seconds)-SECONDS_FROM_1900_1970+tz*3600;
                pkt.basic.transmitTimestamp.fractional = ntohl(pkt.basic.transmitTimestamp.fractional);
#ifdef SNTP_DBG
                ptm = gmtime(&pkt.basic.transmitTimestamp.seconds);
                if(ptm) printf("transmitTime = %d-%02d-%02d %02d:%02d:%02d (%d s)\r\n", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, (int)pkt.basic.transmitTimestamp.seconds);
                printf("\r\n");
#endif
                trip = (ct.seconds - pkt.basic.originateTimestamp.seconds) - ( pkt.basic.transmitTimestamp.seconds - pkt.basic.receiveTimestamp.seconds);
#ifdef SNTP_DBG
                printf("RoundTripDelay = %d\r\n", trip);
#endif
                ct.seconds = pkt.basic.transmitTimestamp.seconds+trip/2;
                ct.fractional = pkt.basic.transmitTimestamp.fractional;
                ptm = gmtime(&ct.seconds);
                if(ptm) {
#ifdef WIN32
                    SYSTEMTIME st;
                    memset(&st,0, sizeof(st));
                    st.wYear = ptm->tm_year+1900;
                    st.wMonth = ptm->tm_mon+1;
                    st.wDay = ptm->tm_mday;
                    st.wHour = ptm->tm_hour;
                    st.wMinute = ptm->tm_min;
                    st.wSecond = ptm->tm_sec;
                    EnableSetTimePriviledge();
                    ret = (SetSystemTime(&st)==FALSE);
#else
                    ret=SetRealTime(tz, ptm->tm_year-100, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
#endif
                    if(ret) printf("SNTP: set system time fail\r\n");
                    else printf("SNTP: Synchronize system time to %d-%02d-%02d %02d:%02d:%02d\r\n", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
                }
            }
        }
    }

    if(sock != -1) close(sock);

    return NULL;
}

#ifdef WIN32

int main(int argc, char* argv[])
{
    HANDLE hNtpServer=NULL, hNtpClient=NULL;
    DWORD dwNtpServerId, dwNtpClientId;
    char* pServer = "210.72.145.44";

    WSADATA wsaData;
    WSAStartup(0x0101, &wsaData);

    if(argc>1) pServer = argv[1];

    g_bRunning = 1;
    hNtpClient = CreateThread(NULL, 0, SntpService, pServer, 0, &dwNtpClientId);
    if(hNtpClient) {
        time_t ct = time(NULL), lastTime=ct;
        while(ct-lastTime<65) {
            Sleep(1000);
            ct++;
        }
        g_bRunning = 0;
        Sleep(1000);
    }
    if(hNtpServer) CloseHandle(hNtpServer);
    if(hNtpClient) CloseHandle(hNtpClient);

    WSACleanup();
    return 0;
}

#endif

#endif // SNTP_HPP

