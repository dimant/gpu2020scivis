#include "ColorMapTexture.h"

#include "math.h"

#include "triangulation.h"

void c(float f, float& R, float& G, float& B)
{
	float dx = 0.8;
	f = (f < 0) ? 0 : (f > 1) ? 1 : f; //clamp f in [0 , 1]
	float g = (6.0f - 2.0f * dx) * f + dx; //scale f to dx, 6 dx
	R = max(0, (3 - fabs(g - 4) - fabs(g - 5)) / 2);
	G = max(0, (4 - fabs(g - 2) - fabs(g - 4)) / 2);
	B = max(0, (3 - fabs(g - 1) - fabs(g - 2)) / 2);
}

Color* ColorMapTexture::createData(int& width, int& height)
{
	width = _steps;
	height = 1;

	Color* data = new Color[width * 3];

	float step = std::abs(_max - _min) / (float)_steps;
	float R, G, B;

	for (int i = 0; i < _steps; i++)
	{
		c(step * (float)i, R, G, B);
		data[i].R = R;
		data[i].G = G;
		data[i].B = B;
	}

	return data;
}

void ColorMapTexture::changeSteps(unsigned int steps)
{
	_steps = steps;

	int width, height;
	Color* data = createData(width, height);

	resetTexture(getId(), data, width, height, GL_FLOAT, _filtering);

	free(data);
}

void ColorMapTexture::changeFiltering(GLint filtering)
{
	_filtering = filtering;

	int width, height;
	Color* data = createData(width, height);

	resetTexture(getId(), data, width, height, GL_FLOAT, _filtering);

	free(data);
}

void ColorMapTexture::init()
{
	int width, height;
	Color* data = createData(width, height);
	_filtering = GL_NEAREST;

	createTexture(data, width, height, GL_FLOAT, _filtering);

	free(data);
}