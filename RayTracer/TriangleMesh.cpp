#include "TriangleMesh.h"


TriangleMesh::TriangleMesh(Material * m) {
	material = m;
	triangles = std::vector<Triangle *>();
	intersectedTriangle = NULL;
	shadowed = false;
	reflective = false;
	refractive = false;
}


TriangleMesh::~TriangleMesh() {
	triangles.clear();
	material = NULL;
	intersectedTriangle = NULL;
}


bool TriangleMesh::isShadowed() {
	return shadowed;
}


bool TriangleMesh::isReflective() {
	return reflective;
}


bool TriangleMesh::isRefractive() {
	return refractive;
}


Vector3 TriangleMesh::getNormal(Vector3 &hit_point) const {
	return intersectedTriangle->getNormal(hit_point);
}


Material * TriangleMesh::getMaterial() {
	return material;
}


BoundingBox TriangleMesh::getBoundingBox() const {
	return bbox;
}


void TriangleMesh::computeBoundingBox() {
	float x_min = INFINITY;
	float y_min = INFINITY;
	float z_min = INFINITY;
	float x_max = -INFINITY;
	float y_max = -INFINITY;
	float z_max = -INFINITY;

	for (unsigned int i = 0; i < triangles.size() - 2; i += 3) {
		Triangle * t = triangles[i];

		float minX = threeMin(t->a.x, t->b.x, t->c.x);
		float minY = threeMin(t->a.y, t->b.y, t->c.y);
		float minZ = threeMin(t->a.z, t->b.z, t->c.z);

		float maxX = threeMax(t->a.x, t->b.x, t->c.x);
		float maxY = threeMax(t->a.y, t->b.y, t->c.y);
		float maxZ = threeMax(t->a.z, t->b.z, t->c.z);

		x_min = (x_min < minX) ? x_min : minX;
		y_min = (y_min < minY) ? y_min : minY;
		z_min = (z_min < minZ) ? z_min : minZ;

		x_max = (x_max > maxX) ? x_max : maxX;
		y_max = (y_max > maxY) ? y_max : maxY;
		z_max = (z_max > maxZ) ? z_max : maxZ;
	}

	bbox = BoundingBox(Vector3(x_min, y_min, z_min), Vector3(x_max, y_max, z_max));
}


void TriangleMesh::applyTransformation(Matrix4 &matrix) {
	for (int i = 0; i < triangles.size(); i++) {
		Vector3 a = triangles[i]->a;
		Vector3 b = triangles[i]->b;
		Vector3 c = triangles[i]->c;

		Vector3 new_a, new_b, new_c;

		matrix.multVecMatrix(a, new_a);
		matrix.multVecMatrix(b, new_b);
		matrix.multVecMatrix(c, new_c);

		triangles[i]->a = new_a;
		triangles[i]->b = new_b;
		triangles[i]->c = new_c;
	}
}


bool TriangleMesh::intersect(const Ray &ray, float &t_near, float &t_far) {
	float best_t_near = INFINITY;
	intersectedTriangle = NULL;

	if (!bbox.intersect(ray, t_near, t_far)) {
		return false;
	}

	for (unsigned int i = 0; i < triangles.size(); i++) {
		if (triangles[i]->intersect(ray, t_near, t_far) && (t_near < best_t_near)) {
			best_t_near = t_near;
			intersectedTriangle = triangles[i];
		}
	}
	return (intersectedTriangle != NULL);
}


bool TriangleMesh::loadObj(const char * filename) {
	std::vector<unsigned int> vertexIndices;
	std::vector<Vector3> tempVertices;

	FILE * file = fopen(filename, "r");
	if (file == NULL) {
		printf("ERROR: Cannot open file %s\n", filename);
		return false;
	}

	char lineHeader[128];
	while (fscanf(file, "%s", lineHeader) != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			Vector3 input;
			fscanf(file, "%f %f %f\n", &input.x, &input.y, &input.z);
			tempVertices.push_back(input);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3];
			int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			if (matches != 3) {
				printf("ERROR: Expected 3 values with f tag, got %d values\n", matches);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

		}
		else if (strcmp(lineHeader, "#") == 0) {
			printf("Comment\n");
		}
		else {
			printf("ERROR: Unrecognized header '%s'\n", lineHeader);
			return false;
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size() - 2; i += 3) {
		Vector3 v0 = tempVertices[vertexIndices[i] - 1];
		Vector3 v1 = tempVertices[vertexIndices[i + 1] - 1];
		Vector3 v2 = tempVertices[vertexIndices[i + 2] - 1];
		Triangle * t = new Triangle(v0, v1, v2, material);
		triangles.push_back(t);
	}
	triangleCount = triangles.size();

	return true;
}