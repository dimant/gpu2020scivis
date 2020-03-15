#ifndef LINESTRIP_H
#define LINESTRIP_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"
#include "Texture.h"

class LineStrip : public Transformable
{
	void* _data;

	size_t _ndata;

	GLuint _lineWidth;

	const GLuint _program;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	Texture* _texture;

	glm::mat4 _origin;

	void initVao(const GLuint & program);

public:
	LineStrip(GLuint program, size_t ndata, void* data, Texture* texture) :
		_program(program),
		_ndata(ndata),
		_data(data),
		_model(glm::mat4(1.0f)),
		_origin(glm::mat4(1.0f)),
		_texture(texture),
		_lineWidth(5)
	{}

	void setOrigin(glm::mat4 origin) { _origin = origin; }

	virtual void transform(Transform t);

	void reset(size_t ndata, void* data);

	void init();

	void draw();

	void destroy();
};

#endif
