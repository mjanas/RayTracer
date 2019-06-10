#pragma once

#include "Material.h"


class DiffuseShader : public Material {
public:
	DiffuseShader(float ka, float kd, RGBColor sc);
	~DiffuseShader();

	RGBColor surfaceColor(Vector3 &hit_point, Vector3 &normal, std::vector<Light *> lights) const;
	RGBColor surfaceColor(Vector3 &hit_point, Vector3 &normal, Vector3 &view, std::vector<Light *> lights) const;

private:
	float ambient, diffuse;
	RGBColor source_color;
};