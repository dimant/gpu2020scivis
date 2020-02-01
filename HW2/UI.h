#ifndef UI_H
#define UI_H

#include <GLFW\glfw3.h>

#include <imgui.h>

struct Config
{
	bool enableAmbientLight;

	bool enableDiffuseLight;

	bool enableSpecularLight;

	bool enableAttenuationLight;

	bool enableDirectionalLight;

	bool enableAutoRotation;
};

class UI
{
private:
	Config _config;

public:
	const Config & getConfig();

	void init(GLFWwindow* window, const char * glslVersion);

	void render();

	void draw();

	void destroy();

	float getDeltaTime();

	bool mouseCaptured();

	bool keyboardCaptured();
};

#endif