#pragma once

#include "Triangle.h"
#include "BoundingBox.h"

class Mesh : public GeometricObject {
public:

	std::vector<Triangle *> triangles;
	int vertexCount, triangleCount;
	BoundingBox bbox;
	Triangle * intersectedTriangle;
	Material * material;

	Mesh(Material * m);
	~Mesh();

	bool intersect(const Ray &ray, float &t_near, float &t_far);
	Vector3 getNormal(Vector3 &hit_point) const;
	Material * getMaterial();
	BoundingBox getBoundingBox() const;

	bool loadObj(const char * filename);

private:
	void computeBoundingBox();
};

