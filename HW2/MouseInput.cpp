#include <glm\glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "MouseInput.h"

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
				{
					glm::vec3 n = normalVector(_xpos, _ypos, xpos, ypos);
					float l = (float)vecLength(_xpos, _ypos, xpos, ypos) * 0.1f;
					_transformable.transform([n, l](glm::mat4 model) { return glm::rotate(model, l, n); });
				}
				break;
			case Translate:
				// Mouse coordinates begin in top left but model coordinates
				// begin in bottom left
				glm::vec3 dir = vector(_xpos, _ypos, xpos, ypos);
				dir.y = -dir.y;
				dir *= 0.2f;
				_transformable.transform([dir](glm::mat4 model) { return glm::translate(model, dir); });
				break;
			case Scale:
				{
					float f = (_xpos - xpos) > 0 ? 1.1f : 0.9f;
					_transformable.transform([f](glm::mat4 model) { return glm::scale(model, glm::vec3(f, f, f)); });
				}
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
