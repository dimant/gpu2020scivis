#ifndef MODEL_H
#define MODEL_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"

class Model : public Transformable
{
private:
	float* _data;

	size_t _ndata;

	const GLuint _program;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	GLuint _texture;

	const char* _textureName;

	void initVao(const GLuint & program);

public:
	Model(GLuint program, size_t ndata, float* data, const char* textureName) :
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