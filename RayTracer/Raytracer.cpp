#include "Raytracer.h"


Raytracer::Raytracer(int hres, int vres, float ps) { 
	horizontalResolution = hres;
	verticalResolution = vres;
	pixelSize = ps;
}


Raytracer::~Raytracer() { }


Vector3 Raytracer::reflect(const Vector3 & incident_dir, const Vector3 & normal_dir) {
	return incident_dir - (normal_dir * 2.0 * (incident_dir * normal_dir));
}


bool Raytracer::objectIsInShadow(const Ray &shadowRay, GeometricObject * currentObject, std::vector<GeometricObject *> &objects) {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i] != currentObject) {
			float t_near = INFINITY;
			float t_far = -INFINITY;
			if (objects[i]->intersect(shadowRay, t_near, t_far)) {
				return true;
			}
		}
	}
	return false;
}


RGBColor Raytracer::castRay(const Ray &ray, std::vector<GeometricObject *> &objects, std::vector<Light *> &lights, int depth) {
	RGBColor color = RGBColor();
	RGBColor shadowColor = RGBColor();
	RGBColor refractionColor = RGBColor();
	RGBColor reflectionColor = RGBColor();
	if (depth > 4) {
		return color;
	}

	float t_near, t_far;
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->intersect(ray, t_near, t_far)) {
			Vector3 hitPoint = ray.origin + ray.direction * t_near;
			Vector3 normal = objects[i]->getNormal(hitPoint);
			normal = (normal * ray.direction > 0) ? -normal : normal;
			Vector3 dir = -ray.direction;

			// Special shading condition - Shadows
			if (objects[i]->isShadowed()) {
				for (unsigned int j = 0; j < lights.size(); j++) {
					Vector3 shadow_dir = (lights[j]->origin - hitPoint).normalize();
					Vector3 shadow_origin = (ray.direction * normal < 0) ? hitPoint + (normal * kEpsilon) : hitPoint - (normal * kEpsilon);
					if (!objectIsInShadow(Ray(shadow_origin, shadow_dir), objects[i], objects)) {
						shadowColor = objects[i]->getMaterial()->surfaceColor(hitPoint, normal, dir, lights);
					}
				}
				color = color + shadowColor;
				break;
			}

			// Special shading condition - Reflective
			if (objects[i]->isReflective()) {
				float reflection_coefficient = 0.9f;
				Vector3 r = reflect(ray.direction, normal).normalize();
				Vector3 o = (ray.direction * normal < 0) ? hitPoint + (normal * kEpsilon) : hitPoint - (normal * kEpsilon);
				reflectionColor += (castRay(Ray(o, r), objects, lights, depth + 1) * reflection_coefficient);
				color = reflectionColor;
				break;
			}

			// Special shading condition - Refractive
			if (objects[i]->isRefractive()) {

			}

			// No special shading conditions
			else {
				color = objects[i]->getMaterial()->surfaceColor(hitPoint, normal, dir, lights);
			}
		}
	}
	return color;
}


void Raytracer::render(Perspective &p, std::vector<GeometricObject *> &objects, std::vector<Light *> &lights) {
	CImg<unsigned char> img(horizontalResolution, verticalResolution, 1, 3);
	img.fill(0);
	unsigned char finalColor[] = { 0, 0, 0 };

	#pragma omp parallel for num_threads(verticalResolution)
	for (int r = 0; r < verticalResolution; r++) {

		#pragma omp parallel for num_threads(horizontalResolution)
		for (int c = 0; c < horizontalResolution; c++) {
			float x = pixelSize * (c - horizontalResolution / 2.0f + 0.5f);
			float y = pixelSize * (r - verticalResolution / 2.0f + 0.5f);
			float distance = 100.0f;

			Vector3 dir = ((p.u * y) + (p.v * x) - (p.w * distance)).normalize();
			Ray ray = Ray(p.eye, dir);

			RGBColor floatColor = castRay(ray, objects, lights, 0);
			clamp1(floatColor.red); clamp1(floatColor.green); clamp1(floatColor.blue);
			finalColor[0] = convertColorFromFloatToChar(floatColor.red);
			finalColor[1] = convertColorFromFloatToChar(floatColor.green);
			finalColor[2] = convertColorFromFloatToChar(floatColor.blue);
			img.draw_point(r, c, finalColor);
		}
	}
	img.display("Render Output");
	img.normalize(0, 255);
	img.save_bmp("output.bmp");
}