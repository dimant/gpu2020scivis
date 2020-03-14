#include "TransformableContainer.h"

void TransformableContainer::add(Transformable* transformable)
{
	_transformables.push_back(transformable);
}

void TransformableContainer::transform(Transform t)
{
	glm::mat4 worldModel = t(glm::mat4(1.0f));

	for (auto transformable : _transformables)
	{
		transformable->transform([worldModel](glm::mat4 objectModel) { return  worldModel * objectModel; });
	}
}
