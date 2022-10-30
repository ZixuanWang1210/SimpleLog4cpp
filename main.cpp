#include <iostream>
#include "Logger.h"
using namespace myLogger::utility;

int main()
{
    Logger::instance()->open("./test.log");
    Logger::instance()->Logger::log(Logger::DEBUG, __FILE__, __LINE__, "Hello");
    return 0;
}