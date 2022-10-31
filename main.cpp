#include "Logger.h"
using namespace myLogger::utility;

int main()
{
  //  设置日志路径
  Logger::instance()->open("./test.log");
  //  设置最小级别过滤
  Logger::instance()->setLevel(Logger::INFO);
  //  设置文件大小 byte
  Logger::instance()->setMax(1024);
  //  输出日志
  Logger::instance()->Logger::log(Logger::INFO, __FILE__, __LINE__, "Hello");
  Logger::instance()->Logger::log(Logger::INFO, __FILE__, __LINE__, "%s %d", "name", 18);
  //  宏输出日志
  debug("hello");
  info("hello");
  warn("hello");
  error("hello");
  fatal("hello");

  return 0;
}