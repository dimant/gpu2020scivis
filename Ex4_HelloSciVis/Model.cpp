#include <shaderlib.h>

#include "Model.h"

void Model::initVao(const GLuint & program)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _ndata, _data, GL_STATIC_DRAW);

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

void Model::transform(Transform t)
{
	_model = t(_model);
}

void Model::init()
{
	if (GL_FALSE == loadTexture(_texture, _textureName))
	{
		throw "Could not load HarleyCube texture.";
	}

	initVao(_program);

	if (GL_FALSE == setMat4(_program, _model, "mModel"))
	{
		throw "Could not set model HarleyCube matrix.";
	}
}

void Model::draw()
{
	setMat4(_program, _model, "mModel");
	glBindTexture(GL_TEXTURE_2D, _texture);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _ndata);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	setMat4(_program, glm::mat4(), "mModel");
}

void Model::destroy()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

