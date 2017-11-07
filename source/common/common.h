#ifndef COMMON_H
#define COMMON_H
#include <string>

void wxsleep(unsigned int n);

void wxsleep_ms(unsigned int n);

// 去除字符串两边的空格
void trimString(std::string &str);

std::string int2string(int i);

int string2int(std::string str);

#endif // COMMON_H
