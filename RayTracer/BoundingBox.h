#pragma once

#include "Ray.h"


class BoundingBox {
public:
	Vector3 min;
	Vector3 max;

	BoundingBox();
	BoundingBox(Vector3 _min, Vector3 _max);
	~BoundingBox();

	bool intersect(const Ray &ray, float &t_near, float &t_far) const;
};

