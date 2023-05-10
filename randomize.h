#ifndef RANDOM
#define RANDOM

#include <cstdlib>
int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

#endif