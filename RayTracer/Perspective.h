#pragma once

#include "Vector3.h"

class Perspective {
public:
	Vector3 eye;
	Vector3 lookAt;
	Vector3 up;
	Vector3 u, v, w;
	float exposure;

	Perspective();
	Perspective(Vector3 _eye, Vector3 _lookAt, Vector3 _up, float e);
	~Perspective();

private:
	void compute_uvw();
};

