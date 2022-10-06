#include "Vec.hpp"

Vec2::Vec2(float _x, float _y) {
	x = _x;
	y = _y;
};

void Vec2::add(Vec2 v) {
	x += v.x;
	y += v.y;
};

void Vec2::addRef(Vec2& v) {
	x += v.x;
	y += v.y;
};

void Vec2::addPtr(Vec2* v) {
	x += v->x;
	y += v->y;
};










Vec3::Vec3(float _x, float _y, float _z) : Vec2(_x, _y) {
	z = _z;
};

void Vec3::add(Vec3 v) {
	Vec2::add(v);
	z += v.z;
};

void Vec3::addRef(Vec3& v) {
	Vec2::addRef(v);
	z += v.z;
};

void Vec3::addPtr(Vec3* v) {
	Vec2::add(*v);
	z += v->z;
};








Vec4::Vec4(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
};

Vec4 Vec4::add(const Vec4& v) {
	return Vec4(
		x + v.x,
		y + v.y,
		z + v.z,
		w + v.w
	);
};

Vec4 Vec4::sub(const Vec4& v) {
	return Vec4(
		x - v.x,
		y - v.y,
		z - v.z,
		w - v.w
	);
};

Vec4 Vec4::mul(const Vec4& v) {
	return Vec4(
		x * v.x,
		y * v.y,
		z * v.z,
		w * v.w
	);
};

Vec4 Vec4::div(const Vec4& v) {
	return Vec4(
		x / v.x,
		y / v.y,
		z / v.z,
		w / v.w
	);
};

void Vec4::incr(const Vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
};

Vec4 Vec4::ZERO = Vec4(0, 0, 0, 0);