#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <shaderlib.h>

#include "TransformableContainer.h"

#include "Scene.h"
#include "Light.h"
#include "MouseInput.h"

#include "HarleyCube.h"
#include "Sphere.h"

Scene* g_scene;
Light* g_light;
MouseInput* g_mouseInput;

void scaleCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwDestroyWindow(window);
			glfwTerminate();
			delete g_mouseInput;
			delete g_scene;
			exit(0);
			break;
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
	float deg = 16.0f * (float)glfwGetTime();
	g_light->rotatePosition(deg);

	glfwSetTime(0.0);
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

	g_scene = new Scene(program);
	g_mouseInput = new MouseInput(tc);

	while (0 == glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		harleyCube.draw();
		sphere.draw();

		glFlush();

		glfwSwapBuffers(window);
		timeCallback();
		glfwPollEvents();
	}

	harleyCube.destroy();

	glfwDestroyWindow(window);

	glfwTerminate();

	delete g_scene;

	return 0;

}
