#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include <gtc\type_ptr.hpp>

#include "stb_image.h"

#include "shaderlib.h"

GLint createTexture(GLuint & texture, const char * data, size_t width, size_t height)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	return GL_TRUE;
}

GLint loadTexture(GLuint & texture, const std::string & path)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;
	stbi_uc * data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		std::cerr << "Could not load texture at path: " << path << std::endl;
		return GL_FALSE;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

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
