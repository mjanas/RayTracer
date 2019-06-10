#pragma once

#include <stdlib.h>
#include <cmath>
#include <vector>
#include <map>
#include <ostream>
#include <ctime>
#include <assert.h>
#include <algorithm>
#include <iostream>

static float kEpsilon = 0.0001f;

static float threeMax(float a, float b, float c) {
	float max = a > b ? a : b;
	return (max > c ? max : c);
}

static float threeMin(float a, float b, float c) {
	float min = a < b ? a : b;
	return (min < c ? min : c);
}

static unsigned char convertColorFromFloatToChar(float in) {
	return (unsigned char)(in * 255);
}


static void clamp1(float & f) {
	f = (f > 1.0f) ? 1.0f : (f < 0.0f) ? 0.0f : f;
}