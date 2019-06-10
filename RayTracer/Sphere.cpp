#include "Sphere.h"


Sphere::Sphere(Vector3 _center, float _radius, Material * _material) {
	center = _center;
	radius = _radius;
	material = _material;
}


Sphere::Sphere(Vector3 _center, float _radius, Material * _material, bool _shadowed, bool _reflective, bool _refractive) {
	center = _center;
	radius = _radius;
	material = _material;
	shadowed = _shadowed;
	reflective = _reflective;
	refractive = _refractive;
}


Sphere::~Sphere() { 
	material = NULL;
}


bool Sphere::isShadowed() {
	return shadowed;
}


bool Sphere::isReflective() {
	return reflective;
}


bool Sphere::isRefractive() {
	return refractive;
}


bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) {
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) {
		x0 = x1 = -0.5f * b / a;
	}
	else {
		float q = (b > 0) ? -0.5f * (b + sqrt(discr)) : -0.5f * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	return true;
}


bool Sphere::intersect(const Ray &ray, float &t_near, float &t_far) {
	float t0, t1;
	Vector3 L = ray.origin - center;
	float a = ray.direction * ray.direction;
	float b = 2 * (ray.direction * L);
	float c = (L * L) - (radius * radius);

	if (!solveQuadratic(a, b, c, t0, t1)) {
		return false;
	}

	if (t0 < 0 && t1 < 0) {
		return false;
	}

	t_near = (t0 < t1) ? t0 : t1;
	t_far = (t0 < t1) ? t1 : t0;
	return true;
}


Vector3 Sphere::getNormal(Vector3 &hit_point) const {
	return (hit_point - center) / radius;
}

Material * Sphere::getMaterial() {
	return material;
}