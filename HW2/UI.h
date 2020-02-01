#ifndef UI_H
#define UI_H

#include <functional>

#include <GLFW\glfw3.h>

#include <imgui.h>

#include "ConfigHandler.h"

class UI
{
public:
	ConfigHandler<bool> EnableAutoRotationHandler;

	ConfigHandler<bool> EnableDirectionalLightHandler;

	void init(GLFWwindow* window, const char * glslVersion);

	void render();

	void draw();

	void destroy();

	float getDeltaTime();

	bool mouseCaptured();

	bool keyboardCaptured();
};

#endif