#ifndef MODEL_H
#define MODEL_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"
#include "Texture.h"

class Model : public Transformable
{
private:
	void* _data;

	size_t _ndata;

	const GLuint _program;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	float _alpha;

	Texture* _texture;

	void initVao(const GLuint & program);

public:
	Model(GLuint program, size_t ndata, void* data, Texture* texture) :
		_program(program),
		_ndata(ndata),
		_data(data),
		_texture(texture),
		_model(glm::mat4(1.0f)),
		_alpha(1.0f)
	{}

	void setAlpha(float alpha);

	virtual void transform(Transform t);

	void init();

	void draw();

	void destroy();
};

#endif
