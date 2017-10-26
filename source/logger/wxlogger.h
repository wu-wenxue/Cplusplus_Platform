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
    ERROR,
    FATAL,
}loglevel;


class Wxlogger
{
public:
    Wxlogger(string name);
    ~Wxlogger();

    void WxLog(loglevel level, ostringstream& oss);

protected:
    string GetCurrentTime();
    string GetCurrentTime_byms();
    string GetCurrentTime_byus();
    string m_Name;
    string m_Path;
    mutex mut;


};

#define WXLOG_INFO(logger,message) { \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(INFO,oss);}

#define WXLOG_WARN(logger,message) { \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(WARN,oss);}

#define WXLOG_ERROR(logger,message) { \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(ERROR,oss);}

#define WXLOG_FATAL(logger,message) { \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(FATAL,oss);}



#endif // WXLOGGER_H
