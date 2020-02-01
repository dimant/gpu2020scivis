#include "Light.h"

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>
#include <gtc/quaternion.hpp>

#include <shaderlib.h>

Light::Light(const GLuint program) :
	_program(program),
	_color(glm::vec3(1.0f)),
	_mNormal(glm::mat3(1.0f)),
	_mModel(glm::mat4(1.0f)),
	_position(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	_target(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	_lightType(LightPoint)
{
	setMat3(_program, _mNormal, "mNormal");
	setColor(_color);
	setVec3(_program, _position, "vLightPosition");
	setVec4(_program, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), "vLightAttenuation");
}

void Light::setLightType(LightType lightType)
{
	_lightType = lightType;

	switch (_lightType)
	{
	case LightPoint:
		setFloat(_program, 1.0f, "fFragmentC");
		break;
	case LightDirectional:
		setFloat(_program, 0.0f, "fFragmentC");
		break;
	}
}

void Light::setColor(glm::vec3 color)
{
	_color = color;

	setVec3(_program, _color, "vLightColor");
}

void Light::setPosition(glm::vec3 position)
{
	_position = position;

	switch (_lightType)
	{
	case LightPoint:
		setVec3(_program, _position, "vLightPosition");
		break;
	case LightDirectional:
		glm::vec3 d = _position - _target;
		setVec3(_program, d, "vLightPosition");
		break;
	}
}

void Light::setTarget(glm::vec3 target)
{
	_target = target;

	if (LightDirectional == _lightType)
	{
		glm::vec3 d = _position - _target;
		setVec3(_program, d, "vLightPosition");
	}
}

void Light::rotatePosition(float angle)
{
	float r = glm::radians(angle);
	glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::quat quatRot = glm::angleAxis(r, axis);
	glm::mat4x4 matRot = glm::mat4_cast(quatRot);

	_position = glm::vec3(matRot * glm::vec4(_position, 1.0));

	setVec3(_program, _position, "vLightPosition");
}

void Light::transform(Transform t)
{
	_mModel = t(_mModel);
	_mNormal = glm::transpose(glm::inverse(_mModel));

	setMat3(_program, _mNormal, "mNormal");
}

