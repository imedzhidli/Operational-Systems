#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

extern "C" float Square(float A, float B);
extern "C" char* translation(long x);

float Square(float A, float B){
    return A * B;
}

char* translation(long x){
    string bin;
    if(x == 0) bin += "0";
    while(x > 0){
        bin += to_string(x % 2);
        x /= 2;
    }
    string number = bin;
    reverse(number.begin(), number.end());
    char* answer = (char*) malloc((number.size() + 1) * sizeof(char));
    strcpy(answer, number.c_str());
    return answer;
}