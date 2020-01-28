
#define harley_cube_v0 -1.0f, -1.0f,  1.0f,
#define harley_cube_v1  1.0f, -1.0f,  1.0f,
#define harley_cube_v2  1.0f, -1.0f, -1.0f,
#define harley_cube_v3 -1.0f, -1.0f, -1.0f,
#define harley_cube_v4 -1.0f,  1.0f,  1.0f,
#define harley_cube_v5  1.0f,  1.0f,  1.0f,
#define harley_cube_v6  1.0f,  1.0f, -1.0f,
#define harley_cube_v7 -1.0f,  1.0f, -1.0f,

#define harley_cube_n0 0.0f, 0.0f, 1.0f,
#define harley_cube_n1 1.0f, 0.0f, 0.0f,
#define harley_cube_n2 0.0f, 0.0f, -1.0f,
#define harley_cube_n3 -1.0f, 0.0f, 0.0f,
#define harley_cube_n4 0.0f, -1.0f, 0.0f,
#define harley_cube_n5 0.0f, 1.0f, 0.0f,

#define harley_cube_t0 0.0f, 0.0f,
#define harley_cube_t1 0.333f, 0.0f,
#define harley_cube_t2 0.666f, 0.0f,
#define harley_cube_t3 1.0f, 0.0f,

#define harley_cube_t4 0.0f, 0.5f,
#define harley_cube_t5 0.333f, 0.5f,
#define harley_cube_t6 0.666f, 0.5f,
#define harley_cube_t7 1.0f, 0.5f,

#define harley_cube_t8 0.0f, 1.0f,
#define harley_cube_t9 0.333f, 1.0f,
#define harley_cube_t10 0.666f, 1.0f,
#define harley_cube_t11 1.0f, 1.0f,

// vertex (x, y, z) texel (x, y) normal (x, y, z)
float harley_cube[] = {
	// face 1 front
	harley_cube_v0 harley_cube_t4 harley_cube_n0
	harley_cube_v1 harley_cube_t5 harley_cube_n0
	harley_cube_v5 harley_cube_t9 harley_cube_n0

	harley_cube_v0 harley_cube_t4 harley_cube_n0
	harley_cube_v5 harley_cube_t9 harley_cube_n0
	harley_cube_v4 harley_cube_t8 harley_cube_n0

	// face 2 right
	harley_cube_v1 harley_cube_t5 harley_cube_n1
	harley_cube_v2 harley_cube_t6 harley_cube_n1
	harley_cube_v6 harley_cube_t10 harley_cube_n1

	harley_cube_v1 harley_cube_t5 harley_cube_n1
	harley_cube_v6 harley_cube_t10 harley_cube_n1
	harley_cube_v5 harley_cube_t9 harley_cube_n1

	// face 3 back
	harley_cube_v2 harley_cube_t6 harley_cube_n2
	harley_cube_v3 harley_cube_t7 harley_cube_n2
	harley_cube_v7 harley_cube_t11 harley_cube_n2

	harley_cube_v2 harley_cube_t6 harley_cube_n2
	harley_cube_v7 harley_cube_t11 harley_cube_n2
	harley_cube_v6 harley_cube_t10 harley_cube_n2

	// face 4 left
	harley_cube_v3 harley_cube_t0 harley_cube_n3
	harley_cube_v0 harley_cube_t1 harley_cube_n3
	harley_cube_v4 harley_cube_t5 harley_cube_n3

	harley_cube_v3 harley_cube_t0 harley_cube_n3
	harley_cube_v4 harley_cube_t5 harley_cube_n3
	harley_cube_v7 harley_cube_t4 harley_cube_n3

	// face 5 bottom
	harley_cube_v0 harley_cube_t1 harley_cube_n4
	harley_cube_v1 harley_cube_t2 harley_cube_n4
	harley_cube_v2 harley_cube_t6 harley_cube_n4

	harley_cube_v0 harley_cube_t1 harley_cube_n4
	harley_cube_v2 harley_cube_t6 harley_cube_n4
	harley_cube_v3 harley_cube_t5 harley_cube_n4

	// face 6 top
	harley_cube_v4 harley_cube_t2 harley_cube_n5
	harley_cube_v5 harley_cube_t3 harley_cube_n5
	harley_cube_v6 harley_cube_t7 harley_cube_n5

	harley_cube_v4 harley_cube_t2 harley_cube_n5
	harley_cube_v6 harley_cube_t7 harley_cube_n5
	harley_cube_v7 harley_cube_t6 harley_cube_n5
};

#include <shaderlib.h>

#include "HarleyCube.h"

void HarleyCube::initVao(const GLuint & program)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(harley_cube), harley_cube, GL_STATIC_DRAW);

	// 3 floats for x, y, z coordinates
	GLuint locPosition = glGetAttribLocation(program, "in_vPosition");
	glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(locPosition);

	// 2 floats for x, y texture coordinates
	GLuint locTexCoord = glGetAttribLocation(program, "in_vTexCoord");
	glVertexAttribPointer(locTexCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(locTexCoord);

	// 3 floats for x, y, z vertex normals
	//GLuint locNormal = glGetAttribLocation(program, "in_vNormal");
	//glVertexAttribPointer(locNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	//glEnableVertexAttribArray(locNormal);
}

void HarleyCube::transform(Transform t)
{
	_model = t(_model);

	setMat4(_program, _model, "mModel");
}

void HarleyCube::init()
{
	if (GL_FALSE == loadTexture(_texture, "textures\\drawing.jpg"))
	{
		throw "Could not load HarleyCube texture.";
	}

	initVao(_program);

	if (GL_FALSE == setMat4(_program, _model, "mModel"))
	{
		throw "Could not set model HarleyCube matrix.";
	}
}

void HarleyCube::draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(harley_cube));
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void HarleyCube::destroy()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

