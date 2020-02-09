#ifndef ISOBUILDER_H
#define ISOBUILDER_H

#include <memory>

#include "LineStrip.h"
#include "UniformGrid.h"

class IsoBuilder
{
public:
	IsoBuilder()
	{
	}

	std::shared_ptr<LineStrip> createIsoLine(GLuint program, UniformGrid & grid, float threshold);
};

#endif
