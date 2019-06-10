#pragma once

#include "Ray.h"
#include "Material.h"

class GeometricObject {
public:

	GeometricObject();
	~GeometricObject();

	virtual bool intersect(const Ray &ray, float &t_near, float &t_far) = 0;
	virtual Vector3 getNormal(Vector3 &hit_point) const = 0;
	virtual Material * getMaterial() = 0;
	virtual bool isShadowed() = 0;
	virtual bool isReflective() = 0;
	virtual bool isRefractive() = 0;
};

