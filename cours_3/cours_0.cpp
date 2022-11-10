// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <chrono>
#include <ctime>
#include <limits>
#include "LinkedList.hpp"
#include "BinaryTree.hpp"

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

	test.removeOne(66);
	test.removeAll(60);
	test.print();

	int here = 0;
};

void testBTree() {
	IntTree ti;
	FloatTree tf;
	StringTree ts;
	ti.insert(1);
	ti.insert(2);
	ti.insert(3);
	ti.insert(4);
	ti.insert(65);
	ti.insert(-51);
	ti.insert(4651);
	ti.insert(-1569);
	ti.insert(0);

	cout << ti.size() << "\n";
	ti.remove(2);

	ti.print();
	cout << "\n";

	ts.insert("a");
	ts.insert("b");
	ts.insert("a");
	ts.insert("c");

	ts.print();
	cout << "\n";

	tf.insert(0.1f);
	tf.insert(0.2f);
	tf.insert(0.3f);
	tf.insert(0.4f);
	tf.insert(.65f);
	tf.insert(-.51f);
	tf.insert(.4651f);
	tf.insert(-.1569f);
	tf.insert(0);

	tf.print();
	cout << "\n";

	int here = 0;
};

int main() {
	//testLinkedList();
	testBTree();
};
