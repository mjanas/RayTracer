#pragma once

#include "GeometricObject.h"

class Sphere : public GeometricObject {
public:

	Vector3 center;
	float radius;
	Material * material;
	bool shadowed, reflective, refractive;


	Sphere(Vector3 _center, float _radius, Material * _material);
	Sphere(Vector3 _center, float _radius, Material * _material, bool _shadowed, bool _reflective, bool _refractive);

	~Sphere();

	bool intersect(const Ray &ray, float &t_near, float &t_far);
	Vector3 getNormal(Vector3 &hit_point) const;
	Material * getMaterial();
	bool isShadowed();
	bool isReflective();
	bool isRefractive();
};