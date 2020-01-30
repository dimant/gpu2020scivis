#ifndef SPHERE_H
#define SPHERE_H

#include <gl/glew.h>
#include <glm/glm.hpp>

#include "Transformable.h"

struct VertAtt
{
	glm::vec3 vertex;
	glm::vec2 texel;
	glm::vec3 normal;
	glm::vec4 material;
};

class Sphere : public Transformable
{
private:
	const glm::vec3 _tetrahedron[4] = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.942809f, -0.333333f),
		glm::vec3(-0.816497f, -0.471405f, -0.333333f),
		glm::vec3(0.816497f, -0.471405f, -0.333333f)
	};

	// const glm::vec4 _color = glm::vec4(0.2941f, 0.4902f, 0.8196f, 1.0f);

	const glm::vec4 _color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 _model;

	VertAtt* _data;

	GLuint _k;

	GLuint _vao;

	GLuint _vbo;

	GLuint _vertices;

	const GLuint & _program;

	GLuint _texture;

	glm::vec4 _material;

	void beginSphere(GLuint recursions);

	void divideTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, GLuint recursion, GLuint recursions);

	void triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int recursions);

	void initVao(const GLuint & program);

public:
	Sphere(const GLuint & program) : 
		_program(program),
		_data(0),
		_k(0),
		_vertices(0),
		_model(glm::mat4(1.0f)),
		// x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
		_material(glm::vec4(0.1f, 12.0f, 2.0f, 256.0f))
	{}

	virtual void transform(Transform t);

	void init(GLuint recursions);

	void draw();

	void destroy();
};

#endif