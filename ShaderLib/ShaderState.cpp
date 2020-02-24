#include "ShaderState.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "shaderlib.h"

size_t shaderStateTypeSize(ShaderStateType type)
{
	switch (type)
	{
	case Mat4ShaderState:
		return 16;
	case Mat3ShaderState:
		return 9;
	case Vec4ShaderState:
		return 4;
	case Vec3ShaderState:
		return 3;
	case FloatShaderState:
		return 1;
	case EmptyShaderState:
		return 0;
		break;
	default:
		return 0;
	}
}

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

void ShaderState::apply(GLuint program)
{
	for (auto entry : _state)
	{
		auto name = entry.first;
		auto value = entry.second;

		switch (value.getType())
		{
		case Mat4ShaderState:
			setMat4(program, glm::make_mat4(value.getData()), name.c_str());
			break;
		case Mat3ShaderState:
			setMat3(program, glm::make_mat3(value.getData()), name.c_str());
			break;
		case Vec4ShaderState:
			setVec4(program, glm::make_vec4(value.getData()), name.c_str());
			break;
		case Vec3ShaderState:
			setVec3(program, glm::make_vec3(value.getData()), name.c_str());
			break;
		case FloatShaderState:
			setFloat(program, *value.getData(), name.c_str());
			break;
		default:
			break;
		}
	}
}

void ShaderState::apply(const std::vector<GLuint> & programs)
{
	for (auto program : programs)
	{
		apply(program);
	}
}

GLint ShaderState::setMat4(const GLuint & program, const glm::mat4 & matrix, const char* name)
{
	size_t s = shaderStateTypeSize(Mat4ShaderState);
	float* data = (float*) new float[s];
	std::memcpy(data, &matrix, s * sizeof(float));
	ShaderStateEntry entry(name, data, Mat4ShaderState);
	_state[std::string(name)] = entry;

	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniformMatrix4fv(
		ptr,
		1,
		GL_FALSE,
		glm::value_ptr(matrix));

	return GL_TRUE;
}

void ShaderState::setMat4Arr(const std::vector<GLuint> & programs, glm::mat4 & matrix, const char* name)
{
	for (auto program : programs)
	{
		setMat4(program, matrix, name);
	}
}

GLint ShaderState::setMat3(const GLuint & program, const glm::mat3 & matrix, const char* name)
{
	size_t s = shaderStateTypeSize(Mat3ShaderState);
	float* data = (float*) new float[s];
	std::memcpy(data, &matrix, s * sizeof(float));
	ShaderStateEntry entry(name, data, Mat3ShaderState);
	_state[std::string(name)] = entry;

	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniformMatrix3fv(
		ptr,
		1,
		GL_FALSE,
		glm::value_ptr(matrix));

	return GL_TRUE;
}

void ShaderState::setMat3Arr(const std::vector<GLuint> & programs, glm::mat3 & value, const char* name)
{
	for (auto program : programs)
	{
		setMat3(program, value, name);
	}
}

GLint ShaderState::setVec4(const GLuint & program, const glm::vec4 & vector, const char* name)
{
	size_t s = shaderStateTypeSize(Vec4ShaderState);
	float* data = (float*) new float[s];
	std::memcpy(data, &vector, s * sizeof(float));
	ShaderStateEntry entry(name, data, Vec4ShaderState);
	_state[std::string(name)] = entry;

	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniform4fv(
		ptr,
		1,
		&vector[0]);

	return GL_TRUE;
}

void ShaderState::setVec4Arr(const std::vector<GLuint> & programs, glm::vec4 & value, const char* name)
{
	for (auto program : programs)
	{
		setVec4(program, value, name);
	}
}

GLint ShaderState::setVec3(const GLuint & program, const glm::vec3 & vector, const char* name)
{
	size_t s = shaderStateTypeSize(Vec3ShaderState);
	float* data = (float*) new float[s];
	std::memcpy(data, &vector, s * sizeof(float));
	ShaderStateEntry entry(name, data, Vec3ShaderState);
	_state[std::string(name)] = entry;

	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniform3fv(
		ptr,
		1,
		&vector[0]);

	return GL_TRUE;
}

void ShaderState::setVec3Arr(const std::vector<GLuint> & programs, glm::vec3 & value, const char* name)
{
	for (auto program : programs)
	{
		setVec3(program, value, name);
	}
}

GLint ShaderState::setFloat(const GLuint & program, const float value, const char* name)
{
	size_t s = shaderStateTypeSize(FloatShaderState);
	float* data = (float*) new float[s];
	std::memcpy(data, &value, s * sizeof(float));
	ShaderStateEntry entry(name, data, FloatShaderState);
	_state[std::string(name)] = entry;

	GLint ptr;
	ISOK(getPtr(program, name, ptr))

	glUniform1f(ptr, value);

	return GL_TRUE;
}

void ShaderState::setFloatArr(const std::vector<GLuint> & programs, float value, const char* name)
{
	for (auto program : programs)
	{
		setFloat(program, value, name);
	}
}