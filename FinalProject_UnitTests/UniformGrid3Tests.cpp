#include "Macros.h"

#include "CppUnitTest.h"

#include "UniformGrid3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FinalProject_Tests
{
	TEST_CLASS(UniformGrid3Tests)
	{
	public:
		TEST_METHOD(numPoints_count_correct)
		{
			UniformGrid3 grid(
				4, 4, 4, 
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Assert::AreEqual((size_t) 64, grid.numPoints());
		}

		TEST_METHOD(numCells_count_correct)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Assert::AreEqual((size_t)27, grid.numCells());
		}

		TEST_METHOD(getPoint_1d_correct)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Point3 p;

			grid.getPoint(3, p);

			Assert::IsTrue(almosteq(3.0f, p.x));
			Assert::IsTrue(almosteq(0.0f, p.y));
			Assert::IsTrue(almosteq(0.0f, p.z));
		}

		TEST_METHOD(getPoint_2d_correct)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Point3 p;

			grid.getPoint(5, p);

			Assert::IsTrue(almosteq(1.0f, p.x));
			Assert::IsTrue(almosteq(1.0f, p.y));
			Assert::IsTrue(almosteq(0.0f, p.z));
		}

		TEST_METHOD(getPoint_3d_correct_111)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Point3 p;

			grid.getPoint(21, p);

			Assert::IsTrue(almosteq(1.0f, p.x));
			Assert::IsTrue(almosteq(1.0f, p.y));
			Assert::IsTrue(almosteq(1.0f, p.z));
		}

		TEST_METHOD(getPoint_3d_correct_001)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Point3 p;

			grid.getPoint(16, p);

			Assert::IsTrue(almosteq(0.0f, p.x));
			Assert::IsTrue(almosteq(0.0f, p.y));
			Assert::IsTrue(almosteq(1.0f, p.z));
		}

		TEST_METHOD(getPoint_3d_correct_121)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Point3 p;

			grid.getPoint(25, p);

			Assert::IsTrue(almosteq(1.0f, p.x));
			Assert::IsTrue(almosteq(2.0f, p.y));
			Assert::IsTrue(almosteq(1.0f, p.z));
		}
	};
}
