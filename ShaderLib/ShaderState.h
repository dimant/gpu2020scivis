#ifndef SHADERSTATE_H
#define SHADERSTATE_H

#include <vector>
#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>

enum ShaderStateType
{
	Mat4ShaderState,
	Mat3ShaderState,
	Vec4ShaderState,
	Vec3ShaderState,
	FloatShaderState,
	EmptyShaderState
};

size_t shaderStateTypeSize(ShaderStateType type);

class ShaderStateEntry
{
private:
	std::string _name;

	ShaderStateType _type;

	float* _data;

public:
	ShaderStateEntry()
	{
		_name = "";
		_type = EmptyShaderState;
		_data = 0;
	}

	ShaderStateEntry(const ShaderStateEntry & source)
	{
		_name = source.getName();
		_type = source.getType();
		size_t s = shaderStateTypeSize(_type);
		_data = new float[s];
		memcpy(_data, source.getData(), s * sizeof(float));
	}

	ShaderStateEntry(const char* name, float* data, ShaderStateType type) :
		_name(name),
		_data(data),
		_type(type)
	{
	}

	const std::string getName() const { return _name; }

	const ShaderStateType getType() const { return _type; }

	const float* getData() const { return _data; }
};

class ShaderState
{
private:
	std::map<std::string, ShaderStateEntry> _state;

public:
	void apply(GLuint program);

	void apply(const std::vector<GLuint> & programs);

	GLint setMat4(const GLuint & program, const glm::mat4 & matrix, const char* name);

	GLint setMat3(const GLuint & program, const glm::mat3 & matrix, const char* name);

	GLint setVec4(const GLuint & program, const glm::vec4 & vector, const char* name);

	GLint setVec3(const GLuint & program, const glm::vec3 & vector, const char* name);

	GLint setFloat(const GLuint & program, const float value, const char* name);

	void setMat3Arr(const std::vector<GLuint> & programs, glm::mat3 & value, const char* name);

	void setMat4Arr(const std::vector<GLuint> & programs, glm::mat4 & value, const char* name);

	void setVec3Arr(const std::vector<GLuint> & programs, glm::vec3 & value, const char* name);

	void setVec4Arr(const std::vector<GLuint> & programs, glm::vec4 & value, const char* name);

	void setFloatArr(const std::vector<GLuint> & programs, float value, const char* name);
};

#endif