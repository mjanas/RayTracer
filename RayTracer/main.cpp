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

bool drawOpenBox = true;

int main() {
	// Set up display
	int horizontalResolution = 128;
	int verticalResolution = 128;
	float pixelSize = 1.0f;

	// Set up camera
	Vector3 eye = Vector3(0.0f, 0.0f, 5.0f);
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

	TriangleMesh m = TriangleMesh(&ss1);
	bool result = m.loadObj("teapot.obj");
	objects.push_back(&m);
	printf("Load OBJ as mesh successful: %d\n", result);


	/**
	Vector3 pt1 = Vector3(-30.0f, -30.0f, -30.0f);
	Vector3 pt2 = Vector3(-30.0f, 30.0f, -30.0f);
	Vector3 pt3 = Vector3(-30.0f, 30.0f, 30.0f);
	Vector3 pt4 = Vector3(-30.0f, -30.0f, 30.0f);
	Vector3 pt5 = Vector3(30.0f, -30.0f, -30.0f);
	Vector3 pt6 = Vector3(30.0f, 30.0f, -30.0f);
	Vector3 pt7 = Vector3(30.0f, 30.0f, 30.0f);
	Vector3 pt8 = Vector3(30.0f, -30.0f, 30.0f);

	Triangle t1 = Triangle(pt5, pt1, pt8, &ds1);
	Triangle t2 = Triangle(pt8, pt1, pt4, &ds1);
	Triangle t3 = Triangle(pt7, pt6, pt2, &ds1);
	Triangle t4 = Triangle(pt7, pt2, pt3, &ds1);
	Triangle t5 = Triangle(pt8, pt5, pt7, &ds1);
	Triangle t6 = Triangle(pt7, pt5, pt6, &ds1);
	Triangle t7 = Triangle(pt4, pt1, pt3, &ds1);
	Triangle t8 = Triangle(pt3, pt1, pt2, &ds1);
	Triangle t9 = Triangle(pt8, pt4, pt3, &ds1);
	Triangle t10 = Triangle(pt8, pt3, pt7, &ds1);

	objects.push_back(&t9);
	objects.push_back(&t10);
	objects.push_back(&t1);
	objects.push_back(&t2);
	objects.push_back(&t3);
	objects.push_back(&t4);
	objects.push_back(&t5);
	objects.push_back(&t6);
	objects.push_back(&t7);
	objects.push_back(&t8); **/

	//Sphere s1 = Sphere(Vector3(-11.0f, 0.0f, 10.0f), 10.0f, &ss1, false, true, false);
	//objects.push_back(&s1);

	//Sphere s2 = Sphere(Vector3(11.0f, 0.0f, 10.0f), 10.0f, &ss2, false, false, false);
	//objects.push_back(&s2);


	// Add lights to the scene
	std::vector<Light *> lights = std::vector<Light *>();
	Light l = Light(Vector3(0.0f, 0.0f, 5.0f), white);
	lights.push_back(&l);

	// Create raytracer and render
	Raytracer rt = Raytracer(horizontalResolution, verticalResolution, pixelSize);
	rt.render(pv, objects, lights);

	// Exit
	return 0;
}