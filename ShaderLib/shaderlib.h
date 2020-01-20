#ifndef SHADERLIB_H
#define SHADERLIB_H

#include <string>
#include <vector>
#include <GL\glew.h>

#define ISOK(X) if(GL_TRUE != (X)) return GL_FALSE;

struct shaderFile
{
	GLenum shaderType;
	std::string fileName;
};

const std::string readFile(const std::string & path);

GLint compileShader(const std::string & source, const GLenum & shaderType, GLuint & shader);

GLint linkShaders(const std::vector<GLuint> & shaders, GLuint & program);

GLint buildShaderProgram(GLuint & program, const std::vector<shaderFile> & shaderFiles);

#endif // !SHADERLIB_H
