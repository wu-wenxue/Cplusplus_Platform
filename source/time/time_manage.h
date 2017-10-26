#ifndef TIME_MANAGE_H
#define TIME_MANAGE_H

#include <string>
#include <chrono>
#include <ratio>

class TimeManage
{
public:
    TimeManage();

    std::string GetCurrentDateString(std::string& str_date);

    std::string GetCurrentTimeString(std::string& str_time);

    std::string GetCurrentTimeString_byMs();

    static long long GetSystemTicks_sec();

    static long long GetSystemTicks_msec();

};

#endif // TIME_MANAGE_H
