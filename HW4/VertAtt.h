#ifndef VERTATT_H
#define VERTATT_H

#include <glm\glm.hpp>

struct VertAtt
{
	glm::vec3 vertex;
	float scalar;
	glm::vec2 texel;
	glm::vec3 normal;
	glm::vec3 material;
};

#endif
