#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "string_to_vector.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Invalid arguments.\n";
        exit(EXIT_FAILURE);
    }

    auto *nameOutputFile = argv[1];
    ofstream out(nameOutputFile);

    string stringNumbers;
    while (getline(cin, stringNumbers)) {

        vector <int> numbers = StringToVector(stringNumbers);
        float firstNumber = numbers[0];
        for (unsigned long long i = 1; i < numbers.size(); i++) {
            if (numbers[i] == 0) {
                cout << "Division by zero.\n";
                out << "\n";
                out.close();
                exit(EXIT_FAILURE);
            }
            firstNumber /= numbers[i];
        }
        out << firstNumber << " ";
    }
    out << "\n";
    out.close();
    return 0;
}
