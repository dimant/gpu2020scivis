#ifndef UI_H
#define UI_H

#include <functional>

#include <GLFW\glfw3.h>

#include <imgui.h>

#include "ConfigHandler.h"

class UI
{
private:
	bool _showDemoWindow;
public:
	ConfigHandler<bool> EnableWireFrameHandler;

	ConfigHandler<bool> EnableAutoRotationHandler;

	ConfigHandler<bool> EnableDirectionalLightHandler;

	ConfigHandler<bool> EnableAttenuationLightHandler;

	ConfigHandler<float> LightDistanceHandler;

	ConfigHandler<int> ShinynessExponentHandler;

	ConfigHandler<float> SpotConeAngleHandler;

	ConfigHandler<float> SpotConeFalloffHandler;

	ConfigHandler<int> ModelManipulationHandler;

	ConfigHandler<bool> ButtonQuitHandler;

	void init(GLFWwindow* window, const char * glslVersion);

	void render();

	void draw();

	void destroy();

	float getDeltaTime();

	bool mouseCaptured();

	bool keyboardCaptured();
};

#endif