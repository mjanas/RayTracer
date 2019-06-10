#include "Matrix4.h"


Matrix4::Matrix4() { }


Matrix4::~Matrix4() {}


Matrix4::Matrix4(float r1c1, float r1c2, float r1c3, float r1c4,
				 float r2c1, float r2c2, float r2c3, float r2c4,
				 float r3c1, float r3c2, float r3c3, float r3c4,
				 float r4c1, float r4c2, float r4c3, float r4c4) {
	x[0][0] = r1c1;
	x[0][1] = r1c2;
	x[0][2] = r1c3;
	x[0][3] = r1c4;
	x[1][0] = r2c1;
	x[1][1] = r2c2;
	x[1][2] = r2c3;
	x[1][3] = r2c4;
	x[2][0] = r3c1;
	x[2][1] = r3c2;
	x[2][2] = r3c3;
	x[2][3] = r3c4;
	x[3][0] = r4c1;
	x[3][1] = r4c2;
	x[3][2] = r4c3;
	x[3][3] = r4c4;
}

const float * Matrix4::operator[](size_t i) const { 
	return x[i]; 
}


float * Matrix4::operator[](size_t i) {
	return x[i];
}


/**
 * Source: https://www.scratchapixel.com/code.php?id=28&origin=/lessons/3d-basic-rendering/introduction-polygon-mesh&src=1
 */
static void multiply(const Matrix4 &a, const Matrix4 &b, Matrix4 &c) {
#if 0
	for (uint8_t i = 0; i < 4; ++i) {
		for (uint8_t j = 0; j < 4; ++j) {
			c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
				a[i][2] * b[2][j] + a[i][3] * b[3][j];
		}
	}
#else
	const float * __restrict ap = &a.x[0][0];
	const float * __restrict bp = &b.x[0][0];
	float * __restrict cp = &c.x[0][0];

	float a0, a1, a2, a3;
	a0 = ap[0];
	a1 = ap[1];
	a2 = ap[2];
	a3 = ap[3];

	cp[0] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
	cp[1] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
	cp[2] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
	cp[3] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

	a0 = ap[4];
	a1 = ap[5];
	a2 = ap[6];
	a3 = ap[7];

	cp[4] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
	cp[5] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
	cp[6] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
	cp[7] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

	a0 = ap[8];
	a1 = ap[9];
	a2 = ap[10];
	a3 = ap[11];

	cp[8] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
	cp[9] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
	cp[10] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
	cp[11] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

	a0 = ap[12];
	a1 = ap[13];
	a2 = ap[14];
	a3 = ap[15];

	cp[12] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
	cp[13] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
	cp[14] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
	cp[15] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];
#endif
}


// Multiply the current matrix with another matrix (rhs)
Matrix4 Matrix4::operator*(const Matrix4 &rhs) const {
	Matrix4 temp;
	multiply(*this, rhs, temp);
	return temp;
}


/**
 * Source: https://www.scratchapixel.com/code.php?id=28&origin=/lessons/3d-basic-rendering/introduction-polygon-mesh&src=1
 */
Matrix4 Matrix4::transposed() const {
#if 0
	Matrix44 t;
	for (uint8_t i = 0; i < 4; ++i) {
		for (uint8_t j = 0; j < 4; ++j) {
			t[i][j] = x[j][i];
		}
	}
	return t;
#else
	return Matrix4(x[0][0], x[1][0], x[2][0], x[3][0],
				   x[0][1], x[1][1], x[2][1], x[3][1],
				   x[0][2], x[1][2], x[2][2], x[3][2],
				   x[0][3], x[1][3], x[2][3], x[3][3]);
#endif
}


/**
 * Source: https://www.scratchapixel.com/code.php?id=28&origin=/lessons/3d-basic-rendering/introduction-polygon-mesh&src=1
 */
Matrix4 & Matrix4::transpose() {
	Matrix4 tmp(x[0][0], x[1][0], x[2][0], x[3][0],
				x[0][1], x[1][1], x[2][1], x[3][1],
				x[0][2], x[1][2], x[2][2], x[3][2],
				x[0][3], x[1][3], x[2][3], x[3][3]);
	*this = tmp;
	return *this;
}


/**
 * Source: https://www.scratchapixel.com/code.php?id=28&origin=/lessons/3d-basic-rendering/introduction-polygon-mesh&src=1
 */
void Matrix4::multVecMatrix(const Vector3 &src, Vector3 &dst) const {
	float a, b, c, w;

	a = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0] + x[3][0];
	b = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1] + x[3][1];
	c = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2] + x[3][2];
	w = src.x * x[0][3] + src.y * x[1][3] + src.z * x[2][3] + x[3][3];

	dst.x = a / w;
	dst.y = b / w;
	dst.z = c / w;
}


/**
 * Source: https://www.scratchapixel.com/code.php?id=28&origin=/lessons/3d-basic-rendering/introduction-polygon-mesh&src=1
 */
void Matrix4::multDirMatrix(const Vector3 &src, Vector3 &dst) const {
	float a, b, c;

	a = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0];
	b = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1];
	c = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2];

	dst.x = a;
	dst.y = b;
	dst.z = c;
}


Matrix4 Matrix4::inverse() const {
	int i, j, k;
	Matrix4 s = Matrix4();
	Matrix4 t = Matrix4();
	// Forward elimination
	for (i = 0; i < 3; i++) {
		int pivot = i;
		float pivotsize = t[i][i];
		if (pivotsize < 0)
			pivotsize = -pivotsize;
		for (j = i + 1; j < 4; j++) {
			float tmp = t[j][i];
			if (tmp < 0)
				tmp = -tmp;
			if (tmp > pivotsize) {
				pivot = j;
				pivotsize = tmp;
			}
		}
		if (pivotsize == 0) {
			return Matrix4(); // cannot invert singular matrix
		}
		if (pivot != i) {
			for (j = 0; j < 4; j++) {
				float tmp;
				tmp = t[i][j];
				t[i][j] = t[pivot][j];
				t[pivot][j] = tmp;
				tmp = s[i][j];
				s[i][j] = s[pivot][j];
				s[pivot][j] = tmp;
			}
		}
		for (j = i + 1; j < 4; j++) {
			float f = t[j][i] / t[i][i];
			for (k = 0; k < 4; k++) {
				t[j][k] -= f * t[i][k];
				s[j][k] -= f * s[i][k];
			}
		}
	}
	// Backward substitution
	for (i = 3; i >= 0; --i) {
		float f;
		if ((f = t[i][i]) == 0) {
			return Matrix4(); // Cannot invert singular matrix
		}
		for (j = 0; j < 4; j++) {
			t[i][j] /= f;
			s[i][j] /= f;
		}
		for (j = 0; j < i; j++) {
			f = t[j][i];
			for (k = 0; k < 4; k++) {
				t[j][k] -= f * t[i][k];
				s[j][k] -= f * s[i][k];
			}
		}
	}
	return s;
}

// \brief set current matrix to its inverse
const Matrix4 & Matrix4::invert() {
	*this = inverse();
	return *this;
}