#pragma once

#include <string>
#include <fstream>

namespace myLogger
{
    namespace utility
    {
#define debug(format, ...) \
    Logger::instance()->Logger::log(Logger::DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define info(format, ...) \
    Logger::instance()->Logger::log(Logger::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define warn(format, ...) \
    Logger::instance()->Logger::log(Logger::WARNING, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define error(format, ...) \
    Logger::instance()->Logger::log(Logger::ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define fatal(format, ...) \
    Logger::instance()->Logger::log(Logger::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__);

        class Logger
        {
        public:
            enum Level
            {
                DEBUG,
                INFO,
                WARNING,
                ERROR,
                FATAL,
                LEVEL_COUNT
            };
            void log(Level level, const char *file, int line, char *format, ...);
            static Logger *instance();

            void open(const std::string &filename);
            void close();
            void setLevel(Level level)
            {
                m_level = level;
            }
            void setMax(int length)
            {
                max_length = length;
            }

        private:
            Logger();
            ~Logger();
            void rotate();

        private:
            static Logger *m_instance;
            static const char *s_level[LEVEL_COUNT];
            std::string m_filename;
            std::ofstream m_fout;
            int max_length;
            int now_length;
            Level m_level;
        };
    }
}