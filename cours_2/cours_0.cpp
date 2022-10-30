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
	arr64.push_back(1);
	arr64.push_back(2);
	//arr64.push_back(3);
	arr64.push_back(4);
	arr64.push_back(5);
	arr64.push_front(0);
	//arr64.set(3, 3);
	arr64.insert(3, 3);
	int here = 0;
}

int main() {
	testInt64Array();
}
