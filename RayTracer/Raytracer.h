#pragma once

#include "CImg.h"
#include "Sphere.h"
#include "Perspective.h"
#include "DiffuseShader.h"

using namespace cimg_library;

class Raytracer {
public:

	int horizontalResolution, verticalResolution;
	float pixelSize;

	Raytracer(int hres, int vres, float ps);
	~Raytracer();

	void render(Perspective &p, std::vector<GeometricObject *> &objects, std::vector<Light *> &lights);

private:
	RGBColor castRay(const Ray &ray, std::vector<GeometricObject *> &objects, std::vector<Light *> &lights, int depth);
};