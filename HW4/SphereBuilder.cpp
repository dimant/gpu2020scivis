#include <shaderlib.h>

#include "SphereBuilder.h"

void SphereBuilder::triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int recursions)
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

void SphereBuilder::divideTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, GLuint recursion, GLuint recursions)
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

void SphereBuilder::beginSphere(GLuint recursions)
{
	divideTriangle(_tetrahedron[0], _tetrahedron[1], _tetrahedron[2], recursions, recursions);
	divideTriangle(_tetrahedron[3], _tetrahedron[2], _tetrahedron[1], recursions, recursions);
	divideTriangle(_tetrahedron[0], _tetrahedron[3], _tetrahedron[1], recursions, recursions);
	divideTriangle(_tetrahedron[0], _tetrahedron[2], _tetrahedron[3], recursions, recursions);
}

std::shared_ptr<Model> SphereBuilder::createSphere(GLuint recursions, ShaderState & shaderState)
{
	_vertices = (GLuint)(3 * glm::pow(4.0f, recursions + 1));
	_data = new VertAtt[_vertices];
	_k = 0;

	beginSphere(recursions);

	return std::make_shared<Model>(
		sizeof(VertAtt) * _vertices,
		_data,
		"textures\\sphere.jpg",
		"ModelFShader.glsl",
		"ModelVShader.glsl",
		shaderState);
}