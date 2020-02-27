#include "ColorMapTexture.h"

#include "math.h"

#include "triangulation.h"

struct Color
{
	float R;
	float G;
	float B;
};

void c(float f, float& R, float& G, float& B)
{
	float dx = 0.8;
	f = (f < 0) ? 0 : (f > 1) ? 1 : f; //clamp f in [0 , 1]
	float g = (6.0f - 2.0f * dx) * f + dx; //scale f to dx, 6 dx
	R = max(0, (3 - fabs(g - 4) - fabs(g - 5)) / 2);
	G = max(0, (4 - fabs(g - 2) - fabs(g - 4)) / 2);
	B = max(0, (3 - fabs(g - 1) - fabs(g - 2)) / 2);
}

void ColorMapTexture::init()
{
	const int width = _steps;
	int height = 1;
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

	createTexture(data, width, height, GL_FLOAT, GL_NEAREST);

	free(data);
}