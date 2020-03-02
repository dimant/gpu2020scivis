#ifndef DATABUILDER_H
#define DATABUILDER_H

#include <memory>

#include "UniformGrid3.h"

#include "Model.h"
#include "Texture.h"

class DataBuilder
{
private:
	UniformGrid3* _grid;

	glm::vec3 _gmid;

public:
	DataBuilder() :
		_grid(0),
		_gmid(glm::vec3(0.0f))
	{
	}

	~DataBuilder()
	{
		if (_grid != 0)
		{
			delete _grid;
		}
	}

	void loadPVM(const char* filename);

	void loadFunction();

	std::shared_ptr<Model> createData(GLuint program, float isolevel, Texture* texture);
};

#endif