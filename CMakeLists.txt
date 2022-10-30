cmake_minimum_required(VERSION 3.22)
project(SimpleLog4cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(utility)

add_executable(SimpleLog4cpp
        utility/Logger.cpp
        utility/Logger.h
        main.cpp)
