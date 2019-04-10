#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config
{
public:
    static Config* getInstance();
    bool ReadConfig(const std::string& filename);
    bool AnalyseLine(const std::string & line, std::string & value);

    int GetParameterByKey(std::string key,std::string& value);

protected:
    Config();

private:
    static Config* _instance;

    std::map<std::string,std::string> map_info;

};

#endif // CONFIG_H
