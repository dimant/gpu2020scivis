#ifndef TRANSFORMABLECONTAINER_H
#define TRANSFORMABLECONTAINER_H

#include <vector>
#include <memory>

#include "Transformable.h"

class TransformableContainer : public Transformable
{
private:
	std::vector<Transformable*> _transformables;

public:
	void add(Transformable* transformable);

	void transform(Transform t);
};
#endif