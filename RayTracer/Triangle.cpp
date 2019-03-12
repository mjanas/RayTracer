#include "Triangle.h"


Triangle::Triangle(Vector3 _a, Vector3 _b, Vector3 _c, Material * m) {
	a = _a;
	b = _b;
	c = _c;
	material = m;
	computeNormal();
}


Triangle::~Triangle() {
	material = NULL;
}


void Triangle::computeNormal() {
	normal = ((b - a) ^ (c - a)).normalize();
}


bool Triangle::intersect(const Ray &ray, float &t_near, float &t_far) {
	Vector3 ab = a - b;
	Vector3 ac = a - c;
	Vector3 ar = a - ray.origin;

	float f1 = ac.y * ray.direction.z - ray.direction.y * ac.z;
	float f2 = ar.y * ray.direction.z - ray.direction.y * ar.z;
	float f3 = ac.y * ar.z - ar.y * ac.z;
	float f4 = ray.direction.y * ab.z - ab.y * ray.direction.z;
	float f5 = ab.y * ac.z - ac.y * ab.z;

	float inv_denom = 1.0f / (ab.x * f1 + ac.x * f4 + ray.direction.x * f5);
	
	float beta = (ar.x * f1 - ac.x * f2 - ray.direction.x * f3) * inv_denom;
	if (beta < 0.0f)
		return false;
	
	float r = ab.y * ar.z - ar.y * ab.z;
	float gamma = (ab.x * f2 + ar.x * f4 + ray.direction.x * r) * inv_denom;
	if (gamma < 0.0f)
		return false;
	if (beta + gamma > 1.0f)
		return false;
	
	float t = (ab.x * f3 - ac.x * r + ar.x * f5) * inv_denom;
	if (t < 0.0001f)
		return false;
	
	t_near = t;
	return true;
}


Vector3 Triangle::getNormal(Vector3 &hit_point) const {
	return normal;
}


Material * Triangle::getMaterial() {
	return material;
}