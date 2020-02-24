#ifndef FILETEXTURE_H
#define FILETEXTURE_H

#include <string>

#include <GL/glew.h>

#include "Texture.h"


class FileTexture : public Texture
{
private:
	std::string _filename;

public:
	FileTexture(const char* filename) :
		_filename(filename)
	{
	}

	virtual void init();
};

#endif
