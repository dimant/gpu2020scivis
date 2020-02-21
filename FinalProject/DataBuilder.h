#ifndef DATABUILDER_H
#define DATABUILDER_H

#include <memory>

#include "UniformGrid3.h"

#include "Model.h"

class DataBuilder
{
public:
	DataBuilder()
	{
	}

	//std::shared_ptr<Model> createData(GLuint program, float isolevel);

	std::shared_ptr<Model> createData(GLuint program, float isolevel, char* filename);
};

#endif