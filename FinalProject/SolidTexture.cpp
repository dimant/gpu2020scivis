#include "SolidTexture.h"

void SolidTexture::init()
{
	int width = 1;
	int height = 1;

	createTexture(&_color, width, height, GL_FLOAT);
}