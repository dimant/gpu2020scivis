#include "LineStrip.h"
#include <shaderlib.h>

#include <iostream>
#include "VertAtt.h"

void LineStrip::initVao(const GLuint & program)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _ndata, _data, GL_DYNAMIC_DRAW);

	// 3 floats for x, y, z coordinates
	GLuint locPosition = glGetAttribLocation(program, "in_vPosition");
	glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(locPosition);

	// 2 floats for x, y texture coordinates
	GLuint locTexCoord = glGetAttribLocation(program, "in_vTexCoord");
	glVertexAttribPointer(locTexCoord, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(locTexCoord);

	// 3 floats for x, y, z vertex normals
	GLuint locNormal = glGetAttribLocation(program, "in_vNormal");
	glVertexAttribPointer(locNormal, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(locNormal);

	// 4 floats for ka, kd, ks, sh for material properties
	GLuint locMaterial = glGetAttribLocation(program, "in_vMaterial");
	glVertexAttribPointer(locMaterial, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(locMaterial);
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

void LineStrip::reset(size_t ndata, void* data)
{
	_ndata = ndata;
	delete _data;
	_data = data;

	glInvalidateBufferData(_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ndata, data);
}

void LineStrip::draw()
{
	setMat4(_program, _model, "mModel");
	glBindVertexArray(_vao);
	glLineWidth(_lineWidth);
	glDrawArrays(GL_LINES, 0, _ndata / sizeof(VertAtt));
	glLineWidth(1);
	glBindVertexArray(0);
	setMat4(_program, glm::mat4(), "mModel");
}

void LineStrip::destroy()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);

	delete _data;
}
