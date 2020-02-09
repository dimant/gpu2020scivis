#include "triangulation.h"

#include <glm\gtx\vector_angle.inl>

float minAngle(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3)
{
	glm::vec3 s1 = glm::normalize(v2 - v1);
	glm::vec3 s2 = glm::normalize(v3 - v1);
	glm::vec3 s3 = glm::normalize(v3 - v2);

	float a1 = glm::angle(s1, s2);
	float a2 = glm::angle(-s1, s3);

	return min3(a1, a2, 180.0f - a1 - a2);
}

// returns true if v1 v3 diagonal is better, false if v2 v4 diagonal is better
bool diagonal(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3, const glm::vec3 & v4)
{
	return min(minAngle(v1, v2, v3), minAngle(v1, v3, v4)) > min(minAngle(v1, v2, v4), minAngle(v2, v3, v4));
}
