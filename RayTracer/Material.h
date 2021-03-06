#pragma once

#include "Light.h"


class Material {
public:
	Material();
	~Material();

	virtual RGBColor surfaceColor(Vector3 &hit_point, Vector3 &normal, std::vector<Light *> lights) const = 0;
	virtual RGBColor surfaceColor(Vector3 &hit_point, Vector3 &normal, Vector3 &view, std::vector<Light *> lights) const = 0;
};

