#ifndef TEST_LOG_HPP
#define TEST_LOG_HPP

#include "logger/wxlogger.h"

int test_log()
{
    std::cout << "Hello World" << endl;
    Wxlogger *logger = Wxlogger::getInstance();
    std::cout << "Hello World" << endl;
//    logger.WxLog(INFO,"testlog : " << 123456);
    ostringstream os;
    os << "testlog : " << 123456;
//    logger->WxLog(INFO,os);

    WXLOG_INFO(logger,"testlog : " << 123456);

    WXLOG_WARN(logger,"testlog WARN : " << 121455);

    WXLOG_ERROR(logger,"testlog ERROR : " << 121575);

    WXLOG_FATAL(logger,"testlog FATAL : " << 125674);

    return 0;
}

#endif // TEST_LOG_HPP
