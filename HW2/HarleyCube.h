#ifndef HARLEYCUBE_H
#define HARLEYCUBE_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"

class HarleyCube : public Transformable
{
private:
	const GLuint _program;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	GLuint _texture;

	void initVao(const GLuint & program);

public:
	HarleyCube(const GLuint program) : _program(program), _model(glm::mat4(1.0f))
	{}

	void transform(Transform t);

	void init();

	void draw();

	void destroy();
};

#endif
