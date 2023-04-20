include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.16.3)

enable_testing()

# add_executable(lab2_test 
#                lab2_test.cpp ../2Laba/include/parent.h ../2Laba/src/parent.cpp
#                ../2Laba/include/string_to_vector.h ../2Laba/src/string_to_vector.cpp
#                )


# target_link_libraries(lab2_test PRIVATE GTest::GTest)
# target_include_directories(lab2_test PRIVATE ../2Laba/include)


# add_test(lab2_test lab2_test)

# add_executable(lab3_test lab3_test.cpp ../3Laba/include/laba3OS.h ../3Laba/src/laba3OS.cpp ../3Laba/include/utils.h)

# target_link_libraries(lab3_test PRIVATE GTest::GTest)
# target_include_directories(lab3_test PRIVATE ../3Laba/include)

# add_test(lab3_test lab3_test)

# find_package(Threads REQUIRED)
# set(CMAKE_THREAD_LIBS_INIT "-lpthread")
# add_executable(lab4_test lab4_test.cpp ../4Laba/include/parent.h ../4Laba/src/parent.cpp
#         ../4Laba/include/string_to_vector.h ../4Laba/src/string_to_vector.cpp)

# target_link_libraries(lab4_test PRIVATE GTest::GTest)
# target_include_directories(lab4_test PRIVATE ../4Laba/include)
# target_link_libraries(lab4_test PRIVATE rt)
# target_link_libraries(lab4_test PRIVATE Threads::Threads)

# add_test(lab4_test lab4_test)

add_executable(lab5_test lab5_test.cpp)

target_link_libraries(lab5_test PRIVATE GTest::GTest dl /usr/lib/d1.so)

add_test(lab5_test lab5_test)
