#include "LineStrip.h"
#include <shaderlib.h>

void LineStrip::initVao(const GLuint & program)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _ndata, _data, GL_STATIC_DRAW);

	// 3 floats for x, y, z coordinates
	GLuint locPosition = glGetAttribLocation(program, "in_vPosition");
	glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(locPosition);
}

void LineStrip::transform(Transform t)
{
	_model = t(_model);
}

void LineStrip::init()
{
	initVao(_program);

	if (GL_FALSE == setMat4(_program, _model, "mModel"))
	{
		throw "Could not set LineStrip matrix.";
	}
}

void LineStrip::draw()
{
	setMat4(_program, _model, "mModel");
	glBindVertexArray(_vao);
	glDrawArrays(GL_LINE_STRIP, 0, _ndata);
	glBindVertexArray(0);
	setMat4(_program, glm::mat4(), "mModel");
}

void LineStrip::destroy()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

