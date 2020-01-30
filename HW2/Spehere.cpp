#include <shaderlib.h>

#include "Sphere.h"

void Sphere::triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int recursions)
{
	_data[_k].vertex = a;
	_data[_k].texel = glm::vec2(0.0f, 0.0f);
	_data[_k].normal = glm::normalize(a);
	_data[_k].material = _material;
	_k++;

	_data[_k].vertex = b;
	_data[_k].texel = glm::vec2(0.0f, 0.0f);
	_data[_k].normal = glm::normalize(b);
	_data[_k].material = _material;
	_k++;

	_data[_k].vertex = c;
	_data[_k].texel = glm::vec2(0.0f, 0.0f);
	_data[_k].normal = glm::normalize(c);
	_data[_k].material = _material;
	_k++;
}

void Sphere::divideTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, GLuint recursion, GLuint recursions)
{
	// save recursion depth level to correct vertex orientation reversals odd/even
	glm::vec3 v1, v2, v3;
	if (recursion > 0)
	{
		v1 = glm::normalize(a + b);
		v2 = glm::normalize(a + c);
		v3 = glm::normalize(b + c);
		divideTriangle(a, v2, v1, recursion - 1, recursions);
		divideTriangle(c, v3, v2, recursion - 1, recursions);
		divideTriangle(b, v1, v3, recursion - 1, recursions);
		divideTriangle(v1, v2, v3, recursion - 1, recursions);
	}
	else
	{
		triangle(a, b, c, recursions);
	}
}

void Sphere::beginSphere(GLuint recursions)
{
	divideTriangle(_tetrahedron[0], _tetrahedron[1], _tetrahedron[2], recursions, recursions);
	divideTriangle(_tetrahedron[3], _tetrahedron[2], _tetrahedron[1], recursions, recursions);
	divideTriangle(_tetrahedron[0], _tetrahedron[3], _tetrahedron[1], recursions, recursions);
	divideTriangle(_tetrahedron[0], _tetrahedron[2], _tetrahedron[3], recursions, recursions);
}


float myrect[] = {
	// vertex position (x,y,z), color (r,g,b), texel (x, y)

	-1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,// v0
	1.0f, -1.0f, 1.0f,     1.0f, 1.0f, 1.0f,// v1
	1.0f, 1.0f, -1.0f,      1.0f, 1.0f, 1.0f,// v2

	-1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,// v0
	1.0f, 1.0f, -1.0f,      1.0f, 1.0f, 1.0f,// v2
	-1.0f, 1.0f, -1.0f,     1.0f, 1.0f, 1.0f,// v3
};

void Sphere::initVao(const GLuint & program)
{
	GLuint vbo;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertAtt) * _vertices, _data, GL_STATIC_DRAW);

	initVaoFormat(_program);
}

void Sphere::init(GLuint recursions)
{
	_vertices = (GLuint)(3 * glm::pow(4.0f, recursions + 1));
	_data = new VertAtt[_vertices];
	_k = 0;

	beginSphere(recursions);

	glUseProgram(_program);
	
	if (GL_FALSE == loadTexture(_texture, "textures\\sphere.jpg"))
	{
		throw "Could not load HarleyCube texture.";
	}

	initVao(_program);
}

void Sphere::draw()
{
	setMat4(_program, _model, "mModel");
	glBindTexture(GL_TEXTURE_2D, _texture);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(VertAtt) * _vertices);
	glBindVertexArray(0);
	setMat4(_program, glm::mat4(), "mModel");
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sphere::destroy()
{
	delete(_data);
	_data = 0;
	_vertices = 0;
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

void Sphere::transform(Transform t)
{
	_model = t(_model);
}