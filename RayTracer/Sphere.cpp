#include "Sphere.h"


Sphere::Sphere() {
	center = Vector3();
	radius = 1.0f;
	surface_color = RGBColor();
}


Sphere::Sphere(Vector3 _center, float _radius, RGBColor _color) {
	center = _center;
	radius = _radius;
	surface_color = _color;
}


Sphere::~Sphere() { }


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


bool Sphere::intersect(const Ray &ray, float &t_near, float &t_far) const {
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


Vector3 Sphere::normal(Vector3 &hit_point) const {
	return (hit_point - center) / radius;
}


RGBColor Sphere::surfaceColor() const {
	return surface_color;
}