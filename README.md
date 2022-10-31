# 简单 C++ 日志系统

## 功能

- 存储五个等级的日志信息为文本文件
- 设置记录的日志级别
- 日志翻滚
- 用法简洁

## 使用

**日志级别**

```cpp
enum Level
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
    LEVEL_COUNT
};
```

```c++
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
  debug("hello");
  info("%s%d","123",5);
  warn("hello");
  error("hello");
  fatal("hello");

  return 0;
}
```

## 问题

多线程存在安全隐患