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

float theta = 180;

bool drawOpenBox = true;

int main() {
	// Set up display
	int horizontalResolution = 128;
	int verticalResolution = 128;
	float pixelSize = 1.0f;

	// Set up camera
	Vector3 eye = Vector3(0.0f, 0.0f, 30.0f);
	Vector3 lookAt = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	float exposure = 1.0f;
	Perspective pv = Perspective(eye, lookAt, up, exposure);

	// Create objects array
	std::vector<GeometricObject *> objects = std::vector<GeometricObject *>();

	// Objects to raytrace
	SpecularShader ss1 = SpecularShader(0.1f, 1.0f, 1.0f, 64.0f, blue);
	SpecularShader ss2 = SpecularShader(0.1f, 1.0f, 1.0f, 64.0f, red);
	DiffuseShader ds1 = DiffuseShader(0.1f, 1.0f, green);

	TriangleMesh m = TriangleMesh(&ds1);
	bool result = m.loadObj("openbox.obj");
	objects.push_back(&m);
	printf("Load OBJ as mesh successful: %d\n", result);

	//Sphere s1 = Sphere(Vector3(-11.0f, 0.0f, 10.0f), 10.0f, &ss1, false, true, false);
	//objects.push_back(&s1);

	//Sphere s2 = Sphere(Vector3(11.0f, 0.0f, 10.0f), 10.0f, &ss2, false, false, false);
	//objects.push_back(&s2);


	// Add lights to the scene
	std::vector<Light *> lights = std::vector<Light *>();
	Light l = Light(Vector3(0.0f, -3.0f, 15.0f), white);
	lights.push_back(&l);

	// Create raytracer and render
	Raytracer rt = Raytracer(horizontalResolution, verticalResolution, pixelSize);
	rt.render(pv, objects, lights);

	// Exit
	return 0;
}