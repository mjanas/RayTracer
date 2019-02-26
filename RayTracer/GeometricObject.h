#pragma once

#include "Ray.h"
#include "RGBColor.h"

class GeometricObject {
public:
	GeometricObject();
	~GeometricObject();

	virtual bool intersect(const Ray &ray, float &t_near, float &t_far) const = 0;
	virtual Vector3 normal(Vector3 & hit_point) const = 0;
	virtual RGBColor surfaceColor() const = 0;
};

