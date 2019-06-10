#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Raytracer/GeometricObject.cpp"
#include "../Raytracer/Plane.cpp"
#include "../Raytracer/Sphere.cpp"
#include "../Raytracer/RGBColor.cpp"
#include "../Raytracer/Triangle.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(test_Plane) {
public:
	TEST_METHOD(initialization_custom1) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Plane p = Plane(v, v, NULL);
		Assert::IsTrue(p.origin == v);
		Assert::IsTrue(p.normal == v);
	}

	TEST_METHOD(initialization_custom2) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 w = Vector3(v);
		Plane p1 = Plane(v, v, NULL);
		Plane p2 = Plane(p1);
		Assert::IsTrue(p2.origin == p1.origin);
		Assert::IsTrue(p2.normal == p1.normal);
	}

	TEST_METHOD(intersection) {
		Vector3 o = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 n = Vector3(0.0f, 0.0f, 1.0f);
		Plane p = Plane(o, n, NULL);
		Ray r = Ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
		float t_near, t_far;
		Assert::IsTrue(p.intersect(r, t_near, t_far));
	}
};

TEST_CLASS(test_Sphere) {
public:
	TEST_METHOD(initialization_custom1) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Sphere s = Sphere(v, 25.0f, NULL);
		Assert::IsTrue(s.center == v);
		Assert::IsTrue(s.radius == 25.0f);
	}

	TEST_METHOD(initialization_custom2) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Sphere s1 = Sphere(v, 4.0f, NULL);
		Sphere s2 = Sphere(s1);
		Assert::IsTrue(s2.center == s1.center);
		Assert::IsTrue(s2.radius == s1.radius);
	}

	TEST_METHOD(getNormal) {
		Sphere s = Sphere(Vector3(), 1.0f, NULL);
		Vector3 point = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 normal = s.getNormal(point);
		Vector3 expected = Vector3(1.0f, 1.0f, 1.0f);
		Assert::AreEqual(normal.x, expected.x);
		Assert::AreEqual(normal.y, expected.y);
		Assert::AreEqual(normal.z, expected.z);
	}

	TEST_METHOD(boundingBoxInitialization) {
		Sphere s = Sphere(Vector3(), 1.0f, NULL);
		Vector3 min = Vector3(-1.0f, -1.0f, -1.0f);
		Vector3 max = Vector3(1.0f, 1.0f, 1.0f);
		Assert::IsTrue(false);
		/**Assert::AreEqual(s.bbox.getMinX(), min.x);
		Assert::AreEqual(s.bbox.getMinY(), min.y);
		Assert::AreEqual(s.bbox.getMinZ(), min.z);
		Assert::AreEqual(s.bbox.getMaxX(), max.x);
		Assert::AreEqual(s.bbox.getMaxY(), max.y);
		Assert::AreEqual(s.bbox.getMaxZ(), max.z);**/
	}

	TEST_METHOD(intersection) {
		Sphere s = Sphere(Vector3(), 1.0f, NULL);
		Ray ray = Ray(Vector3(0.0f, 0.0f, 10.0f), Vector3(0.0f, 0.0f, -1.0f));
		float t_near, t_far;
		Assert::IsTrue(s.intersect(ray, t_near, t_far));

		Ray ray2 = Ray(Vector3(10.0f, 10.0f, 10.0f), Vector3(-1.0f, -1.0f, -1.0f));
		Assert::IsTrue(s.intersect(ray, t_near, t_far));
	}
};

TEST_CLASS(test_Triangle) {
public:
	TEST_METHOD(initialization_custom1) {
		Vector3 a = Vector3(1.0f, 1.0f, 1.0f);
		Triangle t = Triangle(a, a, a, NULL);
		Assert::IsTrue(t.a == a);
		Assert::IsTrue(t.b == a);
		Assert::IsTrue(t.c == a);
	}

	TEST_METHOD(initialization_custom2) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Triangle t1 = Triangle(v, v, v, NULL);
		Triangle t2 = Triangle(t1);
		Assert::IsTrue(t1.a == t2.a);
		Assert::IsTrue(t1.b == t2.b);
		Assert::IsTrue(t1.c == t2.c);
	}

	TEST_METHOD(getNormal) {
		Vector3 a = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 b = Vector3(0.0f, 1.0f, 1.0f);
		Vector3 c = Vector3(1.0f, 1.0f, 1.0f);
		Triangle t = Triangle(a, b, c, NULL);
		Vector3 n = Vector3(0.0f, 1.0f, -1.0f);
		Vector3 nn = n.normalize();
		Assert::AreEqual(t.normal.x, nn.x);
		Assert::AreEqual(t.normal.y, nn.y);
		Assert::AreEqual(t.normal.z, nn.z);
	}

	TEST_METHOD(intersection) {
		Vector3 a = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 b = Vector3(0.0f, 1.0f, 1.0f);
		Vector3 c = Vector3(1.0f, 1.0f, 1.0f);
		Triangle t = Triangle(a, b, c, NULL);
		float t_min, t_max;
		Ray ray = Ray(Vector3(0.5f, 0.5f, 2.0f), Vector3(0.0f, 0.0f, -1.0f));
		Assert::IsTrue(t.intersect(ray, t_min, t_max));
	}
};