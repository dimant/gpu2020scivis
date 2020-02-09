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
bool diagonal(const Quad & quad)
{
	return		min(minAngle(quad.v1, quad.v2, quad.v3), minAngle(quad.v1, quad.v3, quad.v4)) 
			>	min(minAngle(quad.v1, quad.v2, quad.v4), minAngle(quad.v2, quad.v3, quad.v4));
}

inline void copyVertex(const glm::vec3 & v, float* data)
{
	data[0] = v.x;
	data[1] = v.y;
	data[2] = v.z;
}

// given a Quad, subdivide into 2 tris along optimal diagonal, 
// write tris to data and return number of written floats
size_t triangulate(const Quad & quad, float * data)
{
	float * cursor = data;
	bool diag = diagonal(quad);

	if (diag)
	{
		copyVertex(quad.v1, cursor); cursor += 3;
		copyVertex(quad.v2, cursor); cursor += 3;
		copyVertex(quad.v3, cursor); cursor += 3;

		copyVertex(quad.v1, cursor); cursor += 3;
		copyVertex(quad.v3, cursor); cursor += 3;
		copyVertex(quad.v4, cursor); cursor += 3;
	}
	else
	{
		copyVertex(quad.v1, cursor); cursor += 3;
		copyVertex(quad.v2, cursor); cursor += 3;
		copyVertex(quad.v4, cursor); cursor += 3;

		copyVertex(quad.v2, cursor); cursor += 3;
		copyVertex(quad.v3, cursor); cursor += 3;
		copyVertex(quad.v4, cursor); cursor += 3;
	}

	return cursor - data;
}
