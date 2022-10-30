#include <Logger.h>
#include <cstring>
#include <time.h>
using namespace myLogger::utility;

Logger::Logger() {}
Logger::~Logger() {}

const char *Logger::s_level[LEVEL_COUNT] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};

Logger *Logger::m_instance = NULL;

Logger *Logger::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new Logger();
    }
    return m_instance;
}

void Logger::open(const std::string &filename)
{
    m_fout.open(filename, std::ios::app);
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed" + filename);
    }
}

void Logger::close()
{
    m_fout.close();
}

void Logger::log(Level level, const char *file, int line, char *format, ...)
{
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed " + m_filename);
    }
    time_t ticks = time(NULL);
    struct tm *curTime = localtime(&ticks);
    char buffer[32];
    memset(buffer, 0, sizeof buffer);
    strftime(buffer, sizeof buffer, "%Y-%m-%d %H:%M:%S", curTime);
}
