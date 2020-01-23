#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include "Scene.h"

enum MouseTransformationType
{
	Rotate,
	Translate,
	Scale
};

class MouseInput
{
private:
	Scene* _scene;

	unsigned short _buttonState;

	double _xpos;

	double _ypos;

	MouseTransformationType _transformationType;

public:
	MouseInput(Scene* scene);

	void setTransformation(MouseTransformationType transformationType);

	void leftButtonDown();

	void leftButtonUp();

	void moveCursorTo(double xpos, double ypos);
};

#endif