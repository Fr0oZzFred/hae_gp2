// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <chrono>
#include <ctime>
#include <limits>
#include "LinkedList.hpp"

using namespace std;
using namespace std::chrono;
static void assert(bool test) {
	if (!test)
		throw "assert";
};

double getTimeStamp() //retourne le temps actuel en seconde
{
	nanoseconds ns =
		duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
	return ns.count() / 1000000000.0;


	typedef std::numeric_limits< double > dbl;
	cout.precision(dbl::max_digits10);
};

void testLinkedList() {
	IntList test;

	test.push_back(66);
	test.push_back(60);
	test.push_back(50);
	test.push_back(25);
	test.print();

	//test.remove(6);
	test.removeOne(25);
	test.print();

	int here = 0;
};

int main() {
	testLinkedList();
};
