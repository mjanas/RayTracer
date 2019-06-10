#pragma once

#include "Vector3.h"


class Matrix4 {
public:
	float x[4][4] = { {1.0f, 0.0f, 0.0f, 0.0f}, 
					  {0.0f, 1.0f, 0.0f, 0.0f}, 
					  {0.0f, 0.0f, 1.0f, 0.0f}, 
					  {0.0f, 0.0f, 0.0f, 1.0f} };

	Matrix4();
	~Matrix4();
	Matrix4(float r1c1, float r1c2, float r1c3, float r1c4,
			float r2c1, float r2c2, float r2c3, float r2c4,
			float r3c1, float r3c2, float r3c3, float r3c4,
			float r4c1, float r4c2, float r4c3, float r4c4);

	const float * operator[](size_t i) const;
	float * operator[](size_t i);
	Matrix4 operator*(const Matrix4 &rhs) const;

	Matrix4 & transpose();
	Matrix4 transposed() const;
	void multVecMatrix(const Vector3 &src, Vector3 &dst) const;
	void multDirMatrix(const Vector3 &src, Vector3 &dst) const;
	Matrix4 inverse() const;
	const Matrix4 & invert();
};