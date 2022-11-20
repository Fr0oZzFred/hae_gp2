#pragma once
struct Vec3 {
	float	x = 0, y = 0, z = 0, w = 1;
};
//Manipuling Vectors Functions
Vec3 AddVec(Vec3& v1, Vec3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
};
Vec3 SubVec(Vec3& v1, Vec3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
};
Vec3 MulVec(Vec3& v1, Vec3& v2) {
	return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
};
Vec3 DivVec(Vec3& v1, Vec3& v2) {
	return { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
};
Vec3 VecxScalar(Vec3& v1, float k) {
	return { v1.x * k, v1.y * k, v1.z * k };
};
Vec3 VecdScalar(Vec3& v1, float k) {
	return { v1.x / k, v1.y / k, v1.z / k };
};
//Operator
Vec3 operator+(Vec3& v1, Vec3& v2) {
	return AddVec(v1, v2);
};
Vec3 operator-(Vec3& v1, Vec3& v2) {
	return SubVec(v1, v2);
};
Vec3 operator*(Vec3& v1, Vec3& v2) {
	return MulVec(v1, v2);
};
Vec3 operator/(Vec3& v1, Vec3& v2) {
	return DivVec(v1, v2);
};
Vec3 operator*(Vec3& v1, float k) {
	return VecxScalar(v1, k);
};
Vec3 operator/(Vec3& v1, float k) {
	return VecdScalar(v1, k);
};

//Manipuling Vectors Functions
float Dot(Vec3& v1, Vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
};
float Magnitude(Vec3& v) {
	return sqrtf(Dot(v, v));
};
Vec3 Norm(Vec3& v) {
	float l = Magnitude(v);
	return { v.x / l, v.y / l, v.z / l };
};
Vec3 Cross(Vec3& v1, Vec3& v2) {
	Vec3 v3;
	v3.x = v1.y * v2.z - v1.z * v2.y;
	v3.y = v1.z * v2.x - v1.x * v2.z;
	v3.z = v1.x * v2.y - v1.y * v2.x;
	return v3;
};
