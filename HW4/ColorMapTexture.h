#ifndef COLORMAPTEXTURE_H
#define COLORMAPTEXTURE_H

#include "Texture.h"

struct Color
{
	float R;
	float G;
	float B;
};

class ColorMapTexture : public Texture
{
private:
	unsigned int _steps;

	const float _min;

	const float _max;

	GLint _filtering;

	Color* createData(int& width, int& height);

public:
	ColorMapTexture(unsigned int steps, float min, float max) :
		_steps(steps),
		_min(min),
		_max(max)
	{
	}

	virtual void init();

	void changeFiltering(GLint filtering);
	void changeSteps(unsigned int steps);
};
#endif