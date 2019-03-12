#include "DiffuseShader.h"


DiffuseShader::DiffuseShader(float ka, float kd, RGBColor sc) {
	ambient = ka;
	diffuse = kd;
	source_color = sc;
}


DiffuseShader::~DiffuseShader() { }


RGBColor DiffuseShader::surfaceColor(Vector3 &hit_point, Vector3 &normal, Vector3 &view, std::vector<Light *> lights) const {
	return surfaceColor(hit_point, normal, lights);
}


RGBColor DiffuseShader::surfaceColor(Vector3 &hit_point, Vector3 &normal, std::vector<Light *> lights) const {
	RGBColor output;
	float avg_red = 0.0f;
	float avg_green = 0.0f;
	float avg_blue = 0.0f;

	for (size_t i = 0; i < lights.size(); i++) {
		Vector3 light_vector = (lights[i]->origin - hit_point).normalize();
		float distance = light_vector.length() * light_vector.length();

		float ndotL = (light_vector * normal);
		if (ndotL < 0) {
			ndotL = 0.0;
		}
		avg_red += (ambient * source_color.red) + (diffuse * source_color.red * ndotL);
		avg_green += (ambient * source_color.green) + (diffuse * source_color.green * ndotL);
		avg_blue += (ambient * source_color.blue) + (diffuse * source_color.blue * ndotL);
	}

	output.red = avg_red;
	output.green = avg_green;
	output.blue = avg_blue;
	return output;
}
