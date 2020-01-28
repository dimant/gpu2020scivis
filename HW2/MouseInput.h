#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include "Transformable.h"

enum MouseTransformationType
{
	Rotate,
	Translate,
	Scale
};

class MouseInput
{
private:
	Transformable & _transformable;

	unsigned short _buttonState;

	double _xpos;

	double _ypos;

	MouseTransformationType _transformationType;

public:
	MouseInput(Transformable & transformable) : 
		_transformable(transformable), _buttonState(0), _transformationType(Rotate)
	{
	}

	void setTransformation(MouseTransformationType transformationType);

	void leftButtonDown();

	void leftButtonUp();

	void moveCursorTo(double xpos, double ypos);
};

#endif