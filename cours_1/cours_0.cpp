// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include"IntArray.hpp"

using namespace std;
struct Vec2 {
	float x = 0;
	float y = 0;

	Vec2() {}

	Vec2(float _x, float _y) {
		x = _x;
		y = _y;
	}

	void add(Vec2 v) {
		x += v.x;
		y += v.y;
	}

	void addRef(Vec2& v) {
		x += v.x;
		y += v.y;
	}

	void addPtr(Vec2* v) {
		x += v->x;
		y += v->y;
	}
};

struct Vec3 : Vec2 {
	float z = 0;

	Vec3() {}

	Vec3(float _x, float _y, float _z) : Vec2(_x, _y) {
		z = _z;
	}

	void add(Vec3 v) {
		Vec2::add(v);
		z += v.z;
	}

	void addRef(Vec3& v) {
		Vec2::addRef(v);
		z += v.z;
	}

	void addPtr(Vec3* v) {
		Vec2::add(*v);
		z += v->z;
	}
};

struct Vec4 {
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	Vec4() {}

	Vec4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vec4 add(const Vec4& v) {
		return Vec4(
			x + v.x,
			y + v.y,
			z + v.z,
			w + v.w
		);
	}

	Vec4 sub(const Vec4& v) {
		return Vec4(
			x - v.x,
			y - v.y,
			z - v.z,
			w - v.w
		);
	}

	Vec4 mul(const Vec4& v) {
		return Vec4(
			x * v.x,
			y * v.y,
			z * v.z,
			w * v.w
		);
	}

	Vec4 div(const Vec4& v) {
		return Vec4(
			x / v.x,
			y / v.y,
			z / v.z,
			w / v.w
		);
	}

	void incr(const Vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	static Vec4 ZERO;
};
Vec4 Vec4::ZERO = Vec4(0, 0, 0, 0);




/*
[][][][][][][][][0] <- fin de la chaîne de caracter
\0 ~= '0'
0
char => int sur 8 bit
*/

int Strlen(const char* str) {
	int idx = 0;
	while (str[idx] != 0)
	{
		idx++;
	}
	return idx;
};

int Strlen2(const char* str) {
	const char* start = str;
	while (*str != 0)
		str++;
	return str - start;
};

int Strlen3(const char* str) {
	const char* start = str;
	while (*str) str++;
	return str - start;
};

int Countc(const char* str, char c) {
	int length = 0;
	int count = 0;
	while (str[length] != 0)
	{
		length++;
		if (str[length] == c) {
			count++;
		}
	}
	return count;
};

void Strcpy(char* dst, const char* src) {
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}
};

void Strncpy(char* dst, const char* src, int nchars) {
	for (int i = 0; i < nchars; i++)
	{
		dst[i] = src[i];
	}
};


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

void TestArray() {

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

int main() {
	//testVec4();
	TestArray();

	/*int l = Strlen("Tutu0");
	int l1 = Strlen("T");
	int l2 = Strlen("Toto");
	int c = Countc("Tutu", 'u');*/


	/*char test[256] = {};
	//Strcpy(test, "Toto");
	Strncpy(test, "Toto", 2);
	int here = 0;*/
	
}
