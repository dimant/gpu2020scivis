#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture
{
private:
	GLuint _id;

protected:
	GLint createTexture(const unsigned char * data, size_t width, size_t height);

public:
	virtual void init() = 0;

	const GLuint getId() const { return _id; }
};

#endif
