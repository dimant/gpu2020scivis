#ifndef GRID_H
#define GRID_H

#include "ScalarAttributes.h"

struct Point
{
	float x;
	float y;
};

struct Cell
{
	size_t v1;
	size_t v2;
	size_t v3;
	size_t v4;
};

class Grid
{
public:
	virtual size_t numPoints() = 0;
	
	virtual size_t numCells() = 0;
	
	virtual void getPoint(size_t i, Point & p) = 0;
	
	virtual void getCell(size_t, Cell &) = 0;
	
	virtual size_t findCell(const Point &) = 0;
	
	virtual const ScalarAttributes& pointScalars() = 0;
};

#endif