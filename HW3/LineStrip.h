#ifndef LINESTRIP_H
#define LINESTRIP_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"


class LineStrip : public Transformable
{
	void* _data;

	size_t _ndata;

	const GLuint _program;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	void initVao(const GLuint & program);

public:
	LineStrip(GLuint program, size_t ndata, void* data, const char* textureName) :
		_program(program),
		_ndata(ndata),
		_data(data),
		_model(glm::mat4(1.0f))
	{}

	virtual void transform(Transform t);

	void init();

	void draw();

	void destroy();
};

#endif
