#include "CppUnitTest.h"

#include <memory>

#include <glm\glm.hpp>

#include "Macros.h"

#include "triangulation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FinalProject_Tests
{
	TEST_CLASS(TriangulationTests)
	{
	public:
		
		TEST_METHOD(AlmostEq_True)
		{
			Assert::IsTrue(almosteq(3.0f, 3.000001f));
		}

		TEST_METHOD(AlmostEq_False)
		{
			Assert::IsFalse(almosteq(3.5f, 3.000001f));
		}

		TEST_METHOD(Min_ShouldReturn_A)
		{
			float result = min(1.0f, 2.0f);

			Assert::IsTrue(almosteq(result, 1.0f));
		}

		TEST_METHOD(Min2_ShouldReturn_B)
		{
			float result = min3(3.0f, 1.0f, 2.0f);

			Assert::IsTrue(almosteq(result, 1.0f));
		}

		TEST_METHOD(Max_ShouldReturn_B)
		{
			float result = max(1.0f, 2.0f);

			Assert::IsTrue(almosteq(result, 2.0f));
		}

		TEST_METHOD(Max3_ShouldReturn_A)
		{
			float result = max3(3.0f, 1.0f, 2.0f);

			Assert::IsTrue(almosteq(result, 3.0f));
		}

		TEST_METHOD(MinAngle_CorrectAngle)
		{
			glm::vec3 v1(0.0f, 0.0f, 0.0f);
			glm::vec3 v2(4.0f, 0.0f, 0.0f);
			glm::vec3 v3(0.0f, 3.0f, 0.0f);

			float a = minAngle(v1, v2, v3);

			Assert::IsTrue(almosteq(a, 0.643501f));
		}

		TEST_METHOD(Diagnoal_First)
		{
			Quad q;

			glm::vec3 v1(0.0f, 0.0f, 0.0f);
			glm::vec3 v2(1.0f, 0.0f, 0.0f);
			glm::vec3 v3(1.0f, 1.0f, 0.0f);
			glm::vec3 v4(-5.0f, 5.0f, 0.0f);

			q.v1 = v1;
			q.v2 = v2;
			q.v3 = v3;
			q.v4 = v4;

			bool result = diagonal(q);

			Assert::IsTrue(result);
		}

		TEST_METHOD(Diagnoal_Second)
		{
			Quad q;

			glm::vec3 v1(0.0f, 0.0f, 0.0f);
			glm::vec3 v2(1.0f, 0.0f, 0.0f);
			glm::vec3 v3(5.0f, 5.0f, 0.0f);
			glm::vec3 v4(0.0f, 1.0f, 0.0f);

			q.v1 = v1;
			q.v2 = v2;
			q.v3 = v3;
			q.v4 = v4;

			bool result = diagonal(q);

			Assert::IsFalse(result);
		}

		TEST_METHOD(Triangulate_First)
		{
			Quad q;

			glm::vec3 v1(0.0f, 0.0f, 0.0f);
			glm::vec3 v2(1.0f, 0.0f, 0.0f);
			glm::vec3 v3(1.0f, 1.0f, 0.0f);
			glm::vec3 v4(-5.0f, 5.0f, 0.0f);

			q.v1 = v1;
			q.v2 = v2;
			q.v3 = v3;
			q.v4 = v4;

			// three coordinates, three vertices, 2 triangles
			const size_t nTris = 3 * 3 * 2;
			float tris[nTris];

			size_t result = triangulate(q, tris);

			Assert::AreEqual(nTris, result);

			Assert::IsTrue(almosteq(tris[0], v1.x));
			Assert::IsTrue(almosteq(tris[1], v1.y));
			Assert::IsTrue(almosteq(tris[2], v1.z));

			Assert::IsTrue(almosteq(tris[3], v2.x));
			Assert::IsTrue(almosteq(tris[4], v2.y));
			Assert::IsTrue(almosteq(tris[5], v2.z));

			Assert::IsTrue(almosteq(tris[6], v3.x));
			Assert::IsTrue(almosteq(tris[7], v3.y));
			Assert::IsTrue(almosteq(tris[8], v3.z));


			Assert::IsTrue(almosteq(tris[9],  v1.x));
			Assert::IsTrue(almosteq(tris[10], v1.y));
			Assert::IsTrue(almosteq(tris[11], v1.z));

			Assert::IsTrue(almosteq(tris[12], v3.x));
			Assert::IsTrue(almosteq(tris[13], v3.y));
			Assert::IsTrue(almosteq(tris[14], v3.z));

			Assert::IsTrue(almosteq(tris[15], v4.x));
			Assert::IsTrue(almosteq(tris[16], v4.y));
			Assert::IsTrue(almosteq(tris[17], v4.z));
		}

		TEST_METHOD(Triangulate_Second)
		{
			Quad q;

			glm::vec3 v1(0.0f, 0.0f, 0.0f);
			glm::vec3 v2(1.0f, 0.0f, 0.0f);
			glm::vec3 v3(5.0f, 5.0f, 0.0f);
			glm::vec3 v4(0.0f, 1.0f, 0.0f);

			q.v1 = v1;
			q.v2 = v2;
			q.v3 = v3;
			q.v4 = v4;

			// three coordinates, three vertices, 2 triangles
			const size_t nTris = 3 * 3 * 2;
			float tris[nTris];

			size_t result = triangulate(q, tris);

			Assert::AreEqual(nTris, result);

			Assert::IsTrue(almosteq(tris[0], v1.x));
			Assert::IsTrue(almosteq(tris[1], v1.y));
			Assert::IsTrue(almosteq(tris[2], v1.z));

			Assert::IsTrue(almosteq(tris[3], v2.x));
			Assert::IsTrue(almosteq(tris[4], v2.y));
			Assert::IsTrue(almosteq(tris[5], v2.z));

			Assert::IsTrue(almosteq(tris[6], v4.x));
			Assert::IsTrue(almosteq(tris[7], v4.y));
			Assert::IsTrue(almosteq(tris[8], v4.z));


			Assert::IsTrue(almosteq(tris[9],  v2.x));
			Assert::IsTrue(almosteq(tris[10], v2.y));
			Assert::IsTrue(almosteq(tris[11], v2.z));

			Assert::IsTrue(almosteq(tris[12], v3.x));
			Assert::IsTrue(almosteq(tris[13], v3.y));
			Assert::IsTrue(almosteq(tris[14], v3.z));

			Assert::IsTrue(almosteq(tris[15], v4.x));
			Assert::IsTrue(almosteq(tris[16], v4.y));
			Assert::IsTrue(almosteq(tris[17], v4.z));
		}
	};
}
