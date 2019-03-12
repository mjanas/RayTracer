#pragma once

#include "GeometricObject.h"

class Plane : public GeometricObject {
public:
	Vector3 origin;
	Vector3 normal;
	Material * material;

	Plane(Vector3 o, Vector3 n, Material * m);
	~Plane();

	bool intersect(const Ray &ray, float &t_near, float &t_far);
	Vector3 getNormal(Vector3 &hit_point) const;
	Material * getMaterial();
};