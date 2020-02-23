#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"

class Model : public Transformable
{
private:
	void* _data;

	size_t _ndata;

	GLuint _program;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	GLuint _texture;

	const char* _textureName;

	void initVao(const GLuint & program);

public:
	Model(size_t ndata, void* data, const char* textureName) :
		_ndata(ndata),
		_data(data),
		_textureName(textureName),
		_model(glm::mat4(1.0f))
	{}

	virtual void transform(Transform t);

	void init(std::vector<GLuint> & programs);

	virtual GLint initShaders(GLuint & program);

	void draw();

	void destroy();

	const GLuint getProgram() { return _program; }
};

#endif
