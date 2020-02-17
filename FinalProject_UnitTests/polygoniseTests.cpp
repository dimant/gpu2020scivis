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
	};
}