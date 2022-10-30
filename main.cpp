#include "Logger.h"
using namespace myLogger::utility;

int main()
{

  Logger::instance()->open("./test.log");
  Logger::instance()->Logger::log(Logger::DEBUG, __FILE__, __LINE__, "Hello");
  Logger::instance()->Logger::log(Logger::DEBUG, __FILE__, __LINE__, "%s %d", "name", 18);

  debug("hello");
  info("hello");
  warn("hello");
  error("hello");
  fatal("hello");

  return 0;
}