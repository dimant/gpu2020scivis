#ifndef UI_H
#define UI_H

#include <functional>

#include <GLFW\glfw3.h>

#include <imgui.h>

#include "ConfigHandler.h"

#include "ValuesArray.h"

class UI
{
private:
	bool _showDemoWindow;

	float _averageFps;

public:
	ConfigHandler<bool> EnableWireFrameHandler;

	ConfigHandler<bool> EnableAutoRotationHandler;

	ConfigHandler<bool> InvertNormalsHandler;

	ConfigHandler<bool> EnableDirectionalLightHandler;

	ConfigHandler<bool> EnableAttenuationLightHandler;

	ConfigHandler<float> LightDistanceHandler;

	ConfigHandler<int> ShinynessExponentHandler;

	ConfigHandler<float> SpotConeAngleHandler;

	ConfigHandler<float> SpotConeFalloffHandler;

	ConfigHandler<int> ModelManipulationHandler;

	ConfigHandler<bool> ButtonQuitHandler;

	ConfigHandler<float> FloorOffsetHandler;

	ConfigHandler<float> ModelAlphaHandler;

	ValuesArray<float> FpsValuesArray;

	void init(GLFWwindow* window, const char * glslVersion);

	void setAverageFps(float value) { _averageFps = value; }

	void render();

	void draw();

	void destroy();

	float getDeltaTime();

	bool mouseCaptured();

	bool keyboardCaptured();
};

#endif