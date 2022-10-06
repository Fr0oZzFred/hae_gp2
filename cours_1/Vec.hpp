#pragma once
struct Vec2 {
	float x = 0;
	float y = 0;
	Vec2() {}
	Vec2(float _x, float _y);
	void add(Vec2 v);
	void addRef(Vec2& v);
	void addPtr(Vec2* v);
};

struct Vec3 : Vec2 {
	float z = 0;
	Vec3() {}
	Vec3(float _x, float _y, float _z);

	void add(Vec3 v);

	void addRef(Vec3& v);

	void addPtr(Vec3* v);
};

struct Vec4 {
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	Vec4() {}

	Vec4(float _x, float _y, float _z, float _w);
	Vec4 add(const Vec4& v);
	Vec4 sub(const Vec4& v);
	Vec4 mul(const Vec4& v);
	Vec4 div(const Vec4& v);
	void incr(const Vec4& v);
	static Vec4 ZERO;
};
