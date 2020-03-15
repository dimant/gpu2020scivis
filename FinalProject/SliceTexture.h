#ifndef SLICETEXTURE_H
#define SLICETEXTURE_H


#include "Texture.h"

#include <glm/glm.hpp>

class SliceTexture : public Texture
{
private:
	float* _data;
	size_t _width;
	size_t _height;

public:
	SliceTexture(float* data, size_t width, size_t height) :
		_data(data),
		_width(width),
		_height(height)
	{
	}

	virtual void init();

	void reload(float* data);
};

#endif