#ifndef COMMON_H
#define COMMON_H
#include <string>

void wxsleep(unsigned int n);

void wxsleep_ms(unsigned int n);

#define HOURS           1
#define MINUTES         2
#define SECONDS         3
#define MILLISECONDS    4
#define MICROSECONDS    5
#define NANOSECONDS     6

void thread_sleep(unsigned int n,char type = SECONDS);

// 去除字符串两边的空格
void trimString(std::string &str);

std::string int2string(int i);

int string2int(std::string str);

#endif // COMMON_H
