#include <glm\glm.hpp>

#include "MouseInput.h"

MouseInput::MouseInput(Scene* scene) : _scene(scene), _buttonState(0)
{
}

void MouseInput::leftButtonDown() 
{
	_buttonState |= 0x01;
}

void MouseInput::leftButtonUp()
{
	_buttonState &= 0xFFFE;
}

glm::vec3 normalVector(double oldX, double oldY, double newX, double newY)
{
	float x = (float) (newX - oldX);
	float y = (float) (newY - oldY);

	return glm::vec3(y, x, 0.0f);
}

float vecLength(double oldX, double oldY, double newX, double newY)
{
	float x = (float)(newX - oldX);
	float y = (float)(newY - oldY);

	return sqrtf(x * x + y * y);
}

void MouseInput::moveCursorTo(double xpos, double ypos)
{
	if (_buttonState & 0x01)
	{
		_scene->rotateModelAxis(
			normalVector(_xpos, _ypos, xpos, ypos),
			vecLength(_xpos, _ypos, xpos, ypos) * 0.5);
	}

	_xpos = xpos;
	_ypos = ypos;
}

