#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include <GL\glew.h>

#include <gtc\type_ptr.hpp>

#include "shaderlib.h"

GLint getPtr(const GLuint & program, const char * name, GLint & ptr)
{
	ptr = glGetUniformLocation(program, name);

	if (ptr < 0)
	{
		std::cerr << "Shader variable name cannot be resolved: " << name << std::endl;
		return GL_FALSE;
	}
	else
	{
		return GL_TRUE;
	}
}

GLint setMat4(const GLuint & program, const glm::mat4 & matrix, const char* name)
{
	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniformMatrix4fv(
		ptr,
		1,
		GL_FALSE,
		glm::value_ptr(matrix));

	return GL_TRUE;
}

GLint setMat3(const GLuint & program, const glm::mat3 & matrix, const char* name)
{
	GLint ptr;
	ISOK(getPtr(program, name, ptr))

		glUniformMatrix3fv(
			ptr,
			1,
			GL_FALSE,
			glm::value_ptr(matrix));

	return GL_TRUE;
}

GLint setVec4(const GLuint & program, const glm::vec4 & vector, const char* name)
{
	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniform4fv(
		ptr,
		1,
		&vector[0]);

	return GL_TRUE;
}

GLint setVec3(const GLuint & program, const glm::vec3 & vector, const char* name)
{
	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniform3fv(
		ptr,
		1,
		&vector[0]);

	return GL_TRUE;
}

GLint buildShaderProgram(GLuint & program, const std::vector<shaderFile> & shaderFiles)
{
	GLint status = GL_TRUE;

	std::vector<GLuint> shaders;

	for (shaderFile shaderFile : shaderFiles)
	{
		std::string shaderSource = readFile(shaderFile.fileName);
		GLuint shader;
		ISOK(compileShader(shaderSource, shaderFile.shaderType, shader));
		shaders.push_back(shader);
	}

	ISOK(linkShaders(shaders, program));

	return status;
}

const std::string readFile(const std::string & path)
{
	std::string result;
	std::ifstream ifstream;
	std::stringstream sstream;

	ifstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		ifstream.open(path);

		sstream << ifstream.rdbuf();

		ifstream.close();

		result = sstream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error: could not read file " << path << std::endl;
	}

	return result;
}

GLint linkShaders(const std::vector<GLuint> & shaders, GLuint & program)
{
	GLint status = GL_TRUE;
	char infoLog[1024];

	program = glCreateProgram();

	auto attach = [=](const GLuint& s) { glAttachShader(program, s); };

	auto delshader = [](const GLuint& s) { glDeleteShader(s); };

	std::for_each(shaders.begin(), shaders.end(), attach);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);

	std::for_each(shaders.begin(), shaders.end(), delshader);

	if (GL_TRUE != status)
	{
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		std::cout << "Error: failed linking shaders: " << infoLog << std::endl;
	}

	return status;
}

GLint compileShader(const std::string & source, const GLenum & shaderType, GLuint & shader)
{
	GLint status = GL_TRUE;

	const char* cstr = source.c_str();

	shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &cstr, NULL);
	glCompileShader(shader);

	char infoLog[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (GL_TRUE != status)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "Error: failed compiling shader: " << infoLog << std::endl;
	}

	return status;
}
