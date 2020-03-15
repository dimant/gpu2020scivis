#include "SliceTexture.h"

void SliceTexture::reload(float* data)
{
	_data = data;
	resetTexture(getId(), _data, _width, _height, GL_FLOAT, GL_LINEAR);
}

void SliceTexture::init()
{
	createTexture(_data, _width, _height, GL_FLOAT, GL_LINEAR);
}
