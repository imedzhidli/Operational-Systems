#include <iostream>

using namespace std;

extern "C" float Square(float A, float B);
extern "C" char* translation(long x);

int main(){
    int command;
    while((cout << "Введите команду: ") && (cin >> command)){
        if(command == 1){
            cout << "Введите длину A и B: ";
            float A, B;
            cin >> A >> B;
            cout << "Площадь -  " << Square(A, B) << endl;
        }
        else if(command == 2){
            long x;
            cout << "Введите десятичное число: ";
            cin >> x;
            char* memory = translation(x); /*преобразование числа в бинарное\троичное и суем в переменную*/
            cout << "Двоичное число - " << memory << endl;
            free(memory);
        }
        else
            cout << "Команды могут быть 1 и 2 ";
    }
}