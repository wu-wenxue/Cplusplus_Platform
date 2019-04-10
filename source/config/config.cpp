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

    map_info[key] = value;
}

// 读取数据
bool Config::ReadConfig(const std::string& filename)
{
    std::ifstream infile(filename);
    if(!infile)
    {
        return false;
    }
    std::string line,value;
    while(getline(infile,line))
    {
        AnalyseLine(line,  value);
    }
    infile.close();

    return true;
}

int Config::GetParameterByKey(std::string key,std::string& value)
{
    value = map_info[key];
    return 0;
}

