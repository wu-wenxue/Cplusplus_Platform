#include "common.h"

#if defined(__unix__) || defined(unix)
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif


void wxsleep(unsigned int n)
{
#if defined(__unix__) || defined(unix)
    sleep(n);
#endif

#ifdef _WIN32
    Sleep(n*1000);
#endif
}

void wxsleep_ms(unsigned int n)
{
#if defined(__unix__) || defined(unix)
    usleep(n*1000);
#endif

#ifdef _WIN32
    Sleep(n);
#endif
}


void trimString(std::string &str)
{
    int s = str.find_first_not_of(" ");
    int e = str.find_last_not_of(" ");
    str = str.substr(s,e-s+1);
}
