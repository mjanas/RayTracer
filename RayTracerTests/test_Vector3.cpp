#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Raytracer/Vector3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(test_Vector3) {
public:

	TEST_METHOD(defaultInit) {
		Vector3 v = Vector3();
		Assert::AreEqual(v.x, 0.0f);
		Assert::AreEqual(v.y, 0.0f);
		Assert::AreEqual(v.z, 0.0f);
	}

	TEST_METHOD(parameterInit) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Assert::AreEqual(v.x, 1.0f);
		Assert::AreEqual(v.y, 1.0f);
		Assert::AreEqual(v.z, 1.0f);
	}

	TEST_METHOD(objectInit) {
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 w = Vector3(v);
		Assert::AreEqual(w.x, 1.0f);
		Assert::AreEqual(w.y, 1.0f);
		Assert::AreEqual(w.z, 1.0f);
	}

	TEST_METHOD(length) {
		Vector3 v1 = Vector3(1.0f, 1.0f, 1.0f);
		Assert::AreEqual(v1.length(), sqrt(3.0f));

		Vector3 v2 = Vector3(1.0f, 2.0f, 1.0f);
		Assert::AreEqual(v2.length(), sqrt(6.0f));
	}

	TEST_METHOD(normalize) {
		Vector3 v1 = Vector3(1.0f, 1.0f, 1.0f);
		v1 = v1.normalize();
		float val = 1.0f / sqrt(3.0f);
		Vector3 t1 = Vector3(val, val, val);
		Assert::IsTrue(v1 == t1);

		Vector3 v2 = Vector3(1.0f, 2.0f, 1.0f);
		v2 = v2.normalize();
		val = 1.0f / sqrt(6.0f);
		float val2 = 2.0f / sqrt(6.0f);
		Vector3 t2 = Vector3(val, val2, val);
		Assert::IsTrue(v2 == t2);
	}

	TEST_METHOD(crossProduct) {
		Vector3 v1 = Vector3(1.0f, 1.0f, 0.0f);
		Vector3 v2 = Vector3(0.0f, 1.0f, 1.0f);

		Vector3 cross = v1 ^ v2;
		Assert::AreEqual(cross.x, 1.0f);
		Assert::AreEqual(cross.y, -1.0f);
		Assert::AreEqual(cross.z, 1.0f);
	}

	TEST_METHOD(lessThan) {
		Vector3 v1 = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 v2 = Vector3(1.0f, 1.0f, 1.0f);
		Assert::IsTrue(v1 < v2);
		Assert::IsFalse(v2 < v1);
	}

	TEST_METHOD(greaterThan) {
		Vector3 v1 = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 v2 = Vector3(1.0f, 1.0f, 1.0f);
		Assert::IsFalse(v1 > v2);
		Assert::IsTrue(v2 > v1);
	}

	TEST_METHOD(addition) {
		Vector3 v1 = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 v2 = Vector3(2.0f, 2.0f, 2.0f);
		Vector3 v3 = v1 + v2;
		Assert::AreEqual(v3.x, 3.0f);
		Assert::AreEqual(v3.y, 3.0f);
		Assert::AreEqual(v3.z, 3.0f);
	}

	TEST_METHOD(subtraction) {
		Vector3 v1 = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 v2 = Vector3(2.0f, 2.0f, 2.0f);
		Vector3 v3 = v2 - v1;
		Assert::AreEqual(v3.x, 1.0f);
		Assert::AreEqual(v3.y, 1.0f);
		Assert::AreEqual(v3.z, 1.0f);
	}

	TEST_METHOD(dotProduct) {
		Vector3 v1 = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 v2 = Vector3(2.0f, 2.0f, 2.0f);
		double d = v1 * v2;
		Assert::AreEqual(d, 6.0);
	}
};