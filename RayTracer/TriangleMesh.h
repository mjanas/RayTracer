#pragma once

#include "Triangle.h"
#include "BoundingBox.h"
#include "Matrix4.h"


class TriangleMesh : public GeometricObject {
public:
	size_t vertexCount, triangleCount;
	Triangle * intersectedTriangle;

	TriangleMesh(Material * m);
	~TriangleMesh();

	bool intersect(const Ray &ray, float &t_near, float &t_far);
	Vector3 getNormal(Vector3 &hit_point) const;
	Material * getMaterial();
	BoundingBox getBoundingBox() const;
	bool isShadowed();
	bool isReflective();
	bool isRefractive();

	bool loadObj(const char * filename);

	void applyTransformation(Matrix4 &matrix);

private:
	bool shadowed, reflective, refractive;
	std::vector<Triangle *> triangles;
	BoundingBox bbox;
	Material * material;
	void computeBoundingBox();
};

