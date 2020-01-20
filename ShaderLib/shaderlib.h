#ifndef SHADERLIB_H
#define SHADERLIB_H

#include <string>
#include <vector>
#include <GL\glew.h>

const std::string readFile(const std::string & path);

GLint compileShader(const std::string & source, const GLenum & shaderType, GLuint & shader);

GLint linkShaders(const std::vector<GLuint> & shaders, GLuint & program);

#endif // !SHADERLIB_H
