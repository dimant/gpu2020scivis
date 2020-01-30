#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include "Transformable.h"
#include "Light.h"

enum MouseTransformationType
{
	Rotate,
	Translate,
	Scale,
	LightRotate
};

class MouseInput
{
private:
	Transformable & _transformable;

	Light & _light;

	unsigned short _buttonState;

	double _xpos;

	double _ypos;

	MouseTransformationType _transformationType;

public:
	MouseInput(Transformable & transformable, Light & light) :
		_transformable(transformable),
		_buttonState(0),
		_transformationType(Rotate),
		_light(light)
	{
	}

	void setTransformable(Transformable & transformable);

	void setTransformation(MouseTransformationType transformationType);

	void leftButtonDown();

	void leftButtonUp();

	void moveCursorTo(double xpos, double ypos);
};

#endif