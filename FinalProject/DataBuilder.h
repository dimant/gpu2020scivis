#ifndef DATABUILDER_H
#define DATABUILDER_H

#include <memory>

#include "UniformGrid.h"

#include "Model.h"

class DataBuilder
{
public:
	DataBuilder()
	{
	}

	std::shared_ptr<Model> createData(GLuint program, UniformGrid & grid);
};

#endif