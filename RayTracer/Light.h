#pragma once

#include "Ray.h"
#include "RGBColor.h"


class Light {
public:
	Vector3 origin;
	RGBColor color;
	float intensity;

	Light();
	Light(Vector3 o, RGBColor c);
	~Light();

	bool intersect(const Ray &ray, float &t_near, float &t_far) const;
};

