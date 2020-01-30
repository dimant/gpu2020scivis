
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

// x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
#define harley_cube_m0 0.1f,  1.0f, 2.0f, 128,
#define harley_cube_m1 0.11f, 2.0f, 2.2f, 128,
#define harley_cube_m2 0.12f, 3.0f, 2.4f, 128,
#define harley_cube_m3 0.13f, 4.0f, 2.6f, 128,
#define harley_cube_m4 0.14f, 18.0f, 2.8f, 512,
#define harley_cube_m5 0.15f, 6.0f, 3.0f, 128,
#define harley_cube_m6 0.16f, 7.0f, 3.2f, 256,

// vertex (x, y, z) texel (x, y) normal (x, y, z)
float harley_cube[] = {
	// face 1 front
	harley_cube_v0 harley_cube_t4 harley_cube_n0 harley_cube_m0
	harley_cube_v1 harley_cube_t5 harley_cube_n0 harley_cube_m0
	harley_cube_v5 harley_cube_t9 harley_cube_n0 harley_cube_m0

	harley_cube_v0 harley_cube_t4 harley_cube_n0 harley_cube_m0
	harley_cube_v5 harley_cube_t9 harley_cube_n0 harley_cube_m0
	harley_cube_v4 harley_cube_t8 harley_cube_n0 harley_cube_m0

	// face 2 right
	harley_cube_v1 harley_cube_t5 harley_cube_n1 harley_cube_m1
	harley_cube_v2 harley_cube_t6 harley_cube_n1 harley_cube_m1
	harley_cube_v6 harley_cube_t10 harley_cube_n1 harley_cube_m1

	harley_cube_v1 harley_cube_t5 harley_cube_n1 harley_cube_m1
	harley_cube_v6 harley_cube_t10 harley_cube_n1 harley_cube_m1
	harley_cube_v5 harley_cube_t9 harley_cube_n1 harley_cube_m1

	// face 3 back
	harley_cube_v2 harley_cube_t6 harley_cube_n2 harley_cube_m2
	harley_cube_v3 harley_cube_t7 harley_cube_n2 harley_cube_m2
	harley_cube_v7 harley_cube_t11 harley_cube_n2 harley_cube_m2

	harley_cube_v2 harley_cube_t6 harley_cube_n2 harley_cube_m2
	harley_cube_v7 harley_cube_t11 harley_cube_n2 harley_cube_m2
	harley_cube_v6 harley_cube_t10 harley_cube_n2 harley_cube_m2

	// face 4 left
	harley_cube_v3 harley_cube_t0 harley_cube_n3 harley_cube_m3
	harley_cube_v0 harley_cube_t1 harley_cube_n3 harley_cube_m3
	harley_cube_v4 harley_cube_t5 harley_cube_n3 harley_cube_m3

	harley_cube_v3 harley_cube_t0 harley_cube_n3 harley_cube_m3
	harley_cube_v4 harley_cube_t5 harley_cube_n3 harley_cube_m3
	harley_cube_v7 harley_cube_t4 harley_cube_n3 harley_cube_m3

	// face 5 bottom
	harley_cube_v0 harley_cube_t1 harley_cube_n4 harley_cube_m4
	harley_cube_v1 harley_cube_t2 harley_cube_n4 harley_cube_m4
	harley_cube_v2 harley_cube_t6 harley_cube_n4 harley_cube_m4

	harley_cube_v0 harley_cube_t1 harley_cube_n4 harley_cube_m4
	harley_cube_v2 harley_cube_t6 harley_cube_n4 harley_cube_m4
	harley_cube_v3 harley_cube_t5 harley_cube_n4 harley_cube_m4

	// face 6 top
	harley_cube_v4 harley_cube_t2 harley_cube_n5 harley_cube_m5
	harley_cube_v5 harley_cube_t3 harley_cube_n5 harley_cube_m5
	harley_cube_v6 harley_cube_t7 harley_cube_n5 harley_cube_m5

	harley_cube_v4 harley_cube_t2 harley_cube_n5 harley_cube_m5
	harley_cube_v6 harley_cube_t7 harley_cube_n5 harley_cube_m5
	harley_cube_v7 harley_cube_t6 harley_cube_n5 harley_cube_m5
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

	initVaoFormat(_program);
}

void HarleyCube::transform(Transform t)
{
	_model = t(_model);
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
	setMat4(_program, _model, "mModel");
	glBindTexture(GL_TEXTURE_2D, _texture);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(harley_cube));
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	setMat4(_program, glm::mat4(), "mModel");
}

void HarleyCube::destroy()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

