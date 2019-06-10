#pragma once

#include "GeometricObject.h"


class Triangle : public GeometricObject {
public:
	Vector3 a, b, c;
	Vector3 normal;
	
	Triangle(Vector3 _a, Vector3 _b, Vector3 _c, Material * m);
	Triangle(Vector3 _a, Vector3 _b, Vector3 _c, Material * m, bool sh, bool refl, bool refr);
	~Triangle();

	bool intersect(const Ray &ray, float &t_near, float &t_far);
	Vector3 getNormal(Vector3 &hit_point) const;
	Material * getMaterial();
	bool isShadowed();
	bool isReflective();
	bool isRefractive();

private:
	void computeNormal();
	Material * material;
	bool shadowed, reflective, refractive;
};

