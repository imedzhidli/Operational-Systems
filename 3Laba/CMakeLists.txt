cmake_minimum_required(VERSION 3.16.3)

project(lab3 LANGUAGES CXX)

find_package(Threads REQUIRED)

add_executable(lab3
        main.cpp
        include/laba3OS.h src/laba3OS.cpp)

target_include_directories(lab3 PRIVATE include)


target_link_libraries(lab3 PRIVATE Threads::Threads)
