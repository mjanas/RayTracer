#pragma once

#include "Vector3.h"


class Ray {
public:
	Vector3 origin;
	Vector3 direction;

	Ray();
	Ray(Vector3 o, Vector3 d);
	~Ray();

	Ray const & operator=(const Ray &other);
};