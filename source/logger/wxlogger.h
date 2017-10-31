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
    static Wxlogger* getInstance(string Name = NULL);
//    static void SetLogName(string path,string filename);

    ~Wxlogger();

    void WxLog(loglevel level, ostringstream& oss);

protected:
    Wxlogger(string name);
    string GetCurrentTime_();
    string GetCurrentTime_byms();
    string GetCurrentTime_byus();
    string m_Name;
    string m_Path;
    mutex mut;

private:
    static Wxlogger* _instance;
};

#define WXLOG_INFO(message) { \
    Wxlogger* logger = Wxlogger::getInstance(); \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(INFO,oss);}

#define WXLOG_WARN(message) { \
    Wxlogger* logger = Wxlogger::getInstance(); \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(WARN,oss);}

#define WXLOG_ERROR(message) { \
    Wxlogger* logger = Wxlogger::getInstance(); \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(ERR,oss);}

#define WXLOG_FATAL(message) { \
    Wxlogger* logger = Wxlogger::getInstance(); \
    ostringstream oss; \
    oss << message;   \
    logger->WxLog(FATAL,oss);}



#endif // WXLOGGER_H
