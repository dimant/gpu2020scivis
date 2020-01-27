#include "Lighting.h"

#include <shaderlib.h>

Lighting::Lighting(const GLuint & program)
	:
	_program(program),
	_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	_color(glm::vec3(1.0f, 1.0f, 1.0f)),
	// x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
	_coefficients(glm::vec4(0.15f, 0.0f, 0.5f, 256.0f)),
	_mNormal(glm::mat3(1.0f)),
	_lightingType(None)
{
	setColor(_color);
	setMat3(_program, _mNormal, "mNormal");
	setVec4(_program, _coefficients, "vLightCoef");
}

void Lighting::setModel(const glm::mat4 & model)
{
	_mNormal = glm::transpose(glm::inverse(model));

	setMat3(_program, _mNormal, "mNormal");
}

void Lighting::setType(LightingType lightingType)
{
	_lightingType = lightingType;
}

void Lighting::setPosition(glm::vec3 position)
{
	_position = position;

	setVec3(_program, _position, "vLightPosition");
}

void Lighting::setColor(glm::vec3 color)
{
	_color = color;
	_color.x *= _coefficients.x; // ambient (ka)
	_color.y *= _coefficients.x;
	_color.z *= _coefficients.x;

	setVec3(_program, _color, "vLightColor");
}