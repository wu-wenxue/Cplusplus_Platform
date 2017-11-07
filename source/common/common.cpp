#include "common.h"
#include <string>

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

#include <strstream>

std::string int2string(int i)
{
    std::string s;
    std::strstream ss;
    ss<<i;
    ss>>s;

    return s;
}

std::string int_to_string2(int i)
{
    char ch[10] = {0};
    sprintf(ch, "%d", i);
    std::string s(ch);

    return s;
}

int string2int(std::string str)
{
    int i = 0;
    std::strstream ss;
    ss << str;
    ss >> i;
    return i;
}
