#ifndef SPHERE_H
#define SPHERE_H

#include <gl/glew.h>
#include <glm/glm.hpp>

#include "Model.h"

struct VertAtt
{
	glm::vec3 vertex;
	glm::vec2 texel;
	glm::vec3 normal;
	glm::vec3 material;
};

class SphereBuilder
{
private:
	const glm::vec3 _tetrahedron[4] = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.942809f, -0.333333f),
		glm::vec3(-0.816497f, -0.471405f, -0.333333f),
		glm::vec3(0.816497f, -0.471405f, -0.333333f)
	};

	VertAtt* _data;

	GLuint _k;

	GLuint _vertices;

	glm::vec3 _material;

	void beginSphere(GLuint recursions);

	void divideTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, GLuint recursion, GLuint recursions);

	void triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int recursions);

public:
	std::shared_ptr<Model> createSphere(GLuint program, GLuint recursions);
};

#endif