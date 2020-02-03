#ifndef GRID_H
#define GRID_H

#include "ScalarAttributes.h"

class Grid
{
public:
	virtual size_t numPoints() = 0;
	
	virtual size_t numCells() = 0;
	
	virtual void	 getPoint(int, float*) = 0;
	
	virtual int getCell(int, int*) = 0;
	
	virtual int findCell(float*) = 0;
	
	virtual ScalarAttributes& pointScalars() = 0;
};

#endif