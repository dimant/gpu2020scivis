#ifndef GRID_H
#define GRID_H

#include "ScalarAttributes.h"

#include <glm\glm.hpp>

class Grid
{
public:
	virtual size_t numPoints() const = 0;

	virtual size_t numCells() const = 0;

	virtual size_t numVertices() const = 0;

	virtual void getTris(float * data) const = 0;

	virtual const ScalarAttributes& pointScalars() = 0;
};

#endif