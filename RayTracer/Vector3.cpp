#include "Vector3.h"


Vector3::Vector3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}


Vector3::Vector3(float _x, float _y, float _z) {
	x = _x;
	y = _y; 
	z = _z;
}


Vector3::~Vector3() { }


Vector3 const & Vector3::operator=(const Vector3 &other) {
	if (this != &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return *this;
}


bool Vector3::operator==(const Vector3 &other) const {
	return (x == other.x) && (y == other.y) && (z == other.z);
}


bool Vector3::operator!=(const Vector3 &other) const {
	return !(*this == other);
}


bool Vector3::operator<(const Vector3 &other) const {
	return (x < other.x) && (y < other.y) && (z < other.z);
}


bool Vector3::operator>(const Vector3 &other) const {
	return (x > other.x) && (y > other.y) && (z > other.z);
}


bool Vector3::operator<=(const Vector3 &other) const {
	return (x <= other.x) && (y <= other.y) && (z <= other.z);
}


bool Vector3::operator>=(const Vector3 &other) const {
	return (x >= other.x) && (y >= other.y) && (z >= other.z);
}


Vector3 Vector3::operator+(const Vector3 &other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}


Vector3 Vector3::operator-(const Vector3 &other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}


Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}


float Vector3::operator*(const Vector3 &other) const {
	return (x * other.x) + (y * other.y) + (z * other.z);
}


Vector3 Vector3::operator^(const Vector3 &other) const {
	return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}


Vector3 Vector3::operator*(float scale) const {
	return Vector3(x * scale, y * scale, z * scale);
}


Vector3 Vector3::operator/(float scale) const {
	return Vector3(x / scale, y / scale, z / scale);
}


Vector3 const & Vector3::operator+=(const Vector3 &other) {
	x += other.x; y += other.y; z += other.z;
	return *this;
}


Vector3 const & Vector3::operator-=(const Vector3 &other) {
	x -= other.x; y -= other.y; z -= other.z;
	return *this;
}


Vector3 const & Vector3::operator*=(const float scale) {
	x *= scale; y *= scale; z *= scale;
	return *this;
}


Vector3 const & Vector3::operator/=(const float scale) {
	x /= scale; y /= scale; z /= scale;
	return *this;
}


Vector3 Vector3::normalize() {
	float length = sqrt((x * x) + (y * y) + (z * z));
	return Vector3(x / length, y / length, z / length);
}