#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Raytracer/Ray.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(test_Ray) {
public:
	TEST_METHOD(init_default) {
		Ray r = Ray();
		Vector3 v = Vector3();
		Assert::IsTrue(r.origin == v);
		Assert::IsTrue(r.direction == v);
	}

	TEST_METHOD(init_customParams) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Ray r = Ray(v, v);
		Assert::IsTrue(r.origin == v);
		Assert::IsTrue(r.direction == v);
	}

	TEST_METHOD(init_customObject) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 w = Vector3(v);
		Ray r = Ray(v, v);
		Ray r2 = Ray(r);
		Assert::IsTrue(r2.origin == r.origin);
		Assert::IsTrue(r2.direction == r.direction);
	}
};
