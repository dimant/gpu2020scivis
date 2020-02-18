#ifndef VERTATT_H
#define VERTATT_H

#include <glm\glm.hpp>

struct VertAtt
{
	glm::vec3 vertex;
	glm::vec2 texel;
	glm::vec3 normal;
	glm::vec3 material;

	VertAtt()
	{}

	VertAtt(glm::vec3 v, glm::vec2 t, glm::vec3 n, glm::vec3 m) :
		vertex(v), texel(t), normal(n), material(m)
	{}
};

#endif
