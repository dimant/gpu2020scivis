#ifndef SPHERE_H
#define SPHERE_H

#include <gl/glew.h>
#include <glm/glm.hpp>

enum NormalTypes
{
	VertexNormals,
	FacetNormals
};

struct VertAtt
{
	glm::vec3 vertex;
	glm::vec3 normal;
	glm::vec3 color;
};

class Sphere
{
private:
	const glm::vec3 _tetrahedron[4] = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.942809f, -0.333333f),
		glm::vec3(-0.816497f, -0.471405f, -0.333333f),
		glm::vec3(0.816497f, -0.471405f, -0.333333f)
	};

	const glm::vec4 _color = glm::vec4(0.2941f, 0.4902f, 0.8196f, 1.0f);

	VertAtt* _data;

	GLuint _k;

	NormalTypes _normalTypes;

	GLuint _vao;

	GLuint _vbo;

	GLuint _vertices;

	GLuint _program;

	void beginSphere(GLuint recursions);

	void divideTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, GLuint recursion, GLuint recursions);

	void triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int recursions);

	void initVao(const GLuint & program);

	GLint initShaders();

public:
	Sphere() : _data(0), _normalTypes(VertexNormals), _k(0), _vertices(0)
	{}

	const GLuint & getProgram() { return _program; }

	void init(GLuint recursions, NormalTypes normalTypes);

	void draw();

	void destroy();
};

#endif