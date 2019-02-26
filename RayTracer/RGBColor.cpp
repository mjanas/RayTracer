#include "RGBColor.h"


RGBColor::RGBColor() {
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;
}


RGBColor::RGBColor(float r, float g, float b) {
	red = r;
	green = g;
	blue = b;
}


RGBColor::~RGBColor() { }


RGBColor const & RGBColor::operator=(const RGBColor &other) {
	if (this != &other) {
		red = other.red;
		green = other.green;
		blue = other.blue;
	}
	return *this;
}


bool RGBColor::operator==(const RGBColor &other) const {
	return (red == other.red && green == other.green && blue == other.blue);
}


bool RGBColor::operator!=(const RGBColor &other) const {
	return !(*this == other);
}


RGBColor RGBColor::operator+(const RGBColor &other) const {
	return RGBColor(red + other.red, green + other.green, blue + other.blue);
}


RGBColor RGBColor::operator*(const float s) const {
	return RGBColor(red * s, green * s, blue * s);
}


RGBColor RGBColor::operator*(const RGBColor &other) const {
	return RGBColor(red * other.red, green * other.green, blue * other.blue);
}


RGBColor RGBColor::operator/(const float s) const {
	float inv = 1 / s;
	return RGBColor(red * inv, green * inv, blue * inv);
}


RGBColor const & RGBColor::operator+=(const RGBColor &other) {
	red += other.red; green += other.green; blue += other.blue;
	return *this;
}