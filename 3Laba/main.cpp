#include "laba3OS.h"

int main(int argc, char* argv[]){
    
    int n, m, threadCount;

    cout << "Введите кол-во потоков: ";
    cin >> threadCount;

    cout << "Введите размеры матрицы: ";
    cin >> n >> m;


    TMatrix mat1(n, vector<int>(m));
    TMatrix mat2(n, vector<int>(m));

    if (threadCount > n) threadCount = n;


    int window_size;
	
	printf("Введите размер окна (от 3 и более нечетное число): ");
	cin >> window_size;
	
    printf("Введите кол-во медианных фильтров: ");
    int k;
	cin >> k;

	printf("Введите вашу матрицу:\n");

    ReadMatrix(mat1);
    TMatrix res;

    First(n, m, mat1, mat2, k, window_size, threadCount, res);
    WriteMatrix(res);

    return 0;
}