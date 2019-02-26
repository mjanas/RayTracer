#include "Raytracer.h"

RGBColor red = RGBColor(1.0f, 0.0f, 0.0f);
RGBColor green = RGBColor(0.0f, 1.0f, 0.0f);
RGBColor blue = RGBColor(0.0f, 0.0f, 1.0f);
RGBColor magenta = RGBColor(1.0f, 0.0f, 1.0f);
RGBColor yellow = RGBColor(1.0f, 1.0f, 0.0f);
RGBColor cyan = RGBColor(0.0f, 1.0f, 1.0f);
RGBColor white = RGBColor(1.0f, 1.0f, 1.0f);
RGBColor grey = RGBColor(0.5f, 0.5f, 0.5f);
RGBColor black = RGBColor(0.0f, 0.0f, 0.0f);

int main() {
	int horizontalResolution = 256;
	int verticalResolution = 256;
	float pixelSize = 1.0f;
	Raytracer rt = Raytracer(horizontalResolution, verticalResolution, pixelSize);

	Vector3 eye = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 lookAt = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	float exposure = 1.0f;
	Perspective pv = Perspective(eye, lookAt, up, exposure);

	DiffuseShader ds = DiffuseShader(1.0f, 1.0f, magenta);
	std::vector<GeometricObject *> objects = std::vector<GeometricObject *>();
	Sphere s = Sphere(Vector3(0.0f, 0.0f, -15.0f), 10.0f, &ds);
	objects.push_back(&s);

	std::vector<Light *> lights = std::vector<Light *>();
	Light l = Light(Vector3(0.0f, 10.0f, 5.0f), white);
	lights.push_back(&l);

	rt.render(pv, objects, lights);

	return 0;
}