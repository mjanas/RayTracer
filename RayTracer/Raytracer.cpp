#include "Raytracer.h"


Raytracer::Raytracer(int hres, int vres, float ps) { 
	horizontalResolution = hres;
	verticalResolution = vres;
	pixelSize = ps;
}


Raytracer::~Raytracer() { }

unsigned char convertColorFromFloatToChar(float in) {
	return (unsigned char)(in * 255);
}

void clamp255(unsigned char & c) {
	c = (c > 255) ? 255 : (c < 0) ? 0 : c;
}

void clamp1(float & f) {
	f = (f > 1.0f) ? 1.0f : (f < 0.0f) ? 0.0f : f;
}

void clamp255(unsigned char col[]) {
	col[0] = (col[0] > 255) ? 255 : (col[0] < 0) ? 0 : col[0];
	col[1] = (col[1] > 255) ? 255 : (col[1] < 0) ? 0 : col[1];
	col[2] = (col[2] > 255) ? 255 : (col[2] < 0) ? 0 : col[2];
}


RGBColor Raytracer::castRay(const Ray &ray, std::vector<GeometricObject *> &objects, std::vector<Light *> &lights, int depth) {
	RGBColor color = RGBColor();
	RGBColor refractionColor = RGBColor();
	RGBColor reflectionColor = RGBColor();
	if (depth > 4) {
		return color;
	}

	float t_near, t_far;
	float min = INFINITY;
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->intersect(ray, t_near, t_far)) {
			Vector3 hit_point = ray.origin + ray.direction * t_near;
			Vector3 normal = objects[i]->normal(hit_point);
			color = objects[i]->surfaceColor();
			break;
		}
	}
	return color;
}


void Raytracer::render(Perspective &p, std::vector<GeometricObject *> &objects, std::vector<Light *> &lights) {
	CImg<unsigned char> img(horizontalResolution, verticalResolution, 1, 3);
	img.fill(0);
	unsigned char c_color[] = { 0, 0, 0 };
	for (int r = 0; r < verticalResolution; r++) {
		for (int c = 0; c < horizontalResolution; c++) {
			float x = pixelSize * (c - horizontalResolution / 2.0f + 0.5f);
			float y = pixelSize * (r - verticalResolution / 2.0f + 0.5f);
			float distance = 10.0f;

			Vector3 dir = ((p.u * -x) + (p.v * y) - (p.w * distance)).normalize();
			Ray ray = Ray(p.eye, dir);

			RGBColor floatColor = castRay(ray, objects, lights, 0);
			clamp1(floatColor.red); clamp1(floatColor.green); clamp1(floatColor.blue);
			c_color[0] = convertColorFromFloatToChar(floatColor.red);
			c_color[1] = convertColorFromFloatToChar(floatColor.green);
			c_color[2] = convertColorFromFloatToChar(floatColor.blue);
			img.draw_point(r, c, c_color);
		}
	}
	img.display("Render Output");
	img.normalize(0, 255);
	img.save_bmp("output.bmp");
}