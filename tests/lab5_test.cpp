#include <cstdlib>
#include <iostream>
#include <dlfcn.h>
#include <gtest/gtest.h>

TEST(Lab5Test, d1){
    float (*Square)(float A, float B); /*указатель на функцию*/
    char* (*translation)(long x);

    void* library_handle = dlopen("/usr/lib/d1.so", RTLD_LAZY);
    ASSERT_NE(library_handle, nullptr);
    Square = (float(*)(float, float))dlsym(library_handle, "Square"); /*передаем функцию из либы с помощью dlsym() - 
                                                                    получить адрес функции в динамической библиотеке по её имени*/
    translation = (char*(*)(long x))dlsym(library_handle, "translation");
    float A = 3, B = 5;
    float expected = 15;
    float result = Square(A, B);
    EXPECT_EQ(expected, result);
    long number = 5;
    char *resnum = translation(number);

    int sum = atoi(resnum);

    int expectednum = 101;
    EXPECT_EQ(sum, expectednum);
    dlclose(library_handle);
}

TEST(Lab5Test, d2){
    float (*Square)(float A, float B); /*указатель на функцию*/
    char* (*translation)(long x);

    void* library_handle = dlopen("/usr/lib/d2.so", RTLD_LAZY);
    ASSERT_NE(library_handle, nullptr);
    Square = (float(*)(float, float))dlsym(library_handle, "Square"); /*передаем функцию из либы с помощью dlsym() - 
                                                                    получить адрес функции в динамической библиотеке по её имени*/
    translation = (char*(*)(long x))dlsym(library_handle, "translation");
    float A = 3, B = 5;
    float expected = 7.5;
    float result = Square(A, B);
    EXPECT_EQ(expected, result);
    long number = 5;
    char *resnum = translation(number);

    int sum = atoi(resnum);

    int expectednum = 12;
    EXPECT_EQ(sum, expectednum);
    dlclose(library_handle);
}

extern "C" float Square(float A, float B);
extern "C" char* translation(long x);

TEST(Lab5Test, d1link){
    float A = 3, B = 5;
    float expected = 15;
    float result = Square(A, B);
    EXPECT_EQ(expected, result);
    long number = 5;
    char *resnum = translation(number);

    int sum = atoi(resnum);

    int expectednum = 101;
    EXPECT_EQ(sum, expectednum);

}

// TEST(Lab5Test, d2link){
//     float A = 3, B = 5;
//     float expected = 7.5;
//     float result = Square(A, B);
//     EXPECT_EQ(expected, result);
//     long number = 5;
//     char *resnum = translation(number);

//     int sum = atoi(resnum);

//     int expectednum = 12;
//     EXPECT_EQ(sum, expectednum);

// }
