#ifndef DATABUILDER_H
#define DATABUILDER_H

#include <memory>

#include "UniformGrid2.h"

#include "Model.h"

#include "ShaderState.h"

class DataBuilder
{
public:
	DataBuilder()
	{
	}

	std::shared_ptr<Model> createData(UniformGrid2 & grid, ShaderState & shaderState);
};

#endif