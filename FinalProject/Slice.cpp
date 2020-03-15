#include "Slice.h"

#include "SolidTexture.h"

#include <cmath>
#include "VertAtt.h"
#define SIDE 10.0f

#define floor_n0 0.0f, 0.0f, 1.0f
#define floor_m0 0.1f,  1.0f, 2.0f

VertAtt* createFloorVertices(size_t width, size_t height, float factor)
{
	VertAtt* vertices = new VertAtt[6];

	float xneg = -(width * factor / 2.0f);
	float xpos = -xneg;
	float yneg = -(height * factor / 2.0f);
	float ypos = -yneg;

	vertices[0].vertex = glm::vec3(xneg, ypos, 0.0f);
	vertices[0].texel = glm::vec2(0.0f, 1.0f);
	vertices[0].normal = glm::vec3(floor_n0);
	vertices[0].material = glm::vec3(floor_m0);

	vertices[1].vertex = glm::vec3(xpos, ypos, 0.0f);
	vertices[1].texel = glm::vec2(1.0f, 1.0f);
	vertices[1].normal = glm::vec3(floor_n0);
	vertices[1].material = glm::vec3(floor_m0);

	vertices[2].vertex = glm::vec3(xpos, yneg, 0.0f);
	vertices[2].texel = glm::vec2(1.0f, 0.0f);
	vertices[2].normal = glm::vec3(floor_n0);
	vertices[2].material = glm::vec3(floor_m0);

	vertices[3].vertex = glm::vec3(xpos, xneg, 0.0f);
	vertices[3].texel = glm::vec2(1.0f, 0.0f);
	vertices[3].normal = glm::vec3(floor_n0);
	vertices[3].material = glm::vec3(floor_m0);

	vertices[4].vertex = glm::vec3(xneg, yneg, 0.0f);
	vertices[4].texel = glm::vec2(0.0f, 0.0f);
	vertices[4].normal = glm::vec3(floor_n0);
	vertices[4].material = glm::vec3(floor_m0);

	vertices[5].vertex = glm::vec3(xneg, ypos, 0.0f);
	vertices[5].texel = glm::vec2(0.0f, 1.0f);
	vertices[5].normal = glm::vec3(floor_n0);
	vertices[5].material = glm::vec3(floor_m0);

	return vertices;
}

float* Slice::scalarToRGB(float* data, size_t count)
{
	float* result = new float[count * 4];

	float min = FLT_MAX;
	float max = FLT_MIN;

	for (int i = 0; i < count; i++)
	{
		if (data[i] > max)
			max = data[i];
		if (data[i] < min)
			min = data[i];
	}

	float range = 1.0f / (max - min);

	for (int i = 0; i < count; i++)
	{
		float v = 1.0f - range * (data[i] - min);
		result[i * 3 + 0] = v;
		result[i * 3 + 1] = v;
		result[i * 3 + 2] = v;
	}

	return result;
}

void Slice::reset(float* data)
{
	float* rgbData = scalarToRGB(data, _width * _height);

	_sliceTexture->reload(rgbData);

	for (int i = 0; i < _width * _height; i++)
	{
		_grid->pointScalars().setC0Scalar(i, data[i]);
	}

	delete rgbData;
}

void Slice::init(float* data, size_t width, size_t height, float factor, float threshold, TransformableContainer& tc)
{
	_width = width;
	_height = height;
	_threshold = threshold;

	float m1 = -(width * factor / 2.0f);
	float M1 = -m1;
	float m2 = -(height * factor / 2.0f);
	float M2 = -m2;

	_grid = new UniformGrid2(width, height, m1, m2, M1, M2);

	for (int i = 0; i < width * height; i++)
	{
		_grid->pointScalars().setC0Scalar(i, data[i]);
	}

	float* rgbData = scalarToRGB(data, width * height);	
	_sliceTexture = new SliceTexture(rgbData, width, height);
	_sliceTexture->init();
	delete rgbData;

	VertAtt* floorVertices = createFloorVertices(width, height, factor);
	
	_floor = new Model(_program, 6 * sizeof(VertAtt), floorVertices, _sliceTexture);
	_floor->init();
	_floor->setLightMix(0.0f);

	delete floorVertices;

	_lineTexture = new SolidTexture(0.0f, 1.0f, 0.0f);
	_lineTexture->init();

	_lineStrip = new LineStrip(_program, _grid->numVertices(), NULL, _lineTexture);
	_lineStrip->init();
	
	_isoBuilder = new IsoBuilder(*_grid);
	_isoBuilder->createIsoLine(_threshold, _lineStrip, 0.0f);

	tc.add(_floor);
	tc.add(_lineStrip);
}

void Slice::setOrigin(glm::mat4 origin)
{
	_floor->setOrigin(origin);
	_lineStrip->setOrigin(origin);
	_isoBuilder->createIsoLine(_threshold, _lineStrip, origin[3][2]);
}

void Slice::draw()
{
	_floor->draw();
	_lineStrip->draw();
}

void Slice::destroy()
{
	_lineStrip->destroy();
	_floor->destroy();
	delete _floor;
	delete _sliceTexture;
	delete _isoBuilder;
	delete _lineStrip;
	delete _grid;
}