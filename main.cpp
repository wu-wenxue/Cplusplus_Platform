#include <iostream>

#include "test.hpp"
#include "logger/wxlogger.h"

using namespace std;

int main()
{
    Wxlogger* logger = Wxlogger::getInstance("test.log");

    test2();

    cout << "hello" << endl;
}
