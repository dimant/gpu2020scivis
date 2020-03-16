#ifndef BUFFEREDCOUNTER_H
#define BUFFEREDCOUNTER_H

#include "GL/glew.h"

class BufferedCounter
{
private:
	GLuint _queryId[2];

	GLuint _queryFrontBuffer;
	
	GLuint _queryBackBuffer;

	void swapQueryBuffers();

public:
	BufferedCounter() :
		_queryFrontBuffer(0),
		_queryBackBuffer(1)
	{
	}

	void init();

	void start();

	GLuint64 stop();
};

#endif