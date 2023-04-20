cmake_minimum_required(VERSION 3.16.3)

add_executable(lab2
        main.cpp
        include/parent.h src/parent.cpp)

target_include_directories(lab2 PRIVATE include)

add_executable(child
        src/child.cpp
        include/string_to_vector.h src/string_to_vector.cpp)

target_include_directories(child PRIVATE include)

add_dependencies(lab2 child)
