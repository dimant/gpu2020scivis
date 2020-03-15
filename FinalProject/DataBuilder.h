#ifndef DATABUILDER_H
#define DATABUILDER_H

#include <iostream>
#include <memory>

#include "UniformGrid3.h"

#include "Model.h"
#include "Texture.h"

class DataBuilder
{
private:
	UniformGrid3* _grid;

	glm::vec3 _gmid;

	float _factor;

public:
	DataBuilder() :
		_grid(0),
		_gmid(glm::vec3(0.0f)),
		_factor(0.0f)
	{
	}

	~DataBuilder()
	{
		if (_grid != 0)
		{
			delete _grid;
		}
	}

	float getFactor() { return _factor; }

	void getSlice(float offset, float*& data, size_t & width, size_t & height)
	{
		width = _grid->getDimension1();
		height = _grid->getDimension2();
		auto depth = _grid->getDimension3();
		size_t i = (size_t) (offset * (float)depth/100.0f);

		if (i >= depth)
			i = depth - 1;

		data = (float*) _grid->getValues() + (width * height * i);
	}

	const glm::vec3 getMid() const { return _gmid; }

	const glm::vec3 getMin() const { return _grid->getMin(); }

	const glm::vec3 getMax() const { return _grid->getMax(); }

	void loadPVM(const char* filename);

	void loadFunction();

	std::shared_ptr<Model> createData(GLuint program, float isolevel, Texture* texture);
};

#endif