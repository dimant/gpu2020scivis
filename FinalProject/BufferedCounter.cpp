#include "BufferedCounter.h"

void BufferedCounter::init()
{
	glGenQueries(2, _queryId);
}

void BufferedCounter::start()
{
	glBeginQuery(GL_TIME_ELAPSED, _queryId[_queryFrontBuffer]);
}

GLuint64 BufferedCounter::stop()
{
	GLuint64 elapsedTime;

	glEndQuery(GL_TIME_ELAPSED);

	glGetQueryObjectui64v(_queryId[_queryBackBuffer], GL_QUERY_RESULT, &elapsedTime);

	swapQueryBuffers();

	return elapsedTime;
}

void BufferedCounter::swapQueryBuffers()
{
	_queryBackBuffer = !_queryBackBuffer;
	_queryFrontBuffer = !_queryFrontBuffer;
}
