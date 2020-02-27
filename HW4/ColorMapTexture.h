#ifndef COLORMAPTEXTURE_H
#define COLORMAPTEXTURE_H

#include "Texture.h"

class ColorMapTexture : public Texture
{
private:
	const unsigned int _steps;

	const float _min;

	const float _max;

public:
	ColorMapTexture(unsigned int steps, float min, float max) :
		_steps(steps),
		_min(min),
		_max(max)
	{
	}

	virtual void init();
};
#endif