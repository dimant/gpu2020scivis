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

		TEST_METHOD(getPoint_3d_correct_last)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Point3 p;
			size_t last = grid.numPoints() - 1;
			grid.getPoint(last, p);

			Assert::IsTrue(almosteq(3.0f, p.x));
			Assert::IsTrue(almosteq(3.0f, p.y));
			Assert::IsTrue(almosteq(3.0f, p.z));
		}

		TEST_METHOD(getCell_correct_0)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Cell3 cell;

			grid.getCell(0, cell);

			Assert::AreEqual((size_t)0, cell.v0);
			Assert::AreEqual((size_t)1, cell.v1);
			Assert::AreEqual((size_t)17, cell.v2);
			Assert::AreEqual((size_t)16, cell.v3);

			Assert::AreEqual((size_t)4, cell.v4);
			Assert::AreEqual((size_t)5, cell.v5);
			Assert::AreEqual((size_t)21, cell.v6);
			Assert::AreEqual((size_t)20, cell.v7);
		}

		TEST_METHOD(getCell_correct_13)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			Cell3 cell;

			grid.getCell(13, cell);

			Assert::AreEqual((size_t)21, cell.v0);
		}

		TEST_METHOD(getCell_correct_last)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			size_t last = grid.numCells() - 1;

			Cell3 cell;

			grid.getCell(last, cell);

			Assert::AreEqual((size_t)grid.numPoints() - 1, cell.v6);
		}

		TEST_METHOD(getVertex_sample_matches)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			float idx = 0.0f;
			auto func = [idx](float, float, float) mutable { return idx++; };

			grid.sample(func);

			glm::vec4 v;
			grid.getVertex(23, v);

			Assert::IsTrue(almosteq(23.0f, v.w));
		}

		TEST_METHOD(getCube_sample_matches)
		{
			UniformGrid3 grid(
				4, 4, 4,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f));

			float idx = 0.0f;
			auto func = [idx](float, float, float) mutable { return idx++; };

			grid.sample(func);

			Cube cube;
			grid.getCube(15, cube);

			Cell3 cell;
			grid.getCell(15, cell);

			Assert::IsTrue(almosteq((float)cell.v0, cube.v0.w));
			Assert::IsTrue(almosteq((float)cell.v1, cube.v1.w));
			Assert::IsTrue(almosteq((float)cell.v2, cube.v2.w));
			Assert::IsTrue(almosteq((float)cell.v3, cube.v3.w));

			Assert::IsTrue(almosteq((float)cell.v4, cube.v4.w));
			Assert::IsTrue(almosteq((float)cell.v5, cube.v5.w));
			Assert::IsTrue(almosteq((float)cell.v6, cube.v6.w));
			Assert::IsTrue(almosteq((float)cell.v7, cube.v7.w));
		}
	};
}
