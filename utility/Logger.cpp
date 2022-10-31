#include <Logger.h>
#include <cstring>
#include <iostream>
#include <time.h>
#include <stdarg.h>
using namespace myLogger::utility;

Logger::Logger() : now_length(0), max_length(0), m_level(DEBUG) {}
Logger::~Logger() { close(); }

const char *Logger::s_level[LEVEL_COUNT] = {"[DEBUG]", "[INFO]", "[WARNING]", "[ERROR]", "[FATAL]"};

Logger *Logger::m_instance = nullptr;

Logger *Logger::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Logger();
    }
    return m_instance;
}

void Logger::open(const std::string &filename)
{
    m_fout.open(filename, std::ios::app);
    m_filename = filename;
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed" + filename);
    }
    m_fout.seekp(0, std::ios::end);
    now_length = m_fout.tellp();
}

void Logger::close()
{
    m_fout.close();
}

void Logger::log(Level level, const char *file, int line, char *format, ...)
{
    if (m_level > level)
        return;
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed " + m_filename);
    }

    time_t ticks = time(nullptr);
    struct tm *curTime = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof timestamp);
    strftime(timestamp, sizeof timestamp, "%Y-%m-%d %H:%M:%S", curTime);

    const char *fmt = "%s %s %s:%d ";
    //    格式化字符串
    int siz = snprintf(nullptr, 0, fmt, timestamp, s_level[level], file, line);
    if (siz > 0)
    {
        char *buffer = new char[siz + 1];
        snprintf(buffer, siz + 1, fmt, timestamp, s_level[level], file, line);
        buffer[siz] = 0;
        //      std::cout<<buffer<<std::endl;
        m_fout << buffer;
        now_length += siz;
        delete buffer;
    }
    //    可变参数格式化
    va_list arg_ptr;
    va_start(arg_ptr, format);
    siz = vsnprintf(nullptr, 0, format, arg_ptr);
    if (siz > 0)
    {
        char *content = new char[siz + 1];
        va_start(arg_ptr, format);
        vsnprintf(content, siz + 1, format, arg_ptr);
        va_end(arg_ptr);
        m_fout << content;
        now_length += siz;
        delete content;
    }
    m_fout << '\n';
    m_fout.flush();
    if (now_length >= max_length && max_length > 0)
    {
        rotate();
    }
}

void Logger::rotate()
{
    close();
    time_t ticks = time(nullptr);
    struct tm *ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), ".%Y-%m-%d_%H-%M-%S", ptm);
    std::string filename = m_filename + timestamp;
    std::cout << filename << std::endl;
    if (rename(m_filename.c_str(), filename.c_str()) != 0)
    {
        throw std::logic_error("rename log file failed: " + std::string(strerror(errno)));
    }
    open(m_filename);
}