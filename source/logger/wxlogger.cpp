#include "wxlogger.h"
#include <fstream>"
#include <stdio.h>

#if defined(__unix__) || defined(unix)
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

Wxlogger::Wxlogger(string name)
{
    m_Name = name;
}

void Wxlogger::WxLog(loglevel level, ostringstream &oss)
{
    mut.lock();
    ofstream outfile;
    outfile.open(m_Name.c_str(),ios::out|ios::app|ios::ate);

    switch(level)
    {
    case INFO:
    {
        if(outfile.is_open())
        {
            outfile << "[INFO ] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    case WARN:
    {
        if(outfile.is_open())
        {
            outfile << "[WARN ] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    case ERR:
    {
        if(outfile.is_open())
        {
            outfile << "[ERROR] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    case FATAL:
    {
        if(outfile.is_open())
        {
            outfile << "[FATAL] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    }
    outfile.close();
    mut.unlock();

}

string Wxlogger::GetCurrentTime_()
{
    struct tm* ct;   //tm结构指针
    const time_t t = time(NULL);
    ct = localtime(&t);
    char temp[50] = {0};
    sprintf(temp,"%d-%d-%d %d:%d:%d" ,ct->tm_year + 1900,ct->tm_mon + 1,ct->tm_mday,ct->tm_hour,ct->tm_min,ct->tm_sec);

    return string(temp);
}

string Wxlogger::GetCurrentTime_byms()
{
    int ms = 0;

#if defined(__unix__) || defined(unix)
    struct timeval tv;
    gettimeofday(&tv,NULL);
    ms = tv.tv_usec/1000;
#endif

#ifdef _WIN32
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);

    ms = wtm.wMilliseconds;
#endif

    struct tm* stm;
    const time_t t = time(NULL);
    stm = localtime(&t);

    char time[50] = {0};
    sprintf(time,"%04d-%02d-%02d %02d:%02d:%02d.%03d",stm->tm_year+1900,stm->tm_mon+1,stm->tm_mday,stm->tm_hour,stm->tm_min,stm->tm_sec,ms);
    return string(time);
}

string Wxlogger::GetCurrentTime_byus()
{
    int us = 0;
#if defined(__unix__) || defined(unix)
    struct timeval tv;
    gettimeofday(&tv,NULL);
    us = tv.tv_usec;
#endif

#ifdef _WIN32
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);

    us = wtm.wMilliseconds*1000;
#endif

    struct tm* stm;
    const time_t t = time(NULL);
    stm = localtime(&t);

    char time[50] = {0};
    sprintf(time,"%04d-%02d-%02d %02d:%02d:%02d.%06d",stm->tm_year+1900,stm->tm_mon+1,stm->tm_mday,stm->tm_hour,stm->tm_min,stm->tm_sec,us);
    return string(time);
}
