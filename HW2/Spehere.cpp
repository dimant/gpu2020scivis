#include <shaderlib.h>

#include "Sphere.h"

void Sphere::triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int recursions)
{
	glm::vec3 facetNormal;
	if (recursions % 2 == 0) // even
		facetNormal = glm::normalize(glm::cross((a - b), (a - c)));
	else
		facetNormal = glm::normalize(glm::cross((a - c), (a - b)));

	_data[_k].vertex = a;
	_data[_k].normal = glm::normalize(a - glm::vec3(0.0f));
	_data[_k].color = _color;
	_k++;

	_data[_k].vertex = b;
	_data[_k].normal = glm::normalize(b - glm::vec3(0.0f));
	_data[_k].color = _color;
	_k++;

	_data[_k].vertex = c;
	_data[_k].normal = glm::normalize(c - glm::vec3(0.0f));
	_data[_k].color = _color;
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

	// 3 floats for x, y, z coordinates
	GLuint locPosition = glGetAttribLocation(program, "in_vPosition");
	glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(locPosition);

	// 3 floats for x, y, z vertex normals
	GLuint locNormal = glGetAttribLocation(program, "in_vNormal");
	glVertexAttribPointer(locNormal, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(locNormal);

	// 3 floats for r, g, b colors
	GLuint locColor = glGetAttribLocation(program, "in_vColor");
	glVertexAttribPointer(locColor, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(locColor);
}

void Sphere::init(GLuint recursions)
{
	_vertices = (GLuint)(3 * glm::pow(4.0f, recursions + 1));
	_data = new VertAtt[_vertices];
	_k = 0;

	beginSphere(recursions);

	glUseProgram(_program);

	initVao(_program);
}

void Sphere::draw()
{
	setMat4(_program, _model, "mModel");
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(VertAtt) * _vertices);
	glBindVertexArray(0);
	setMat4(_program, glm::mat4(), "mModel");
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
