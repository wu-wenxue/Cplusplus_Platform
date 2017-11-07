#include <iostream>

#include "test.hpp"
#include "logger/wxlogger.h"
#include "unit_test/http_test.hpp"
#include "common/common.h"

using namespace std;

int main()
{
    Wxlogger* logger = Wxlogger::getInstance();
    logger->SetLogName("./log/","test.log");
    logger->SetLogLevel(INFO);

    cout << "hello" << endl;
    test2();
//    http_test();

//    wxsleep(5);
    cout << "hello" << endl;
}
