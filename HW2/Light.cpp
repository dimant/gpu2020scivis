#include "Light.h"

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include <shaderlib.h>

Light::Light(const GLuint program) :
	_program(program),
	_color(glm::vec3(1.0f)),
	_coefficients(glm::vec4(0.1f, 6.0f, 2.0f, 128)), // x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
	_mNormal(glm::mat3(1.0f)),
	_mModel(glm::mat4(1.0f)),
	_position(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	_target(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
{
	setMat3(_program, _mNormal, "mNormal");
	setColor(_color);
	setVec4(_program, _coefficients, "vLightCoef");
	setVec3(_program, _position, "vLightPosition");
}

void Light::setColor(glm::vec3 color)
{
	_color = color;
	_color.x *= _coefficients.x; // ambient (ka)
	_color.y *= _coefficients.x;
	_color.z *= _coefficients.x;

	setVec3(_program, _color, "vLightColor");
}

void Light::setPosition(glm::vec3 position)
{
	_position = position;

	setVec3(_program, _position, "vLightPosition");
}

void Light::transform(Transform t)
{
	_mModel = t(_mModel);
	_mNormal = glm::transpose(glm::inverse(_mModel));

	setMat3(_program, _mNormal, "mNormal");
}

