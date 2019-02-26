#include "Perspective.h"


Perspective::Perspective() {
	eye = Vector3();
	lookAt = Vector3(0.0f, 0.0f, -1.0f);
	exposure = 1.0f;
	compute_uvw();
}


Perspective::Perspective(Vector3 _eye, Vector3 _lookAt, Vector3 _up, float e) {
	eye = _eye;
	lookAt = _lookAt;
	up = _up;
	exposure = e;
	compute_uvw();
}


Perspective::~Perspective() { }


void Perspective::compute_uvw() {
	w = (eye - lookAt).normalize();
	u = (up ^ w).normalize();
	v = w ^ u;
}