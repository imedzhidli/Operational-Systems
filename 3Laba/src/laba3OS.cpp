#include "laba3OS.h"
#include "utils.h"

void ReadMatrix(TMatrix &matrix) {
    for (int i = 0; i < Isize(matrix); i++) {
        for (int j = 0; j < Isize(matrix[i]); j++) {
            cin >> matrix[i][j];
        }
    }
}

void WriteMatrix(TMatrix &matrix) {
    for (int i = 0; i < Isize(matrix); i++) {
        for (int j = 0; j < Isize(matrix[i]); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}


int median(vector <int> &matrix){
    int n = matrix.size();
	for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(matrix[i] > matrix[j]){
               int temp = matrix[i];
               matrix[i] = matrix[j];
               matrix[j] = temp;
            }
        }
    }
    return matrix[n / 2];
}

void median_filter(int &height, int &width, TMatrix &a, TMatrix &b, int &area, int &lower_row, int &upper_row){
	int radius = (area - 1) / 2;
	for (int y = lower_row; y < upper_row; y++){
		int top = MAX(y - radius, 0);
		int bottom = MIN(y + radius, height - 1);
		for (int x = 0; x < width; x++){
			int left = MAX(x - radius, 0);
			int right = MIN(x + radius, width - 1);
			vector <int> m((bottom - top + 1) * (right - left + 1));
			int k = 0;
			for (int v = top; v <= bottom; v++){
				for (int u = left; u <= right; u++){
					m[k] = a[v][u];
					k++;
				}
			}
			b[y][x] = median(m);
		}
	}
}

void *lineresation(void *args){
	thread_args *arg = (thread_args*) args;
	median_filter(arg->height, arg->width, *arg->first_matrix, *arg->second_matrix, arg->area, arg->lower_row, arg->upper_row);
	return NULL;
}


void First(int &n, int &m, TMatrix &mat1, TMatrix &mat2, int &k, int &window_size, int &threadCount, TMatrix &res){
	int imedy = n / threadCount;
    pthread_t threads[threadCount];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	thread_args p_args[threadCount];
	for (int i  = 0; i < k; i++){
		for(int j = 0; j < threadCount; j++){
			p_args[j].height = n;
			p_args[j].width = m;

			if (i % 2 == 0){
				p_args[j].first_matrix = &mat1;
				p_args[j].second_matrix = &mat2;
			}
			else{
				p_args[j].first_matrix = &mat2;
				p_args[j].second_matrix = &mat1;
			}
			p_args[j].area = window_size;
			p_args[j].lower_row = j * imedy;
			p_args[j].upper_row = (j + 1) * imedy;
			if (j == threadCount - 1)
				p_args[j].upper_row = n;
			cout << "Поток "<< j+1 << " работает с [" << p_args[j].lower_row <<","<< p_args[j].upper_row << ") строкой(ами)" << "\n";
		}
		for (int i = 0; i < threadCount; i++){
			int res = pthread_create(&threads[i], &attr, lineresation, &p_args[i]);
			if (res != 0){
				cout << "Ошибка с созданием потока!";
				exit(-2);
			}
		}
		for (int i = 0; i < threadCount; i++){
			int res = pthread_join(threads[i], NULL);
			if (res != 0){
				cout << "Ошибка с ожиданием выхода!";
				exit(-3);
			}
		}
		printf("-------------------------------------------------\n");
	}

	if (k % 2 == 1){
		res = mat2;}
	else {
		res = mat1;}

}