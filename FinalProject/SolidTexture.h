#ifndef SOLIDTEXTURE_H
#define SOLIDTEXTURE_H

#include "Texture.h"
#include <glm/glm.hpp>

class SolidTexture : public Texture
{
private:
	glm::vec3 _color;

public:
	SolidTexture(float r, float g, float b) :
		_color(r, g, b)
	{
	}

	virtual void init();
};

#endif
