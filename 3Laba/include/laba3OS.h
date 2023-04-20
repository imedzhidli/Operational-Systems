#ifndef OS_LABS_LAB3_H
#define OS_LABS_LAB3_H

#include <vector>
#include <iostream>
#include <string>
#include <pthread.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
using namespace std;

using TMatrix = vector<vector<int>>;

struct thread_args{
	int height;
	int width;
	TMatrix *first_matrix;
	TMatrix *second_matrix;
	int area; 
	int lower_row;
	int upper_row;
};

void ReadMatrix(TMatrix &matrix);

void WriteMatrix(TMatrix &matrix);

int median(vector <int> &matrix);

void median_filter(int &height, int &width, TMatrix &a, TMatrix &b, int &area, int &lower_row, int &upper_row);

void First(int &n, int &m, TMatrix &mat1, TMatrix &mat2, int &k, int &window_size, int &threadCount, TMatrix &res);

#endif //OS_LABS_LAB3_H