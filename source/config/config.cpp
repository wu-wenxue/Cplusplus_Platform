#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "common/common.h"
#include <string.h>

#define COMMENT_CHAR '#'

Config* Config::_instance = NULL;

Config::Config()
{

}

Config* Config::getInstance()
{
    if(NULL == _instance)
    {
        _instance = new Config();
    }
    return _instance;
}


bool Config::AnalyseLine(const std::string & line, std::string & value)
{
    if (line.empty())
        return false;

    int start_pos = 0, end_pos = line.size() - 1, pos;
    if ((pos = line.find(COMMENT_CHAR)) != -1) {
        if (0 == pos) {  // 行的第一个字符就是注释字符
            return false;
        }
        end_pos = pos - 1;
    }
    std::string new_line = line.substr(start_pos, start_pos + 1 - end_pos);  // 预处理，删除注释部分

    if ((pos = new_line.find('=')) == -1)
        return false;  // 没有=号
    std::string key;
    key = new_line.substr(0, pos);
    value = new_line.substr(pos + 1, end_pos + 1- (pos + 1));

    trimString(key);
    trimString(value);


    if(key.compare("logLevel") == 0)
    {
        if(value.compare("info") == 0) logLevel = 0;
        if(value.compare("debug") == 0) logLevel = 1;
        if(value.compare("warn") == 0) logLevel = 2;
        if(value.compare("error") == 0) logLevel = 3;
        if(value.compare("fatal") == 0) logLevel = 4;
    }
    if(key.compare("logFilePath") == 0)
    {
        logFilePath = value;
    }
    if(key.compare("logFileName") == 0)
    {
        logFileName = value;
    }
    if(key.compare("logFileSize") == 0)
    {
        logFileSize = string2int(value);
    }
    if(key.compare("logFileBackCount") == 0)
    {
        logFileBackCount = string2int(value);
    }


}

// 读取数据
bool Config::ReadConfig(const std::string& filename)
{
    std::ifstream infile(filename);
    if(!infile)
    {
//        LOG4CXX_ERROR(logger,"config file open error");
        return false;
    }
//    LOG4CXX_INFO(logger,"config file open sucess!");
    std::string line,value;
    while(getline(infile,line))
    {
        AnalyseLine(line,  value);
    }
    infile.close();

    return true;
}


int Config::GetLogLevel()
{
    return logLevel;
}

std::string Config::GetLogFilePath()
{
    return logFilePath;
}

std::string Config::GetLogFileName()
{
    return logFileName;
}

int Config::GetLogFileSize()
{
    return logFileSize;
}

int Config::GetLogFileBackCount()
{
    return logFileBackCount;
}
