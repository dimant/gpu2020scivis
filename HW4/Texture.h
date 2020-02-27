#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture
{
private:
	GLuint _id;

protected:
	GLint createTexture(
		const void * data,
		size_t width,
		size_t height,
		GLenum type = GL_UNSIGNED_BYTE,
		GLint filtering = GL_LINEAR);

	void resetTexture(
		GLuint texture,
		const void * data,
		size_t width,
		size_t height,
		GLenum type,
		GLint filtering);

public:
	virtual void init() = 0;

	const GLuint getId() const { return _id; }
};

#endif
