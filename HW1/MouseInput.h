#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include "Scene.h"

class MouseInput
{
private:
	Scene* _scene;

	unsigned short _buttonState;

	double _xpos;

	double _ypos;

public:
	MouseInput(Scene* scene);

	void leftButtonDown();

	void leftButtonUp();

	void moveCursorTo(double xpos, double ypos);
};

#endif