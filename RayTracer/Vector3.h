#pragma once

#include "Constants.h"

class Vector3 {
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();

	Vector3 const & operator=(const Vector3 &other);
	bool operator==(const Vector3 &other) const;
	bool operator!=(const Vector3 &other) const;

	bool operator<(const Vector3 &other) const;
	bool operator>(const Vector3 &other) const;
	bool operator<=(const Vector3 &other) const;
	bool operator>=(const Vector3 &other) const;

	Vector3 operator+(const Vector3 &other) const;
	Vector3 operator-(const Vector3 &other) const;
	Vector3 operator-() const;

	float operator*(const Vector3 &other) const;
	Vector3 operator^(const Vector3 &other) const;

	Vector3 operator*(float scale) const;
	Vector3 operator/(float scale) const;

	Vector3 const & operator+=(const Vector3 &other);
	Vector3 const & operator-=(const Vector3 &other);
	Vector3 const & operator*=(const float scale);
	Vector3 const & operator/=(const float scale);

	float length();
	Vector3 normalize();

	float x, y, z;
};

