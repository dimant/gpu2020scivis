#ifndef LIGHT_H
#define LIGHT_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Transformable.h"

class Light : public Transformable
{
private:
	const GLuint _program;

	glm::vec3 _color;

	glm::vec4 _coefficients; // x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)

	glm::mat3 _mNormal;

	glm::mat4 _mModel;

	glm::vec3 _position;

	glm::vec3 _target;

public:
	Light(const GLuint program);

	// note: this does not actually transform the light.
	// Instead, it keeps track of the normal transformation matrix.
	virtual void transform(Transform t);

	void setColor(glm::vec3 color);

	void setPosition(glm::vec3 position);
};

#endif