#ifndef LIGHTING_H
#define LIGHTING_H

#include <GL\glew.h>
#include <glm\glm.hpp>

enum LightingType
{
	None,
	Diffuse,
	Specular,
	Phong
};

class Lighting
{
private:
	const GLuint & _program;

	glm::vec3 _position;

	glm::vec3 _color;

	glm::vec4 _coefficients; // x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)

	glm::mat3 _mNormal;

	LightingType _lightingType;

public:
	Lighting(const GLuint & program);

	void setModel(const glm::mat4 & model);

	void setType(LightingType lightingType);

	void setPosition(glm::vec3 position);

	void setColor(glm::vec3 color);
};

#endif