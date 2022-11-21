#pragma once

struct Mat4 {
	float m[4][4] = { 0 };
};

Vec3 Mat4MulVec3(Mat4& m, Vec3& i) {
	Vec3 v;
	v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
	v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
	v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
	v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
	return v;
};

Vec3 operator* (Mat4& m, Vec3& i) {
	return Mat4MulVec3(m, i);
};

//Manipulating Matrices Functions
Mat4 IdentityMatrix() {
	Mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
};
Mat4 XRotationMatrix(float theta) {
	Mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(theta);
	matrix.m[1][2] = sinf(theta);
	matrix.m[2][1] = -sinf(theta);
	matrix.m[2][2] = cosf(theta);
	matrix.m[3][3] = 1.0f;
	return matrix;
};
Mat4 YRotationMatrix(float theta) {
	Mat4 matrix;
	matrix.m[0][0] = cosf(theta);
	matrix.m[0][2] = sinf(theta);
	matrix.m[2][0] = -sinf(theta);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(theta);
	matrix.m[3][3] = 1.0f;
	return matrix;
};
Mat4 ZRotationMatrix(float theta) {
	Mat4 matrix;
	matrix.m[0][0] = cosf(theta);
	matrix.m[0][1] = sinf(theta);
	matrix.m[1][0] = -sinf(theta);
	matrix.m[1][1] = cosf(theta);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
};
Mat4 TranslationMatrix(float x, float y, float z) {
	Mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	matrix.m[3][0] = x;
	matrix.m[3][1] = y;
	matrix.m[3][2] = z;
	return matrix;
};
Mat4 ProjectionMatrix(float FOVdeg, float aspect, float cameraDistance, float renderDistance) {
	float FOVrad = 1.0f / tanf(FOVdeg * 0.5f / 180.0f * 3.14159f);
	Mat4 matrix;
	matrix.m[0][0] = aspect * FOVrad;
	matrix.m[1][1] = FOVrad;
	matrix.m[2][2] = renderDistance / (renderDistance - cameraDistance);
	matrix.m[3][2] = (-renderDistance * cameraDistance) / (renderDistance - cameraDistance);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return matrix;
};
Mat4 MatrixMultiply(Mat4& m1, Mat4& m2) {
	Mat4 matrix;
	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 4; r++) {
			matrix.m[r][c] = 
				m1.m[r][0] * m2.m[0][c] +
				m1.m[r][1] * m2.m[1][c] + 
				m1.m[r][2] * m2.m[2][c] + 
				m1.m[r][3] * m2.m[3][c];
		}
	}
	return matrix;
};
Mat4 operator * (Mat4& m1, Mat4& m2) {
	return MatrixMultiply(m1, m2);
};
Mat4 PointingMatrix(Vec3& pos, Vec3& target, Vec3& up) {
	
	//Calcute new forward direction
	Vec3 newForward = target - pos;
	newForward = Norm(newForward);

	//Calculate new Up direction
	Vec3 a = newForward * Dot(up, newForward);
	Vec3 newUp = up - a;
	newUp = Norm(newUp);

	// New Right direction
	Vec3 newRight = Cross(newUp, newForward);

	//Construct Dimensioning and Translation Matrix
	Mat4 matrix;
	matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
	return matrix;
};
Mat4 MatrixQuickInverse(Mat4& m) //Only for Rotation/Translation Matrices
{
	Mat4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
};