#include "platform.h"
#include "config/config.h"
#include "logger/wxlogger.h"

platform::platform()
{

}


bool platform_init()
{
    Config* config = Config::getInstance();
    config->ReadConfig("./conf/config.ini");

    Wxlogger *logger = Wxlogger::getInstance();
    logger->init();

    return true;
}
