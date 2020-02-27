#ifndef COLORMAPTEXTURE_H
#define COLORMAPTEXTURE_H

#include "Texture.h"

class ColorMapTexture : public Texture
{
private:
	const unsigned int _steps;

public:
	ColorMapTexture(unsigned int steps) :
		_steps(steps)
	{
	}

	virtual void init();
};
#endif