#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <functional>

#include <glm.hpp>

typedef std::function<glm::mat4(const glm::mat4)> Transform;

class Transformable
{
public:
	virtual void transform(Transform t) {}
};

#endif