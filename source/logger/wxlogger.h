#ifndef WXLOGGER_H
#define WXLOGGER_H

#include <string>
#include <time.h>
#include <mutex>
#include <sstream>
#include <strstream>


using namespace std;

typedef enum LogLevel
{
    INFO = 0,
    DEBUG,
    WARN,
    ERR,
    FATAL,
}loglevel;


class Wxlogger
{
public:
    static Wxlogger* getInstance();

    ~Wxlogger();

    void init();

    void WxLog(loglevel level, ostringstream& oss);

    void SetLogName(const string path,const string filename);
    void SetLogLevel(loglevel level);
    void SetLogFileSize(const int size);
    void SetLogSaveCount(const int n);
    int getLogFileSize();

protected:
    Wxlogger();
    void BackLogFile();
private:
    string GetCurrentTime_();
    string GetCurrentTime_byms();
    string GetCurrentTime_byus();
    string m_Name;
    string m_Path;
    loglevel m_level;
    mutex mut;
    int m_logFileSize;
    int m_logSaveCount;

private:
    static Wxlogger* _instance;
};

#define WXLOG_INFO(logger,message) { \
    ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    logger->WxLog(INFO,oss);}

#define WXLOG_DEBUG(logger,message) { \
    ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    logger->WxLog(DEBUG,oss);}

#define WXLOG_WARN(logger,message) { \
    ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    logger->WxLog(WARN,oss);}

#define WXLOG_ERROR(logger,message) { \
    ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    logger->WxLog(ERR,oss);}

#define WXLOG_FATAL(logger,message) { \
    ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    logger->WxLog(FATAL,oss);}



#endif // WXLOGGER_H
