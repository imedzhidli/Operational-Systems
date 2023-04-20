cmake_minimum_required(VERSION 3.16.3)

project(lab4 LANGUAGES CXX)

find_package(Threads REQUIRED)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
add_executable(lab4
        main.cpp
        include/parent.h src/parent.cpp
       )

target_link_libraries(lab4 PRIVATE rt)
target_link_libraries(lab4 PRIVATE Threads::Threads)
target_include_directories(lab4 PRIVATE include)

add_executable(child
        src/child.cpp
        include/string_to_vector.h src/string_to_vector.cpp
        )
target_link_libraries(child PRIVATE rt)
target_link_libraries(child PRIVATE Threads::Threads)
target_include_directories(child PRIVATE include)

add_dependencies(lab4 child)

