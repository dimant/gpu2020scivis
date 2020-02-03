#ifndef TRANSFORMABLECONTAINER_H
#define TRANSFORMABLECONTAINER_H

#include <vector>
#include <memory>

#include "Transformable.h"

#include <glm\glm.hpp>

class TransformableContainer : public Transformable
{
private:
	std::vector<Transformable*> _transformables;

public:
	TransformableContainer() : _world(glm::mat4(1.0f))
	{
	}

	void add(Transformable* transformable);

	void transform(Transform t);
};
#endif