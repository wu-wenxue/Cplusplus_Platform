#include "time_manage.h"

#if defined(__unix__) || defined(unix)
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

TimeManage::TimeManage()
{

}

std::string TimeManage::GetCurrentDateString(std::string& str_date)
{
    struct tm *st;
    const time_t now = time(NULL);
    st = localtime(&now);

    char time[12] = {0};
    sprintf(time,"%04d-%02d-%02d",st->tm_year+1900,st->tm_mon + 1,st->tm_mday);
    return std::string(time);
}

std::string TimeManage::GetCurrentTimeString(std::string& str_time)
{
    struct tm *st;
    const time_t now = time(NULL);
    st = localtime(&now);

    char time[12] = {0};
    sprintf(time,"%04d-%02d-%02d %02d:%02d:%02d",st->tm_year+1900,st->tm_mon + 1,st->tm_mday,st->tm_hour,st->tm_min,st->tm_sec);
    return std::string(time);
}

std::string TimeManage::GetCurrentTimeString_byMs()
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
    return std::string(time);
}

long long TimeManage::GetSystemTicks_sec()
{
    using namespace std::chrono;
    typedef duration<int,std::ratio<1>> days_type;
    time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());
    return (long long)today.time_since_epoch().count();
}

long long TimeManage::GetSystemTicks_msec()
{
    typedef std::chrono::duration<long long,std::ratio<1,1000>> milliseconds;
//    std::chrono::time_point<std::chrono::system_clock,milliseconds>;
    auto time = std::chrono::time_point_cast<milliseconds>(std::chrono::system_clock::now());
    return (long long)time.time_since_epoch().count();

}
