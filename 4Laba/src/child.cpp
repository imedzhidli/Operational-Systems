#include <istream>
#include <ostream>
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <semaphore.h>

#include "string_to_vector.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Invalid arguments.\n";
        exit(EXIT_FAILURE);
    }

    auto *nameOutputFile = argv[1];
    ofstream out(nameOutputFile);
    int sfd;
    int semInFd;
    int semOutFd; 
    if ((sfd = shm_open(argv[2], O_RDWR, S_IRWXU)) == -1) {
        cout << "shm_open error" << endl;
        exit(EXIT_FAILURE);
    }

    if ((semInFd = shm_open(argv[3], O_RDWR, S_IRWXU)) == -1) {
        cout << "Shm_open error" << endl;
        exit(EXIT_FAILURE);
    }
    if ((semOutFd = shm_open(argv[4], O_RDWR, S_IRWXU)) == -1) {
        cout << "Shm_open error" << endl;
        exit(EXIT_FAILURE);
    }

    char* ptr = (char*)mmap(nullptr, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);
    if (ptr == MAP_FAILED) {
        cout << "error mmap func" << endl;
        exit(EXIT_FAILURE);
    }

    auto *semInput = (sem_t*)mmap(nullptr, getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, semInFd, 0);
    auto *semOutput = (sem_t*)mmap(nullptr, getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, semOutFd, 0);
    if (semInput == MAP_FAILED) {
        cout << "Mmap error" << endl;
        exit(EXIT_FAILURE);
    }

    if (semOutput == MAP_FAILED) {
        cout << "Mmap error" << endl;
        exit(EXIT_FAILURE);
    }
    while (true) {
        sem_wait(semOutput);
        string stringNumbers = ptr;
        if (stringNumbers.empty()) {
            sem_post(semInput);
            break;
        }

        vector <int> numbers = StringToVector(stringNumbers);
        float firstNumber = numbers[0];
        for (size_t i = 1; i < numbers.size(); i++) {
            if (numbers[i] == 0) {
                cout << "Division by zero.\n";
                out << "\n";
                out.close();
                sprintf((char *) ptr, "%s", "Division by zero.");
                sem_post(semInput);
                exit(EXIT_FAILURE);
            }
            firstNumber /= numbers[i];
        }
        out << firstNumber << " ";
        sem_post(semInput);
    }
    out << "\n";
    out.close();
    if (munmap(ptr, getpagesize()) == -1) {
        cout << "Munmap error" << endl;
        exit(EXIT_FAILURE);
    }
    if (munmap(semInput, getpagesize()) == -1) {
        cout << "Munmap error" << endl;
        exit(EXIT_FAILURE);
    }
    if (munmap(semOutput, getpagesize()) == -1) {
        cout << "Munmap error" << endl;
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}