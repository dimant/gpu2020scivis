#include "TransformableContainer.h"

void TransformableContainer::add(Transformable* transformable)
{
	_transformables.push_back(transformable);
}

void TransformableContainer::transform(Transform t)
{
	for (auto transformable : _transformables)
	{
		transformable->transform(t);
	}
}
