#ifndef SHADERLIB_H
#define SHADERLIB_H

#include <string>
#include <vector>
#include <GL\glew.h>

#include <glm\glm.hpp>

#define ISOK(X) if(GL_TRUE != (X)) return GL_FALSE;

struct shaderFile
{
	GLenum shaderType;
	std::string fileName;
};

GLint loadTexture(GLuint & texture, const std::string & path);

GLint createTexture(GLuint & texture, const char * data, size_t width, size_t height);

const std::string readFile(const std::string & path);

GLint compileShader(const std::string & source, const GLenum & shaderType, GLuint & shader);

GLint linkShaders(const std::vector<GLuint> & shaders, GLuint & program);

GLint getPtr(const GLuint & program, const char * name, GLint & ptr);

GLint buildShaderProgram(GLuint & program, const std::vector<shaderFile> & shaderFiles);

GLint setMat4(const GLuint & program, const glm::mat4 & matrix, const char* name);

GLint setMat3(const GLuint & program, const glm::mat3 & matrix, const char* name);

GLint setVec4(const GLuint & program, const glm::vec4 & vector, const char* name);

GLint setVec3(const GLuint & program, const glm::vec3 & vector, const char* name);

GLint setFloat(const GLuint & program, const float value, const char* name);

#endif // !SHADERLIB_H
