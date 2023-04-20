#include "parent.h"

using namespace std;

void ParentRoutine(istream& stream, const char* pathToChild) {
    string nameOutputFile;
    getline(stream, nameOutputFile);
    array <int, 2> parentPipe; //0 - read 1 - write 
    if (pipe(parentPipe.data()) == -1) {
        cout << "Error creating pipe\n";
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) {
        cout << "Error creating process\n";
        exit(EXIT_FAILURE);
    }

    if (pid != 0) { // родительский процесс
        close(parentPipe[0]);
        string stringNumbers;
        while (getline(stream, stringNumbers)) {
            stringNumbers += "\n";
            write(parentPipe[1], stringNumbers.data(), stringNumbers.size());
        }
        close(parentPipe[1]);
        wait(nullptr);
    }
    else { // дочерний процесс
        close(parentPipe[1]);
        dup2(parentPipe[0], 0);

        if(execl(pathToChild, pathToChild, nameOutputFile.data(), nullptr) == -1) {
            cout << "Failed to exec\n";
            exit(EXIT_FAILURE);
        }
        close(parentPipe[0]);
    }
}
