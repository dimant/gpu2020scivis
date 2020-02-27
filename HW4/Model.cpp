#include <shaderlib.h>

#include "Model.h"

void Model::initVao(const GLuint & program)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _ndata, _data, GL_STATIC_DRAW);

	// 3 floats for x, y, z coordinates
	GLuint locPosition = glGetAttribLocation(program, "in_vPosition");
	glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(locPosition);

	// 1 float for scalar
	GLuint locScalar = glGetAttribLocation(program, "in_fScalar");
	glVertexAttribPointer(locScalar, 1, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)1);
	glEnableVertexAttribArray(locScalar);

	// 2 floats for x, y texture coordinates
	GLuint locTexCoord = glGetAttribLocation(program, "in_vTexCoord");
	glVertexAttribPointer(locTexCoord, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(locTexCoord);

	// 3 floats for x, y, z vertex normals
	GLuint locNormal = glGetAttribLocation(program, "in_vNormal");
	glVertexAttribPointer(locNormal, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(locNormal);

	// 4 floats for ka, kd, ks, sh for material properties
	GLuint locMaterial = glGetAttribLocation(program, "in_vMaterial");
	glVertexAttribPointer(locMaterial, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(locMaterial);
}

void Model::transform(Transform t)
{
	_model = t(_model);
}

GLint Model::initShaders(GLuint & program)
{
	shaderFile vertexShader{ GL_VERTEX_SHADER, _vshaderName };
	shaderFile fragmentShader{ GL_FRAGMENT_SHADER,  _fshaderName };
	std::vector<shaderFile> shaderFiles{ vertexShader, fragmentShader };

	ISOK(buildShaderProgram(program, shaderFiles));

	return GL_TRUE;
}

void Model::init(std::vector<GLuint> & programs)
{
	_texture->init();
	initShaders(_program);
	initVao(_program);
	glUseProgram(_program);
	if (GL_FALSE == _shaderState.setMat4(_program, _model, "mModel"))
	{
		throw "Could not set model Model matrix.";
	}
	programs.push_back(_program);
}

void Model::setTexture(Texture* texture)
{
	delete _texture;
	_texture = texture;
}

void Model::setFloat(float value, const char* name)
{
	_shaderState.setFloat(_program, value, name);
}

void Model::draw()
{
	glUseProgram(_program);

	_shaderState.setMat4(_program, _model, "mModel");
	_shaderState.apply(_program);
	GLuint id = _texture->getId();
	glBindTexture(GL_TEXTURE_2D, id);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _ndata);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::destroy()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

