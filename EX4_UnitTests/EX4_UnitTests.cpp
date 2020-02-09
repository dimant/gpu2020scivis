#include "CppUnitTest.h"

#include <memory>

#include <glm\glm.hpp>

#include "triangulation.h"

#define EPSILON 0.00001
#define almosteq(x, y) (abs(x - y) <= EPSILON * max3(1.0f, abs(x), abs(y)))

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EX4UntiTests
{
	TEST_CLASS(EX4UnitTests)
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
			glm::vec3 v1(0.0f, 0.0f, 0.0f);
			glm::vec3 v2(1.0f, 0.0f, 0.0f);
			glm::vec3 v3(5.0f, 5.0f, 0.0f);
			glm::vec3 v4(0.0f, 1.0f, 0.0f);

			bool result = diagonal(v1, v2, v3, v4);

			Assert::IsFalse(result);
		}

		TEST_METHOD(Diagnoal_Second)
		{
			glm::vec3 v1(0.0f, 0.0f, 0.0f);
			glm::vec3 v2(1.0f, 0.0f, 0.0f);
			glm::vec3 v3(1.0f, 1.0f, 0.0f);
			glm::vec3 v4(-5.0f, 5.0f, 0.0f);

			bool result = diagonal(v1, v2, v3, v4);

			Assert::IsTrue(result);
		}
	};
}
