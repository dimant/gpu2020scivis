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
	_enableDirectionalLight(false),
	_attenuation(glm::vec4(1.0f, 0.022f, 0.0019f, 1.0f))
{
	setFloat(_program, 1.0f, "fEnableDirectionalLight");
	setMat3(_program, _mNormal, "mNormal");
	setColor(_color);
	setPosition(_position);
	setVec4(_program, _attenuation, "vLightAttenuation");
	setFloat(_program, 2.0f, "fLightShininess");
	setEnableAttenuation(false);
}

void Light::setDirectionalLight(bool enable)
{
	if (_enableDirectionalLight == enable)
		return;

	_enableDirectionalLight = enable;

	if (_enableDirectionalLight)
	{
		setFloat(_program, 0.0f, "fEnableDirectionalLight");
	}
	else
	{
		setFloat(_program, 1.0f, "fEnableDirectionalLight");
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

	glm::vec3 d = glm::normalize(_position - _target);
	setVec3(_program, d, "vLightDirection");
	
	if (_enableDirectionalLight)
	{
		setVec3(_program, d, "vLightPosition");
	}
	else
	{
		setVec3(_program, _position, "vLightPosition");
	}
}

float Light::getLightDistance()
{
	return glm::length(_position - _target);
}

void Light::setLightDistance(float d)
{
	glm::vec3 u = glm::normalize(_position - _target);
	setPosition(_target + u * d);
}

void Light::setTarget(glm::vec3 target)
{
	_target = target;
	
	glm::vec3 d = glm::normalize(_position - _target);
	setVec3(_program, d, "vLightDirection");

	if (_enableDirectionalLight)
	{
		setVec3(_program, d, "vLightPosition");
	}
}

void Light::rotatePosition(float angle)
{
	float r = glm::radians(angle);
	glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::quat quatRot = glm::angleAxis(r, axis);
	glm::mat4x4 matRot = glm::mat4_cast(quatRot);

	glm::vec3 position = glm::vec3(matRot * glm::vec4(_position, 1.0));

	setPosition(position);
}

void Light::transform(Transform t)
{
	_mModel = t(_mModel);
	_mNormal = glm::transpose(glm::inverse(_mModel));

	setMat3(_program, _mNormal, "mNormal");
}

void Light::setEnableAttenuation(bool enable)
{
	if (enable)
	{
		setVec4(_program, _attenuation, "vLightAttenuation");
	}
	else
	{
		setVec4(_program, glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), "vLightAttenuation");
	}
}

void Light::setShininess(float e)
{
	setFloat(_program, e, "fLightShininess");
}

void Light::setConeAngle(float theta)
{
	float r = cos(glm::radians(theta));
	setFloat(_program, r, "fSpotCosTheta");
}