#include "CppUnitTest.h"

#include <memory>

#include <glm\glm.hpp>

#include "Macros.h"

#include "UniformGrid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EX4UnitTests
{
	TEST_CLASS(UniformGridTests)
	{
	public:

		TEST_METHOD(Sample_values)
		{
			UniformGrid grid(5, 5, 0, 0, 5, 5);

			auto func = [](float x, float y) { return x + y; };

			grid.sample(func);

			Assert::IsTrue(almosteq(0.0f, grid.pointScalars().getC0Scalar(0)));
			Assert::IsTrue(almosteq(5.0f, grid.pointScalars().getC0Scalar(4)));
			Assert::IsTrue(almosteq(10.0f, grid.pointScalars().getC0Scalar(24)));
		}

		TEST_METHOD(getVertex_z)
		{
			UniformGrid grid(5, 5, 0, 0, 5, 5);

			auto func = [](float x, float y) { return x + y; };

			grid.sample(func);

			glm::vec3 v;

			grid.getVertex(0, v);
			Assert::IsTrue(almosteq(0.0f, v.x));
			Assert::IsTrue(almosteq(0.0f, v.y));
			Assert::IsTrue(almosteq(0.0f, v.z));

			grid.getVertex(4, v);
			Assert::IsTrue(almosteq(5.0f, v.x));
			Assert::IsTrue(almosteq(0.0f, v.y));
			Assert::IsTrue(almosteq(5.0f, v.z));

			grid.getVertex(24, v);
			Assert::IsTrue(almosteq(5.0f, v.x));
			Assert::IsTrue(almosteq(5.0f, v.y));
			Assert::IsTrue(almosteq(10.0f, v.z));
		}

		TEST_METHOD(getTris_data)
		{
			UniformGrid grid(5, 5, 0, 0, 5, 5);

			auto func = [](float x, float y) { return x + y; };

			grid.sample(func);

			auto nVerts = grid.numVertices();

			Assert::AreEqual((size_t)96, nVerts);

			float* data = new float[nVerts * 3];

			grid.getTris(data);

			size_t i = 0;
			Assert::IsTrue(almosteq(0.0f, data[i]));
			Assert::IsTrue(almosteq(0.0f, data[i + 1]));
			Assert::IsTrue(almosteq(0.0f, data[i + 2]));
		}
	};
}
