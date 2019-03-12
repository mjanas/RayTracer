#include "SpecularShader.h"


SpecularShader::SpecularShader() {
	ambient = 1.0f;
	diffuse = 1.0f;
	specular = 1.0f;
	exponent = 16.0f;
	source_color = RGBColor();
}


SpecularShader::SpecularShader(float ka, float kd, float ks, float e, RGBColor sc) {
	ambient = ka;
	diffuse = kd;
	specular = ks;
	exponent = e;
	source_color = sc;
}


SpecularShader::~SpecularShader() { }


RGBColor SpecularShader::surfaceColor(Vector3 &hit_point, Vector3 &normal, std::vector<Light *> lights) const {
	return RGBColor(1.0f, 1.0f, 1.0f);
}


RGBColor SpecularShader::surfaceColor(Vector3 &hit_point, Vector3 &normal, Vector3 &view, std::vector<Light *> lights) const {
	Vector3 normalized_normal = normal.normalize();
	Vector3 dir = (-view).normalize();

	RGBColor output;
	float avg_red = 0.0f;
	float avg_green = 0.0f;
	float avg_blue = 0.0f;

	for (size_t i = 0; i < lights.size(); i++) {
		Vector3 light_vector = (lights[i]->origin - hit_point).normalize();
		float distance = light_vector.length() * light_vector.length();

		float ndotL = (light_vector * normal);
		if (ndotL < 0) {
			ndotL = 0.0f;
		}

		Vector3 h = (light_vector + dir).normalize();
		float ndotH = normalized_normal * h;
		if (ndotH < 0) {
			ndotH = 0.0f;
		}
		ndotH = pow(ndotH, exponent);

		avg_red += source_color.red * ambient + (diffuse * source_color.red * ndotL) + (specular * lights[i]->color.red * ndotH);
		avg_green += source_color.green * ambient + (diffuse * source_color.green * ndotL) + (specular * lights[i]->color.green * ndotH);
		avg_blue += source_color.blue * ambient + (diffuse * source_color.blue * ndotL) + (specular * lights[i]->color.blue * ndotH);
	}

	output.red = avg_red;
	output.green = avg_green;
	output.blue = avg_blue;
	return output;
}