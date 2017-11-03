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
    WARN,
    ERR,
    FATAL,
}loglevel;


class Wxlogger
{
public:
    static Wxlogger* getInstance();

    ~Wxlogger();

    void WxLog(loglevel level, ostringstream& oss);

    void SetLogName(string path,string filename);
    void SetLogLevel(loglevel level);

protected:
    Wxlogger();

private:
    string GetCurrentTime_();
    string GetCurrentTime_byms();
    string GetCurrentTime_byus();
    string m_Name;
    string m_Path;
    loglevel m_level;
    mutex mut;

private:
    static Wxlogger* _instance;
};

#define WXLOG_INFO(logger,message) { \
    ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    logger->WxLog(INFO,oss);}

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
