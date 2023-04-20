cmake_minimum_required(VERSION 3.16.3)

project(lab5 LANGUAGES CXX)

# Добавляем библиотеку d1
add_library(d1 SHARED lib1.cpp)
set_target_properties(d1 PROPERTIES OUTPUT_NAME "d1")
set_target_properties(d1 PROPERTIES PREFIX "")
set_target_properties(d1 PROPERTIES SUFFIX ".so")

# Добавляем библиотеку d2
add_library(d2 SHARED lib2.cpp)
set_target_properties(d2 PROPERTIES OUTPUT_NAME "d2")
set_target_properties(d2 PROPERTIES PREFIX "")
set_target_properties(d2 PROPERTIES SUFFIX ".so")

# Добавляем исполняемый файл main1 и линкуем с библиотекой d1
add_executable(main1 first.cpp)
target_link_libraries(main1 d1)
target_link_options(main1 PRIVATE -Wl,-rpath=$ORIGIN)

# Добавляем исполняемый файл main2 и линкуем с библиотекой dl
add_executable(main2 second.cpp)
target_link_libraries(main2 dl)
# target_link_libraries(main2 dl)

