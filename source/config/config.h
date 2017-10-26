#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config
{
public:
    static Config* getInstance();
    bool ReadConfig(const std::string& filename);
    bool AnalyseLine(const std::string & line, std::string & value);

protected:
    Config();

private:
    static Config* _instance;
};

#endif // CONFIG_H
