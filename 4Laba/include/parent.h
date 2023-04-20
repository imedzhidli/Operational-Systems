#ifndef PARENT_H
#define PARENT_H

#include <istream>
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <sys/wait.h>
#include <array>
#include <iterator>
#include <pthread.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <cstring>

using namespace std;

void ParentRoutine(istream& stream, const char* pathToChild);

#endif