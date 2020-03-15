#ifndef SLICE_H
#define SLICE_H

#include <GL\glew.h>

#include "Model.h"
#include "LineStrip.h"
#include "IsoBuilder.h"
#include "SliceTexture.h"
#include "UniformGrid2.h"
#include "TransformableContainer.h"

class Slice
{
private:
	const GLuint _program;

	UniformGrid2* _grid;

	Model* _floor;

	LineStrip* _lineStrip;

	IsoBuilder* _isoBuilder;

	SliceTexture* _sliceTexture;

	Texture* _lineTexture;

	size_t _width;

	size_t _height;

	float _threshold;

public:
	Slice(GLuint program) : _program(program)
	{
	}

	float* scalarToRGB(float* data, size_t count);

	void setOrigin(glm::mat4 origin);

	void reset(float* data);

	void init(float* data, size_t width, size_t height, float threshold, TransformableContainer& tc);

	void draw();

	void destroy();
};

#endif
