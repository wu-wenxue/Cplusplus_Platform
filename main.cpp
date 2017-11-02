#include <iostream>

#include "test.hpp"
#include "logger/wxlogger.h"
#include "unit_test/http_test.hpp"

using namespace std;

int main()
{
    Wxlogger* logger = Wxlogger::getInstance();
    logger->SetLogName(".","test.log");
    logger->SetLogLevel(INFO);

    cout << "hello" << endl;
    test2();
    http_test();

    cout << "hello" << endl;
}
