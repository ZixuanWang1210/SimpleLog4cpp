#pragma once

#include <string>
#include <fstream>

namespace myLogger
{
    namespace utility
    {
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

        private:
            Logger();
            ~Logger();
            static Logger *m_instance;

        private:
            static const char *s_level[LEVEL_COUNT];
            std::string m_filename;
            std::ofstream m_fout;
        };
    }
}