#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <shaderlib.h>

#include "UI.h"

#include "Transformable.h"
#include "TransformableContainer.h"
#include "Model.h"

#include "Scene.h"
#include "Light.h"
#include "MouseInput.h"

#include "DataBuilder.h"

UI* g_ui;
Scene* g_scene;
Light* g_light;
MouseInput* g_mouseInput;

bool g_autoRotate = true;
bool g_quit = false;

void scaleCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	g_scene->setProj(glm::perspective(glm::radians(90.0f), (float)width/(float)height, 0.1f, 50.0f));
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (g_ui->mouseCaptured())
		return;

	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			g_mouseInput->leftButtonDown();
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			g_mouseInput->leftButtonUp();
			break;
		}
	}
}

void mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	g_mouseInput->moveCursorTo(xpos, ypos);
}

void timeCallback()
{
	if (g_autoRotate)
	{
		float deg = 16.0f * g_ui->getDeltaTime();
		g_light->rotatePosition(deg);
	}
}

void initCallbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, scaleCallback);

	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	glfwSetCursorPosCallback(window, mousePositionCallback);
}

GLint initModelShaders(GLuint & program)
{
	shaderFile vertexShader{ GL_VERTEX_SHADER, "ModelVShader.glsl" };
	shaderFile fragmentShader{ GL_FRAGMENT_SHADER, "ModelFShader.glsl" };
	std::vector<shaderFile> shaderFiles{ vertexShader, fragmentShader };

	ISOK(buildShaderProgram(program, shaderFiles));

	return GL_TRUE;
}

void createUI()
{

	g_autoRotate = g_ui->EnableAutoRotationHandler.Value = false;
	g_ui->EnableAutoRotationHandler.connect([](bool v) {
		g_autoRotate = v;
		if (v && g_ui->ModelManipulationHandler.Value == 3)
		{
			g_ui->ModelManipulationHandler.Value = 0;
			g_ui->ModelManipulationHandler.handle(true);
		}
	});

	g_ui->EnableDirectionalLightHandler.Value = true;
	g_light->setDirectionalLight(g_ui->EnableDirectionalLightHandler.Value);
	g_ui->EnableDirectionalLightHandler.connect([](bool v) { g_light->setDirectionalLight(v); });

	g_ui->EnableWireFrameHandler.Value = false;
	g_scene->setPolygonMode(g_ui->EnableWireFrameHandler.Value);
	g_ui->EnableWireFrameHandler.connect([](bool v) { g_scene->setPolygonMode(v); });

	g_ui->EnableAttenuationLightHandler.Value = true;
	g_light->setEnableAttenuation(g_ui->EnableAttenuationLightHandler.Value);
	g_ui->EnableAttenuationLightHandler.connect([](bool v) { g_light->setEnableAttenuation(v); });

	g_ui->ShinynessExponentHandler.Value = 4;
	g_light->setShininess((float)(1 << g_ui->ShinynessExponentHandler.Value));
	g_ui->ShinynessExponentHandler.connect([](int e) { g_light->setShininess((float)(1 << e)); });

	g_ui->LightDistanceHandler.Value = g_light->getLightDistance();
	g_ui->LightDistanceHandler.connect([](float d) { g_light->setLightDistance(d); });

	float coneAngle = 12.5f;
	g_ui->SpotConeAngleHandler.Value = coneAngle;
	g_light->setConeAngle(coneAngle);
	g_ui->SpotConeAngleHandler.connect([](float a) { g_light->setConeAngle(a); });

	float coneFalloff = 32.0f;
	g_ui->SpotConeFalloffHandler.Value = coneFalloff;
	g_light->setConeFalloff(coneFalloff);
	g_ui->SpotConeFalloffHandler.connect([](float e) { g_light->setConeFalloff(e); });

	g_ui->ModelManipulationHandler.Value = 0;
	g_ui->ModelManipulationHandler.connect([](int o) {
		switch (o)
		{
		case 0:
			g_mouseInput->setTransformation(Rotate);
			break;
		case 1:
			g_mouseInput->setTransformation(Translate);
			break;
		case 2:
			g_mouseInput->setTransformation(Scale);
			break;
		case 3:
			g_ui->EnableAutoRotationHandler.Value = false;
			g_ui->EnableAutoRotationHandler.handle(true);
			g_mouseInput->setTransformation(LightRotate);
			break;
		}
	});

	g_ui->ButtonQuitHandler.connect([](bool v) { g_quit = true; });
}

int main(int argc, char** argv)
{
	const char * glslVersion = "#version 440 core";

	if (GLFW_TRUE != glfwInit())
	{
		std::cerr << "ERROR: could not start GLFW3\n" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1200, 1200, "Hello Triangle!", NULL, NULL);
	if (NULL == window)
	{
		std::cerr << "ERROR: could not open window with GLFW3\n" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	initCallbacks(window);

	std::cout << "GLEW Version : " << GLEW_VERSION << std::endl;
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "glewInit failed, aborting." << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLuint modelProgram;
	ISOK(initModelShaders(modelProgram));
	glUseProgram(modelProgram);

	UI ui;
	g_ui = &ui;
	g_ui->init(window, glslVersion);
	TransformableContainer tc;

	Light light(modelProgram);
	light.setPosition(glm::vec3(0.0f, 24.0f, 24.0f));
	g_light = &light;

	tc.add(&light);

	Scene scene;
	scene.addProgram(modelProgram);
	scene.apply();
	g_scene = &scene;

	DataBuilder dataBuilder;
	auto data = dataBuilder.createData(modelProgram, 2.f, "");
	//auto data = dataBuilder.createData(modelProgram, 2.0f);

	return 0;

	data->init();
	tc.add(data.get());

	MouseInput mouseInput(tc, light);
	g_mouseInput = &mouseInput;

	createUI();

	while (0 == glfwWindowShouldClose(window) && false == g_quit)
	{
		glfwPollEvents();

		g_ui->render();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		data->draw();

		g_ui->draw();

		glFlush();

		glfwSwapBuffers(window);
		timeCallback();
	}

	data->destroy();

	g_ui->destroy();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
