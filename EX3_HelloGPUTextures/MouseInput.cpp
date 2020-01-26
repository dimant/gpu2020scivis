#include <glm\glm.hpp>

#include "MouseInput.h"

MouseInput::MouseInput(Scene* scene) : _scene(scene), _buttonState(0), _transformationType(Rotate)
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

glm::vec3 vector(double oldX, double oldY, double newX, double newY)
{
	float x = (float)(newX - oldX);
	float y = (float)(newY - oldY);

	return glm::vec3(x, y, 0.0f);
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
		switch (_transformationType)
		{
			case Rotate:
				_scene->rotateModelAxis(
					normalVector(_xpos, _ypos, xpos, ypos),
					(float) vecLength(_xpos, _ypos, xpos, ypos) * 0.5f);
				break;
			case Translate:
				// Mouse coordinates begin in top left but model coordinates
				// begin in bottom left
				glm::vec3 direction = vector(_xpos, _ypos, xpos, ypos);
				direction.y = -direction.y;
				_scene->translateModel(direction * 0.01f);
				break;
			case Scale:
				float factor = (float)(_xpos - xpos);
				_scene->scaleModel(factor > 0 ? 1.1f : 0.9f);
				break;
		}
	}

	_xpos = xpos;
	_ypos = ypos;
}

void MouseInput::setTransformation(MouseTransformationType transformationType)
{
	_transformationType = transformationType;
}
