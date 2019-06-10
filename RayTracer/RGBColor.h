#pragma once


class RGBColor {
public:
	float red, green, blue;

	RGBColor();
	RGBColor(float r, float g, float b);
	~RGBColor();

	RGBColor const & operator=(const RGBColor &other);
	bool operator==(const RGBColor &other) const;
	bool operator!=(const RGBColor &other) const;
	RGBColor operator+(const RGBColor &other) const;
	RGBColor operator*(const float s) const;
	RGBColor operator/(const float s) const;
	RGBColor operator*(const RGBColor &other) const;
	RGBColor const & operator+=(const RGBColor &other);
};