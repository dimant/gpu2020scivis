#include <glm\glm.hpp>

#include "rotateAxis.h"

/// This implementation is not efficient, it is
/// written for clarity.
glm::mat4 rotateAxis(glm::vec3 position, glm::vec3 axis, float deg)
{
	glm::vec3 unitAxis = glm::normalize(axis);

	float a = unitAxis.x;
	float b = unitAxis.y;
	float c = unitAxis.z;
	float d = sqrtf(b * b + c * c);

	float rad = glm::radians(deg);
	float crad = cosf(rad);
	float srad = sinf(rad);

	if (0 == d)
	{
		return glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, crad, -srad, 0.0f,
			0.0f, srad, crad, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	glm::mat4 T = glm::mat4(
		1.0f, 0.0f, 0.0f, position.x,
		0.0f, 1.0f, 0.0f, position.y,
		0.0f, 0.0f, 1.0f, position.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 TInv = glm::mat4(
		1.0f, 0.0f, 0.0f, -position.x,
		0.0f, 1.0f, 0.0f, -position.y,
		0.0f, 0.0f, 1.0f, -position.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 Rx = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c / d, -b / d, 0.0f,
		0.0f, b / d, c / d, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 RxInv = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c / d, b / d, 0.0f,
		0.0f, -b / d, c / d, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 Ry = glm::mat4(
		d, 0.0f, -a, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		a, 0.0f, d, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 RyInv = glm::mat4(
		d, 0.0f, a, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-a, 0.0f, d, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 Rz = glm::mat4(
		crad, -srad, 0.0f, 0.0f,
		srad, crad, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return TInv * RxInv * RyInv * Rz * Ry * Rx * T;
}