#include "Ray.h"


Ray::Ray() {
	origin = Vector3();
	direction = Vector3();
}


Ray::Ray(Vector3 o, Vector3 d) {
	origin = o;
	direction = d;
}


Ray::~Ray() { }


Ray const & Ray::operator=(const Ray &other) {
	if (this != &other) {
		origin = other.origin;
		direction = other.direction;
	}
	return *this;
}