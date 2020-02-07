#include "CppUnitTest.h"

#include <memory>

#include <GL\GL.h>
#include <glm\glm.hpp>
#include <glm\gtx\vector_angle.inl>

#define max(x, y) ((x > y) ? x : y)
#define max3(x, y, z) (max(x, max(y, z)))
#define min(x, y) ((x < y) ? x : y)
#define min3(x, y, z) (min(x, min(y, z)))

#define EPSILON 0.00001
#define almosteq(x, y) (abs(x - y) <= EPSILON * max3(1.0f, abs(x), abs(y)))

inline float minAngle(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3)
{
	glm::vec3 s1 = v2 - v1;
	glm::vec3 s2 = v3 - v1;
	glm::vec3 s3 = v3 - v2;

	float a1 = glm::angle(s1, s2);
	float a2 = glm::angle(-s1, s3);

	return min3(a1, a2, 180.0f - a1 - a2);
}

// returns true if v1 v3 diagonal is better, false if v2 v4 diagonal is better
inline bool diagonal(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3, const glm::vec4 & v4)
{
	return min(minAngle(v1, v2, v3), minAngle(v1, v3, v4)) > min(minAngle(v1, v2, v4), minAngle(v2, v3, v4));
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EX4UntiTests
{
	TEST_CLASS(EX4UnitTests)
	{
	public:
		
		TEST_METHOD(AlmostEq)
		{
			Assert::IsTrue(almosteq(3.0f, 3.000001f));
		}
	};
}
