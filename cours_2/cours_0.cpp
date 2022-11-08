// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <chrono>
#include <ctime>
#include <limits>
#include "Int64Array.hpp"

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
};

void testInt64Array() {
	Int64Array arr64(0);
	arr64.push_back(1);
	arr64.push_back(2);
	//arr64.push_back(3);
	arr64.push_back(4);
	arr64.push_back(5);
	//arr64.set(3, 3);
	arr64.insert(3, 3);
	arr64.fillWithRandom(5);
	arr64.push_front(0);
	arr64.push_front(1);
	arr64.push_front(0);
	int here = 0;
	printf("%d", arr64.searchPosition(5));
	printf("\n");
	//arr64.removeAll(0);
	//arr64.removeAll(4);
	//arr64.removeAll(3);


	Int64Array test(3);
	test.push_back(3);
	test.push_back(1);
	test.push_back(2);


	Int64Array* sorted = Int64Array::sort(arr64);
	int here1 = 0;
	{
		Int64Array nu(0);
		//nu.insert(0, 1);
		//nu.insert(0, 2);
		//nu.insert(0, 3);
		//nu.insert(0, 4);
		//nu.insert(0, 5);
		nu.fillWithRandom(5);
		nu.InsertionSort();
		int here = 0;
	}


	//Chrono
	{
		typedef std::numeric_limits< double > dbl;
		cout.precision(dbl::max_digits10);
	
		int sz = 1600;

		double start = getTimeStamp();
		Int64Array nu(0);
		nu.fillWithRandom(sz);
		nu.InsertionSort();
		double base = (getTimeStamp() - start);
		cout << "Nano sec 1er tab : " << base;
		printf("\n");
	
	
		double start2 = getTimeStamp();
		Int64Array nu2(0);
		nu2.fillWithRandom(sz);
		nu2.InsertionSort();
		double time1 = (getTimeStamp() - start2);
		cout << "Nano sec 2er tab : " << time1 << "   % : " << time1 / base;
		printf("\n");
	
		double start3 = getTimeStamp();
		Int64Array nu3(0);
		nu3.fillWithRandom(sz);
		nu3.Qsort();
		double time2 = (getTimeStamp() - start2);
		cout << "Nano sec 3er tab : " << time2 << "   % : " << time2 / time1;
		printf("\n");
	
		int here = 0;
	}

	{
		int sz = 1600;

		Int64Array nu(0);
		nu.insert(0, 5);
		nu.fillWithRandom(sz);
		nu.InsertionSort();

		double start = getTimeStamp();
		int tutu = nu.bsearch(5);
		double base = (getTimeStamp() - start);
		cout << "Nano sec bsearch : " << base << " " << tutu;
		printf("\n");

		double start2 = getTimeStamp();
		tutu = nu.linearsearch(5);
		double time1 = (getTimeStamp() - start2);
		cout << "Nano sec linearsearch : " << time1 << "   % : " << time1 / base << " /" << tutu;
		printf("\n");
	
		int here = 0;
	}
}

int main() {
	testInt64Array();
}
