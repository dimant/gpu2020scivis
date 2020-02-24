#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"

#include "ShaderState.h"

class Model : public Transformable
{
private:
	void* _data;

	const std::string _fshaderName;

	const std::string _vshaderName;

	size_t _ndata;

	GLuint _program;

	ShaderState & _shaderState;

	glm::mat4 _model;

	GLuint _vao;

	GLuint _vbo;

	GLuint _texture;

	const char* _textureName;

	void initVao(const GLuint & program);

public:
	Model(size_t ndata, void* data, const char* textureName,
		std::string fshaderName,
		std::string vshaderName,
		ShaderState & shaderState) :
		_ndata(ndata),
		_data(data),
		_textureName(textureName),
		_fshaderName(fshaderName),
		_vshaderName(vshaderName),
		_model(glm::mat4(1.0f)),
		_shaderState(shaderState)
	{}

	virtual void transform(Transform t);

	void init(std::vector<GLuint> & programs);

	GLint initShaders(GLuint & program);

	void draw();

	void destroy();

	const GLuint getProgram() { return _program; }
};

#endif
