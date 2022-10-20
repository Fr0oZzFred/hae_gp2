// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include "IntArray.hpp"
#include "Vec.hpp"
#include "StringFunctions.hpp"
#include "LinkedListInt.hpp"
#include "IntTree.hpp"
#include <stdlib.h>
#include <time.h>
#include <functional>
#include "FloatArray.hpp"
#include "Lib.hpp"
#include "StringTree.hpp"
#include "StringTreeCorrection.hpp"
using namespace std;

static void assert(bool test) {
	if (!test)
		throw "assert";
};

void testVec4() {
	{
		Vec3 sapin;
		//int here = 0;

		//Vec3 v0(6, 7, 8);
		//Vec3 v1(1, 2, 3);
		//int here = 0;
		//v0.addPtr(&v1);
		//int here = 0;
	}


	{
		Vec4 v0(1, 2, 3, 4);
		Vec4 v1(1, 2, 3, 4);

		Vec4 vAdd;
		Vec4 vSub;
		Vec4 vMul;
		Vec4 vDiv;
		Vec4 vIncr;

		vAdd = v0.add(v1);
		int here = 0;
		vSub = v0.sub(v1);
		here = 0;
		vMul = v0.mul(v1);
		here = 0;
		vDiv = v0.div(v1);
		here = 0;
		v0.incr(v1);
		here = 0;

	}

	{
		Vec4 v0(1, 2, 3, 4);
		Vec4 v1(1, 2, 3, 4);

		Vec4 res = v0.add(v1);
		if (res.x != 2) throw "assert";
		if (res.y != 4) throw "assert";
		int here = 0;
	}

	{
		Vec4 v0(1, 2, 3, 4);
		Vec4 v1(1, 2, 3, 4);

		Vec4 res = v0.sub(v1);
		if (res.x != 0) throw "assert";
		if (res.y != 0) throw "assert";
		int here = 0;

		Vec4 v2 = Vec4::ZERO;
		here = 0;
	}

	{
		Vec4* r0 = new Vec4();
		//int here = 0;

		Vec4* r1 = new Vec4;
		Vec4* r2 = nullptr;
		//int here = 0;

		Vec4* r3 = new Vec4[16];
		r3[4].incr(Vec4(666, 0, 0, 0));

		auto r34 = r3[4];
		auto r34bis = *(r3 + 4);

		int here = 0;
	}

}

void testArray() {

	{
		IntArray a(16);
		a.set(0, 3);
		a.set(15, 4);
		if (a.get(4) != 0)throw "assert";
		int here = 0;
	}
	{
		IntArray a(8);
		if (a.get(0) != 0)throw "assert";
		a.set(2, 666);
		a.set(a.getSize() - 1, 777);

		a.resize(5);
		if (a.getSize() != 5)throw "assert";
		if (a.get(2) != 666)throw "assert";

		a.resize(1024);
		assert(a.get(256) == 0);
		assert(a.get(2) == 666);
		assert(a.get(512) == 0);

		int here = 0;
	}

	{
		IntArray a(8);
		for (int i = 0; i < 8; ++i) {
			a.set(i, i*i);
			printf("%d ", a.get(i));
		}
		printf("\n");
		int here = 0;
		printf("%d\n", a.searchOrderInferior(-1));
		printf("%d\n", a.searchOrderInferior(8));
		printf("%d\n", a.searchOrderInferior(50));



		a.insertOrderInferior(-1); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(8); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(9); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(50); // order sur A par le predicat f : a[i] < a[i+1]

		assert(a.isSorted());
		here = 0;

		
		//auto predicate = [](int & e0,int & e1) {
		//	return e0 < e1;
		//};
		//a.insertOrderInferior(21);
	}

	{
		IntArray b(4);
		b.set(0, 5);
		b.set(1, -5);
		b.set(2, 50);
		b.set(3, 7);

		int beforeSort = 0;
		b.Sort();

		int sorted = 0;

		assert(b.isSorted());

	}
}

void testString() {
	int l = Strlen("Tutu0");
	int l1 = Strlen("T");
	int l2 = Strlen("Toto");
	int c = Countc("Tutu", 'u');

	char test[256] = {};
	Strcpy(test, "Toto");
	Strncpy(test, "Toto", 2);
	int here = 0;
}

void testLinkedList() {
	LinkedListInt tutu;

	tutu.insert(0);
	tutu.insert(0);
	tutu.insert(5);
	tutu.insert(9);
	tutu.insert(7);

	tutu.remove(4);
	tutu.remove(5);
	tutu.remove(0);
	tutu.remove(7);

	tutu.print();

	int here = 0;
}

void testIntTree() {
	IntTreeController treeController;

	//treeController.insert(2); 
	//treeController.insert(1);
	//treeController.insert(12);
	//treeController.insert(13);
	//treeController.insert(-5);


	//treeController.insert(2);
	//treeController.insert(-1);
	//treeController.insert(13);
	//treeController.insert(1);
	//treeController.insert(-4);
	//treeController.insert(-5);
	//treeController.insert(666);
	//treeController.insert(86);
	//treeController.insert(-7);
	//treeController.insert(42);
	//treeController.insert(2077);
	//treeController.insert(4);
	//treeController.remove(2);

	//for (int i = 0; i < 10; i++) {
	//	treeController.insert(5);
	//}
	//treeController.remove(5);

	//treeController.print();


	clock_t now = clock();
	srand(now);
	std::vector<int> data;
	for (int i = 0; i < 10; ++i) {
		data.push_back(rand() % 20 - 10);
	}
	treeController.print();
	for (auto v : data) {
		treeController.insert(v);
	}
	treeController.print();
	for (auto v : data) {
		cout << "\n removing " << std::to_string(v) << "\n";
		treeController.remove(v);
		treeController.print();
	}
	treeController.print();
}

void testC() {
	int* data = data = (int*)malloc(150 * sizeof(int));
	//int tata[150] = {}; //Allocations Statiques (supprimé de la mémoire après la sortie de la func)
	//int* toto = new int[150]; //Allocations Dynamiques (reste en mémoire après la sortie de la func)

	//new int [150] fait l'équivalent de new (((int*)malloc(150 * sizeof(int))) (int) (150);

	for (int i = 0; i < 150; i++) {
		data[i] = i * i;
	}
	for (int i = 149; i > 0; i--) {
		printf("%d ", data[i]);
	}


	//stack pointer => pointeur sur le debut de la memoire local
	//program pointer
	{
		int o = 0;//sp+=4; [sp] = 0;
		int* sapin = (int*)malloc(8); //sp+=sizeof(int*); [sp] = [malloc(8)]
	}
}

void testFloatArray() {
	FloatArray arr(16);
	arr.push_first(1);
	arr.push_back(16);
	arr.push_back(15);
	arr.push_first(14);
	arr.resize(150);
	arr.push_back(666);
	arr.push_first(-666);
	arr.print();

	float totalSum = 0;
	auto maFonction = [&totalSum](float val) {
		totalSum += val;
	};
	arr.iter(maFonction);
	printf("-------SUM--------\n");
	printf("%f ", totalSum);
	printf("\n");
	int here = 0;


	float abc[3] = { 66, 67, 68 };

	FloatArray nu = arr.fromArray(arr.getData(), arr.getSize());
	nu.print();

}

void testLib() {
	char sapin[6] = "sapin";
	char buffer[512] = {};
	Lib::Memcpy(buffer, "sapin", 5);
	int here = 0;


	const char* test = Lib::StrChr("Sapin", 'a');
	printf("%s", test);
	int here1 = 0;

	printf("\n");
	const char* one = "one";
	const char* test1 = Lib::StrStr("one two three", one);
	const char* test2 = Lib::StrStr("one two three", "three");
	printf("%s", test1);
	printf("\n");
	printf("%s", test2);
	int here2 = 0;

	printf("\n");
	int buf[512] = {};
	int buf2[512] = {0,1,2,3,4,0,1,2,3,4,0,1,2,3,4 };
	Lib::MemcpyRec((char*)buf, (char*) buf2, sizeof(buf2));
	int here3 = 0;
	printf("\n");

	const char* test3 = Lib::StrChrRec("Sapin", 'a');
	const char* test6 = Lib::StrChrRec("Sapin", 'c');
	printf("%s", test3);
	printf("\n"); 
	printf("%s", test6);
	printf("\n");

	const char* test4 = Lib::StrStrRec("one two three", one);
	const char* test5 = Lib::StrStrRec("one two three", "three");
	printf("%s", test4);
	printf("\n");
	printf("%s", test5);



	printf("\n");
	printf("%d", Lib::add(0, 5));
	printf("\n");
	printf("%d", Lib::sub(0, 5));
	printf("\n");
	printf("%d", Lib::mul(50, 10));
	printf("\n");
	printf("%d", Lib::div(2, 2));
	printf("\n");
	printf("%d", Lib::mod(5, 3));
	printf("\n");


	printf("%d", Lib::StrlenRec("Tutu"));
	printf("\n");

	char buff[512] = {};
	Lib::StrcpyRec(buff, "Truc");
	printf("%s", buff);
	printf("\n");

	char buffe[512] = {};
	Lib::StrcpyRec(buffe, "Machin");
	printf("%s", buffe);
	printf("\n");

	printf("%d", Lib::StrCmp("a", "b"));
	printf("\n");

	printf("%d", Lib::mulTerminalRecursion(2, 5, 0));
	printf("\n");

	printf("%d", Lib::divTerminalRecursion(4, 24, 0));
	printf("\n");
}

void testStringTree() {
	StringTreeController stc;
	stc.insert((char*)"b");
	stc.insert((char*)"a");
	stc.insert((char*)"c");
	stc.insert((char*)"d");
	stc.remove((char*)"d");
	stc.print();
	printf("\n");
	printf("%d", stc.searchMatch((char*)"b"));
	printf("\n");
	printf("%d", stc.searchMatch((char*)"a"));
	printf("\n");

	StringTreeController stc1;
	stc1.insert((char*)"Lilia");
	stc1.insert((char*)"Livai");
	stc1.insert((char*)"Lola");
	stc1.insert((char*)"Lord");
	stc1.searchPrefix((char*)"L");
}

void correctionStringTree() {
	StringTreeControllerCorrection ctlr;

	std::string to("toto");
	std::string tu("tutu");
	std::string ta("tata");

	ctlr.insert(to);
	ctlr.insert(tu);
	ctlr.insert(ta);
	ctlr.print();

	auto res = ctlr.searchString(tu);

	if (res) cout << res->value << "\n";
	

	std::string tu1("tu");
	auto res1 = ctlr.searchPattern(tu1);
	if (res1) cout << res1->value << "\n";
}

int main() {
	//testVec4();
	// 
	//testArray();
	// 
	//testString();
	// 
	//testLinkedList();
	// 
	//clock_t init = clock();
	//testIntTree();
	//
	//testC();
	//
	//testFloatArray();
	//
	testLib();
	//
	//testStringTree();
	//
	//correctionStringTree();
}
