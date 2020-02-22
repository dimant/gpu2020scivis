#include <glm\glm.hpp>

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
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
					float l = (float)vecLength(_xpos, _ypos, xpos, ypos) * 0.01f;
					_transformable.transform([n, l](glm::mat4 model) { 
						glm::vec3 axis = glm::vec3((glm::inverse(model) * glm::vec4(n, 0.0f)));
						return glm::rotate(model, l, axis); 
					});
				}
				break;

			case Translate:
				// Mouse coordinates begin in top left but model coordinates
				// begin in bottom left
				glm::vec3 dir = vector(_xpos, _ypos, xpos, ypos);
				dir.y = -dir.y;
				dir *= 0.002f;

				_transformable.transform([dir](glm::mat4 model) { return glm::translate(model, dir); });
				break;

			case Scale:
				{
					float f = (_xpos - xpos) > 0 ? 1.1f : 0.9f;
					_transformable.transform([f](glm::mat4 model) { return glm::scale(model, glm::vec3(f, f, f)); });
				}
				break;

			case LightRotate:
				float l = (float)vecLength(_xpos, _ypos, xpos, ypos) * 0.5f;
				if (xpos < _xpos)
				{
					l = -l;
				}
				_light.rotatePosition(l);
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

void MouseInput::setTransformable(Transformable & transformable)
{
	_transformable = transformable;
}
