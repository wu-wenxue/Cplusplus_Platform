#ifndef WXLOGGER_DEF_H
#define WXLOGGER_DEF_H

#include "wxlogger.h"


#define WXLOG_INFO(message) { \
    std::ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    wwxlog::Wxlogger::getInstance()->WxLog((wwxlog::LogLevel)0,oss);}

#define WXLOG_DEBUG(message) { \
    std::ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    wwxlog::Wxlogger::getInstance()->WxLog((wwxlog::LogLevel)1,oss);}

#define WXLOG_WARN(message) { \
    std::ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    wwxlog::Wxlogger::getInstance()->WxLog((wwxlog::LogLevel)2,oss);}

#define WXLOG_ERROR(message) { \
    std::ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    wwxlog::Wxlogger::getInstance()->WxLog((wwxlog::LogLevel)3,oss);}

#define WXLOG_FATAL(message) { \
    std::ostringstream oss; \
    oss << __FUNCTION__ << ", " << message;   \
    wwxlog::Wxlogger::getInstance()->WxLog((wwxlog::LogLevel)4,oss);}

#endif // WXLOGGER_DEF_H
