#include "Macros.h"

#include "CppUnitTest.h"

#include "polygonise.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FinalProject_Tests
{
	TEST_CLASS(PolygoniseTests)
	{
	public:
		TEST_METHOD(interp1_05)
		{
			float u = 0.0f;
			float v = 1.0f;
			float t = 0.5f;

			float r = INTERP1(u, v, t);

			Assert::IsTrue(almosteq(0.5f, r));
		}

		TEST_METHOD(interp1_33)
		{
			float u = 0.0f;
			float v = 3.0f;
			float t = 1.0f;

			float r = INTERP1(u, v, t);

			Assert::IsTrue(almosteq(0.333333f, r));
		}

		TEST_METHOD(interp1_35)
		{
			float u = 0.0f;
			float v = 10.0f;
			float t = 3.5f;

			float r = INTERP1(u, v, t);

			Assert::IsTrue(almosteq(0.35f, r));
		}

		TEST_METHOD(interp1_uneven)
		{
			float u = 1.0f;
			float v = 3.0f;
			float t = 2.2f;

			float r = INTERP1(u, v, t);

			Assert::IsTrue(almosteq(0.6f, r));
		}

		TEST_METHOD(interpolate_vertex_normal)
		{
			glm::vec3 p;
			glm::vec3 n;

			float isolevel = 0.5;

			glm::vec4 p1(0.0f, 0.0f, 0.0f, 0.0f);
			glm::vec4 p2(1.0f, 0.0f, 0.0f, 1.0f);

			glm::vec3 n1(0.0f, 1.0f, 0.0f);
			glm::vec3 n2(1.0f, 0.0f, 0.0f);
			
			interpolate(p, n, isolevel, p1, n1, p2, n2);

			Assert::IsTrue(almosteq(0.5f, p.x));
			Assert::IsTrue(almosteq(0.0f, p.y));
			Assert::IsTrue(almosteq(0.0f, p.z));

			Assert::IsTrue(almosteq(n.x, n.y));
			Assert::IsTrue(almosteq(1.0f, glm::length(n)));
		}

		TEST_METHOD(interpolate_vertex_normal_uneven)
		{
			glm::vec3 p;
			glm::vec3 n;

			float isolevel = 2.2;

			glm::vec4 p1(1.0f, 2.0f, 3.0f, 1.0f);
			glm::vec4 p2(3.0f, 4.0f, 5.0f, 3.0f);

			glm::vec3 n1(0.0f, 1.0f, 0.0f);
			glm::vec3 n2(1.0f, 0.0f, 0.0f);

			interpolate(p, n, isolevel, p1, n1, p2, n2);

			Assert::IsTrue(almosteq(2.2f, p.x));
			Assert::IsTrue(almosteq(3.2f, p.y));
			Assert::IsTrue(almosteq(4.2f, p.z));

			Assert::IsTrue(almosteq(1.0f, glm::length(n)));
		}

		TEST_METHOD(getTriangles_test)
		{
			int triTable[1][16]
			{
				{0, 1, 2, 
				 3, 4, 5, 
				 6, 7, 8, 
				 9, 10, 11, 
				 12, 13, 14, 
				-1}
			};

			glm::vec3 vertlist[15] = 
			{
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 3.0f),
				glm::vec3(0.0f, 0.0f, 4.0f),
				glm::vec3(0.0f, 0.0f, 5.0f),
				glm::vec3(0.0f, 0.0f, 6.0f),
				glm::vec3(0.0f, 0.0f, 7.0f),
				glm::vec3(0.0f, 0.0f, 8.0f),
				glm::vec3(0.0f, 0.0f, 9.0f),
				glm::vec3(0.0f, 0.0f, 10.0f),
				glm::vec3(0.0f, 0.0f, 11.0f),
				glm::vec3(0.0f, 0.0f, 12.0f),
				glm::vec3(0.0f, 0.0f, 13.0f),
				glm::vec3(0.0f, 0.0f, 14.0f),
			};

			glm::vec3 normlist[15] =
			{
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 2.0f, 0.0f),
				glm::vec3(0.0f, 3.0f, 0.0f),
				glm::vec3(0.0f, 4.0f, 0.0f),
				glm::vec3(0.0f, 5.0f, 0.0f),
				glm::vec3(0.0f, 6.0f, 0.0f),
				glm::vec3(0.0f, 7.0f, 0.0f),
				glm::vec3(0.0f, 8.0f, 0.0f),
				glm::vec3(0.0f, 9.0f, 0.0f),
				glm::vec3(0.0f, 10.0f, 0.0f),
				glm::vec3(0.0f, 11.0f, 0.0f),
				glm::vec3(0.0f, 12.0f, 0.0f),
				glm::vec3(0.0f, 13.0f, 0.0f),
				glm::vec3(0.0f, 14.0f, 0.0f),
			};

			int cubeindex = 0;

			float vertices[90];

			for (int i = 0; i < 90; i++)
			{
				vertices[i] = 90;
			}

			int nfloats = getTriangles(triTable, vertlist, normlist, cubeindex, vertices);

			Assert::AreEqual(90, nfloats);

			glm::vec3* vvert = (glm::vec3*) vertices;

			for (int i = 0; i < 15; i++)
			{
				glm::vec3 v = vvert[i * 2];
				glm::vec3 n = vvert[i * 2 + 1];

				Assert::IsTrue(almosteq((float)(i), v.z));
				Assert::IsTrue(almosteq((float)(i), n.y));
			}
		}
	};
}