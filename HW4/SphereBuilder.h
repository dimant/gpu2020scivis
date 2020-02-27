#ifndef SPHERE_H
#define SPHERE_H

#include <gl/glew.h>
#include <glm/glm.hpp>

#include "Model.h"

#include "ShaderState.h"

#include "VertAtt.h"

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
	SphereBuilder() :
		_data(0),
		_k(0),
		_vertices(0),
		// x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
		_material(glm::vec3(0.1f, 12.0f, 2.0f))
	{
	}

	std::shared_ptr<Model> createSphere(GLuint recursions, ShaderState & shaderState);
};

#endif