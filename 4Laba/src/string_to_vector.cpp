#include "string_to_vector.h"

using namespace std;

vector<int> StringToVector(string const& stringNumbers, char separator) {
    vector<int> results;
    auto start = stringNumbers.begin();
    auto end = stringNumbers.end();
    auto next = find(start, end, separator);
    while (next != end) {
        results.push_back(stof(string(start, next)));
        start = next + 1;
        next = find(start, end, separator);
    }
    results.push_back(stof(string(start, next)));
    return results;
}
