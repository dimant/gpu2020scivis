#ifndef MODEL_H
#define MODEL_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"

struct VertAtt
{
	glm::vec3 vertex;
	glm::vec2 texel;
	glm::vec3 normal;
	glm::vec3 material;
};

class Model : public Transformable
{
private:
	void* _data;

	size_t _ndata;

	const GLuint _program;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	GLuint _texture;

	const char* _textureName;

	void initVao(const GLuint & program);

public:
	Model(GLuint program, size_t ndata, void* data, const char* textureName) :
		_program(program),
		_ndata(ndata),
		_data(data),
		_textureName(textureName),
		_model(glm::mat4(1.0f))
	{}

	virtual void transform(Transform t);

	void init();

	void draw();

	void destroy();
};

#endif
