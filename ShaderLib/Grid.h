#ifndef GRID_H
#define GRID_H

#include "ScalarAttributes.h"

#include <glm\glm.hpp>

class Grid
{
public:
	virtual size_t numPoints() = 0;
	
	virtual size_t numCells() = 0;

	virtual size_t numVertices() = 0;

	virtual void getVertex(size_t i, glm::vec3 & v) = 0;

	virtual void getTris(float * data) = 0;
	
	virtual const ScalarAttributes& pointScalars() = 0;
};

#endif