#pragma once

#include "Material.h"

class SpecularShader :public Material {
public:

	float ambient, diffuse, specular;
	float exponent;
	RGBColor source_color;

	SpecularShader();
	SpecularShader(float ka, float kd, float ks, float e, RGBColor sc);
	~SpecularShader();

	RGBColor surfaceColor(Vector3 &hit_point, Vector3 &normal, std::vector<Light *> lights) const; 
	RGBColor surfaceColor(Vector3 &hit_point, Vector3 &normal, Vector3 &view, std::vector<Light *> lights) const;
};

