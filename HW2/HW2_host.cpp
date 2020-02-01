#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <shaderlib.h>

#include "UI.h"

#include "TransformableContainer.h"

#include "Scene.h"
#include "Light.h"
#include "MouseInput.h"

#include "HarleyCube.h"
#include "Sphere.h"

UI* g_ui;
Scene* g_scene;
Light* g_light;
MouseInput* g_mouseInput;

bool g_autoRotate = true;
bool g_quit = false;

void scaleCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (g_ui->keyboardCaptured())
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_8:
			g_mouseInput->setTransformation(Rotate);
			break;
		case GLFW_KEY_9:
			g_mouseInput->setTransformation(Translate);
			break;
		case GLFW_KEY_0:
			g_mouseInput->setTransformation(Scale);
			break;
		}
	}
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

	glfwSetKeyCallback(window, keyCallback);

	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	glfwSetCursorPosCallback(window, mousePositionCallback);
}

GLint initShaders(GLuint & program)
{
	shaderFile vertexShader{ GL_VERTEX_SHADER, "vshaderHCube.glsl" };
	shaderFile fragmentShader{ GL_FRAGMENT_SHADER, "fshaderHCube.glsl" };
	std::vector<shaderFile> shaderFiles{ vertexShader, fragmentShader };

	ISOK(buildShaderProgram(program, shaderFiles));

	return GL_TRUE;
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

	GLuint program;
	ISOK(initShaders(program));
	glUseProgram(program);

	UI ui;
	g_ui = &ui;
	g_ui->init(window, glslVersion);
	TransformableContainer tc;

	HarleyCube harleyCube(program);
	harleyCube.init();
	harleyCube.transform([](glm::mat4 m) { return glm::translate(m, glm::vec3(1.0f, 0.0f, 0.0f)); });

	Sphere sphere(program);
	sphere.init(4);
	sphere.transform([](glm::mat4 m) { return glm::translate(m, glm::vec3(-1.0f, 0.0f, 0.0f)); });

	Light light(program);
	light.setPosition(glm::vec3(0.0f, 3.0f, 3.0f));
	g_light = &light;

	tc.add(&harleyCube);
	tc.add(&sphere);
	tc.add(&light);

	Scene scene(program);
	g_scene = &scene;
	MouseInput mouseInput(tc, light);
	g_mouseInput = &mouseInput;

	g_autoRotate = g_ui->EnableAutoRotationHandler.Value = true;
	g_ui->EnableAutoRotationHandler.connect([](bool v) { 
		g_autoRotate = v;
		if (v)
			g_mouseInput->setTransformation(Rotate);
		else
			g_mouseInput->setTransformation(LightRotate);
	});

	g_ui->EnableDirectionalLightHandler.Value = false;
	light.setDirectionalLight(g_ui->EnableDirectionalLightHandler.Value);
	g_ui->EnableDirectionalLightHandler.connect([](bool v) { g_light->setDirectionalLight(v); });

	g_ui->EnableAttenuationLightHandler.Value = false;
	light.setEnableAttenuation(g_ui->EnableAttenuationLightHandler.Value);
	g_ui->EnableAttenuationLightHandler.connect([](bool v) { g_light->setEnableAttenuation(v); });

	g_ui->ShinynessExponentHandler.Value = 4;
	light.setShinyness((float)(1 << g_ui->ShinynessExponentHandler.Value));
	g_ui->ShinynessExponentHandler.connect([](int e) {
		g_light->setShinyness((float)(1 << g_ui->ShinynessExponentHandler.Value)); });

	g_ui->LightDistanceHandler.Value = light.getLightDistance();
	g_ui->LightDistanceHandler.connect([](float d) { g_light->setLightDistance(d); });

	g_ui->ButtonQuitHandler.connect([](bool v) { g_quit = true; });

	while (0 == glfwWindowShouldClose(window) && false == g_quit)
	{
		glfwPollEvents();

		g_ui->render();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		harleyCube.draw();
		sphere.draw();

		g_ui->draw();

		glFlush();

		glfwSwapBuffers(window);
		timeCallback();
	}

	harleyCube.destroy();
	sphere.destroy();

	g_ui->destroy();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
