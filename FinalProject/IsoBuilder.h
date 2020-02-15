#ifndef ISOBUILDER_H
#define ISOBUILDER_H

#include <memory>

#include "LineStrip.h"
#include "UniformGrid.h"

class IsoBuilder
{
private:
	UniformGrid & _grid;

public:
	IsoBuilder(UniformGrid & grid) :
		_grid(grid)
	{
	}

	void createIsoLine(float threshold, LineStrip* lineStrip);
};

#endif
