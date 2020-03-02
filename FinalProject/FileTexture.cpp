#include "FileTexture.h"

#include <iostream>

#include "stb_image.h"

void FileTexture::init()
{
	int width, height, channels;
	stbi_uc * data = stbi_load(_filename.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		std::cerr << "Could not load texture at path: " << _filename << std::endl;
	}

	createTexture(data, width, height);

	stbi_image_free(data);
}
