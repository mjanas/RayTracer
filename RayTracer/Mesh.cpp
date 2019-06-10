#include "Mesh.h"


Mesh::Mesh(Material * m) { 
	triangles = std::vector<Triangle *>();
	vertexCount = 0;
	triangleCount = 0;
	material = m;
	intersectedTriangle = NULL;
	shadowed = false;
	reflective = false;
	refractive = false;
}


Mesh::~Mesh() { 
	triangles.clear();
	vertexCount = 0;
	triangleCount = 0;
	intersectedTriangle = NULL;
}


bool Mesh::intersect(const Ray &ray, float &t_near, float &t_far) {
	if (!bbox.intersect(ray, t_near, t_far)) {
		return false;
	}

	float best_t_near = INFINITY;
	for (size_t i = 0; i < triangleCount; i++) {
		if (triangles[i]->intersect(ray, t_near, t_far)) {
			if (t_near < best_t_near) {
				best_t_near = t_near;
				intersectedTriangle = triangles[i];
			}
		}
	}
	return (intersectedTriangle != NULL);
}



Vector3 Mesh::getNormal(Vector3 &hit_point) const {
	return intersectedTriangle->normal;
}



Material * Mesh::getMaterial() {
	return material;
}



BoundingBox Mesh::getBoundingBox() const {
	return bbox;
}


bool Mesh::isShadowed() {
	return shadowed;
}

bool Mesh::isReflective() {
	return reflective;
}

bool Mesh::isRefractive() {
	return refractive;
}


void Mesh::computeBoundingBox() {
	float x_min = INFINITY;
	float y_min = INFINITY;
	float z_min = INFINITY;
	float x_max = -INFINITY;
	float y_max = -INFINITY;
	float z_max = -INFINITY;

	for (size_t i = 0; i < triangleCount; i++) {
		float minX = threeMin(triangles[i]->a.x, triangles[i]->b.x, triangles[i]->c.x);
		float minY = threeMin(triangles[i]->a.y, triangles[i]->b.y, triangles[i]->c.y);
		float minZ = threeMin(triangles[i]->a.z, triangles[i]->b.z, triangles[i]->c.z);

		float maxX = threeMax(triangles[i]->a.x, triangles[i]->b.x, triangles[i]->c.x);
		float maxY = threeMax(triangles[i]->a.y, triangles[i]->b.y, triangles[i]->c.y);
		float maxZ = threeMax(triangles[i]->a.z, triangles[i]->b.z, triangles[i]->c.z);

		x_min = (x_min < minX) ? x_min : minX;
		y_min = (y_min < minY) ? y_min : minY;
		z_min = (z_min < minZ) ? z_min : minZ;

		x_max = (x_max > maxX) ? x_max : maxX;
		y_max = (y_max > maxY) ? y_max : maxY;
		z_max = (z_max > maxZ) ? z_max : maxZ;
	}

	bbox = BoundingBox(Vector3(x_min, y_min, z_min), Vector3(x_max, y_max, z_max));
}


bool Mesh::loadObj(const char * filename) {
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

	float x_min = INFINITY;
	float y_min = INFINITY;
	float z_min = INFINITY;
	float x_max = -INFINITY;
	float y_max = -INFINITY;
	float z_max = -INFINITY;

	for (unsigned int i = 0; i < vertexIndices.size() - 2; i += 3) {
		Vector3 v0 = tempVertices[vertexIndices[i] - 1];
		Vector3 v1 = tempVertices[vertexIndices[i + 1] - 1];
		Vector3 v2 = tempVertices[vertexIndices[i + 2] - 1];
		Triangle * t = new Triangle(v0, v1, v2, material);
		triangles.push_back(t);

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

	triangleCount = triangles.size();
	bbox = BoundingBox(Vector3(x_min, y_min, z_min), Vector3(x_max, y_max, z_max));

	return true;
}