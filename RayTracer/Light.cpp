#include "Light.h"


Light::Light() {
	origin = Vector3();
	color = RGBColor();
	intensity = 50.0f;
}


Light::Light(Vector3 o, RGBColor c) {
	origin = o;
	color = c;
	intensity = 50.0f;
}


Light::~Light() { }


bool Light::intersect(const Ray &ray, float &t_near, float &t_far) const {
	if (ray.direction * origin == 0) {
		return true;
	}
	return false;
}
