#include "Plane.h"


Plane::Plane(Vector3 o, Vector3 n, Material * m) {
	origin = o;
	normal = n;
	material = m;
}


Plane::Plane(Vector3 o, Vector3 n, Material * m, bool sh, bool refl, bool refr) {
	origin = o;
	normal = n;
	material = m;
	shadowed = sh;
	reflective = refl;
	refractive = refr;
}


Plane::~Plane() {
	material = NULL;
}


bool Plane::intersect(const Ray &ray, float &t_near, float &t_far) {
	float denom = normal * ray.direction;
	if (fabs(denom) > 0.0001f) {
		float t = ((origin - ray.origin) * normal) / denom;
		if (t >= 0) {
			t_near = t;
			return true;
		}
	}
	return false;
}


Vector3 Plane::getNormal(Vector3 &hit_point) const {
	return normal;
}


Material * Plane::getMaterial() {
	return material;
}


bool Plane::isShadowed() {
	return shadowed;
}


bool Plane::isReflective() {
	return reflective;
}


bool Plane::isRefractive() {
	return refractive;
}