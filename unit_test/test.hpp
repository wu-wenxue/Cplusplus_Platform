#ifndef TEST_HPP
#define TEST_HPP
#include "logger/wxlogger.h"

int test_log()
{
    Wxlogger *logger = new Wxlogger("test.log");

//    logger.WxLog(INFO,"testlog : " << 123456);
    ostringstream os;
    os << "testlog : " << 123456;
    logger->WxLog(INFO,os);

    WXLOG_INFO(logger,"testlog : " << 123456);

    WXLOG_WARN(logger,"testlog WARN : " << 121455);

    WXLOG_ERROR(logger,"testlog ERROR : " << 121575);

    WXLOG_FATAL(logger,"testlog FATAL : " << 125674);


}


void test2()
{
    test_log();
}

#endif // TEST_HPP

