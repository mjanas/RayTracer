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

static float threeMax(float a, float b, float c) {
	float max = a > b ? a : b;
	return (max > c ? max : c);
}

static float threeMin(float a, float b, float c) {
	float min = a < b ? a : b;
	return (min < c ? min : c);
}