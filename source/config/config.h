#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config
{
public:
    static Config* getInstance();
    bool ReadConfig(const std::string& filename);
    bool AnalyseLine(const std::string & line, std::string & value);

    int GetLogLevel();
    std::string GetLogFilePath();
    std::string GetLogFileName();
    int GetLogFileSize();
    int GetLogFileBackupCount();

protected:
    Config();

private:
    static Config* _instance;

   int logLevel;
   std::string logFilePath;
   std::string logFileName;
   int logFileSize;
   int logFileBackupCount;
};

#endif // CONFIG_H
