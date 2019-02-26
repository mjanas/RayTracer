#pragma once

#include "GeometricObject.h"

class Sphere : public GeometricObject {
public:

	Vector3 center;
	float radius;
	RGBColor surface_color;

	Sphere();
	Sphere(Vector3 _center, float _radius, RGBColor _color);
	~Sphere();

	bool intersect(const Ray &ray, float &t_near, float &t_far) const;
	Vector3 normal(Vector3 &hit_point) const;
	RGBColor surfaceColor() const;
};