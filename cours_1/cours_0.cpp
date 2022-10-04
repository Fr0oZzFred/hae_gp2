// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>

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

};

struct Array {
	int top = 0;

	void add(int value) {

	}

};

struct intPerso {

};

int main() {
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
	}
}
