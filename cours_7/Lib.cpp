#include "Lib.hpp"
#include <ctime>
#include <cstdlib>

int Lib::rand() {
	static bool isInit = false;
	if (!isInit) {
		clock_t now = clock();
		srand(now);
		isInit = true;
	}

	return ::rand();
};