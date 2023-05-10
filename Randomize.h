#ifndef rhje
#define rhje
#include <iostream>
#include <random>
#include <chrono>

int getRand(int mins, int maks) {
	std::mt19937 mt{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
	std::uniform_int_distribution<int> die{ mins, maks };
	
	return die(mt);
}

#endif