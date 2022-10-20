// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Int64Array.hpp"

static void assert(bool test) {
	if (!test)
		throw "assert";
};

void testInt64Array() {
	Int64Array arr64(0);
	arr64.resize(10);
	arr64.resize(32);
	int here = 0;
}

int main() {
	testInt64Array();
}
