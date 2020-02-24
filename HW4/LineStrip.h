#ifndef LINESTRIP_H
#define LINESTRIP_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"

#include "ShaderState.h"

class LineStrip : public Transformable
{
	void* _data;

	size_t _ndata;

	GLuint _lineWidth;

	const GLuint _program;

	ShaderState & _shaderState;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	void initVao(const GLuint & program);

public:
	LineStrip(GLuint program, size_t ndata, void* data, ShaderState & shaderState) :
		_program(program),
		_shaderState(shaderState),
		_ndata(ndata),
		_data(data),
		_model(glm::mat4(1.0f)),
		_lineWidth(5)
	{}

	virtual void transform(Transform t);

	void reset(size_t ndata, void* data);

	void init();

	void draw();

	void destroy();
};

#endif
