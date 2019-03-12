#include "BoundingBox.h"


BoundingBox::BoundingBox() {
	min = Vector3();
	max = Vector3();
}


BoundingBox::BoundingBox(Vector3 _min, Vector3 _max) {
	min = _min;
	max = _max;
}


BoundingBox::~BoundingBox() { }


bool BoundingBox::intersect(const Ray &ray, float &t_near, float &t_far) const {
	if (ray.origin < min || ray.origin > max) {
		return false;
	}
	return (((max - min) - ray.origin) * ray.direction > 0.0f);
}