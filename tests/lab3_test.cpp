#include <gtest/gtest.h>

#include "laba3OS.h"
#include "utils.h"

#include <chrono>

namespace {
    TMatrix GenerateMatrix(int n, int m) {
        TMatrix result(n, vector<int>(m));

        srand(time(nullptr));

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                result[i][j] = rand() % 100;
            }
        }

        return result;
    }
}

bool operator==(const TMatrix& lhs, const TMatrix& rhs) {
    if(lhs.size() != rhs.size()) {
        return false;
    }

    for(int i = 0; i < Isize(lhs); ++i) {
        if(lhs[i].size() != rhs[i].size()) {
            return false;
        }

        for(int j = 0; j < Isize(lhs); ++j) {
            if(lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }

    return true;
}

TEST(Lab3Test, MedianTest) {
    
    int expectedres = 3;
    int expectedres2 = 2;

    vector <int> beforefunc = {0, 0, 1, 20, 34, 3, 50};
    vector <int> beforefunc2 = {0, 2, 1, 3};

    int res = median(beforefunc);
    int res2 = median(beforefunc2);
    EXPECT_EQ(expectedres, res);
    EXPECT_EQ(expectedres2, res2);

}

TEST(Lab3Test, FirstTest) {
    srand(time(NULL));
    auto getAvgTime = [](int thread_count) {
    int n = 3; int m = 3;
    int window_size = 3;
    // int thread_count = 2;
    int k = 2;
    TMatrix expectedMatrix{
        {1, 1, 2},
        {1, 1, 2},
        {1, 1, 3}
    };
    TMatrix mat1 = {
        {1, 2, 3},
        {1, 1, 0},
        {1, 4, 5}
    };
    TMatrix mat2(n, vector<int>(m));
    TMatrix res;

    double avg = 0;

    auto begin = chrono::high_resolution_clock::now();
    First(n, m, mat1, mat2, k, window_size, thread_count, res);
    EXPECT_EQ(res, expectedMatrix);
    auto end = chrono::high_resolution_clock::now();
    avg += chrono::duration_cast<chrono::milliseconds>(end - begin).count();


        return avg / 10;
    };
    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(3);

    cout << "Avg time for 1 thread: " << singleThread << '\n';
    cout << "Avg time for 3 threads: " << multiThread << '\n';
    
    EXPECT_LE(singleThread, multiThread);
}