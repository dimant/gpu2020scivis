#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include <shaderlib.h>

#include <stb\stb_image.h>

#include "vertexArrays.h"
#include "Scene.h"
#include "MouseInput.h"
#include "Sphere.h"
#include "Lighting.h"

Scene* g_scene;
MouseInput* g_mouseInput;

bool g_enableAutoRotation = false;

void scaleCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void printHelp()
{
	std::cout << "Commands:" << std::endl
		<< "Camera: P M" << std::endl
		<< "Rotation: X Y Z" << std::endl
		<< "Timed Rotation: R" << std::endl
		<< "Mouse Rotation: Left Button + Drag" << std::endl
		<< "Wireframe: W" << std::endl
		<< "Rotate mode (default): 8" << std::endl
		<< "Translate mode: 9" << std::endl
		<< "Scale mode: 0" << std::endl
		<< std::endl;
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
				delete g_scene;
				exit(0);
				break;
			case GLFW_KEY_B:
				g_scene->scaleModel(2.0f);
				break;
			case GLFW_KEY_S:
				g_scene->scaleModel(0.5f);
				break;
			case GLFW_KEY_P:
				g_scene->moveCamZ(0.1f);
				break;
			case GLFW_KEY_M:
				g_scene->moveCamZ(-0.1f);
				break;
			case GLFW_KEY_X:
				g_scene->rotateModelX(45.0f);
				break;
			case GLFW_KEY_Y:
				g_scene->rotateModelY(45.0f);
				break;
			case GLFW_KEY_Z:
				g_scene->rotateModelZ(45.0f);
				break;
			case GLFW_KEY_W:
				g_scene->changePolygonMode();
				break;
			case GLFW_KEY_R:
				g_enableAutoRotation = !g_enableAutoRotation;
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
	else if(action == GLFW_RELEASE)
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
	if (g_enableAutoRotation)
	{
		float deg = 16.0f * (float) glfwGetTime();
		g_scene->rotateModelY(deg);
	}

	glfwSetTime(0.0);
}

void initCallbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, scaleCallback);

	glfwSetKeyCallback(window, keyCallback);

	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	glfwSetCursorPosCallback(window, mousePositionCallback);
}

void checkArgs(int argc, char** argv)
{
	if (argc == 1)
	{
		return;
	}

	if (argc != 3)
	{
		std::cout << "USAGE: " << argv[0] << " ARG1 ARG2\n" << std::endl;
		std::cout << "INPUT ARG1 : set recursion depth level (integer = 1 or greater)\n" << std::endl;
		std::cout << "INPUT ARG2 : 0 = facet normals, 1 = per-vertex normals, 2 = per-fragment Phong shading\n" << std::endl;
		std::cout << "Exiting..." << std::endl;
		exit(EXIT_SUCCESS);
	}
}

int getRecursions(int argc, char** argv)
{
	if (argc == 1)
	{
		return 4;
	}

	return atoi(argv[1]);
}

NormalTypes getNormalType(int argc, char** argv)
{
	if (argc == 1)
	{
		return VertexNormals;
	}

	return static_cast<NormalTypes>(atoi(argv[2]));
}

int main(int argc, char** argv)
{
	checkArgs(argc, argv);

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

	std::cout << "GLEW Version : " << GLEW_VERSION << std::endl;
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "glewInit failed, aborting." << std::endl;
	}

	int recursions = getRecursions(argc, argv);
	NormalTypes normals = getNormalType(argc, argv);

	Sphere sphere;
	sphere.init(recursions, normals);

	g_scene = new Scene(sphere.getProgram());
	g_mouseInput = new MouseInput(g_scene);

	Lighting lighting(sphere.getProgram());
	g_scene->registerModelChanged([&lighting](const glm::mat4 & m) { lighting.setModel(m); });
	g_scene->apply();

	lighting.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));

	// initialize callbacks after constructing state keeping objects
	initCallbacks(window);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	printHelp();
	
	while (0 == glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sphere.draw();

		glFlush();

		glfwSwapBuffers(window);
		timeCallback();
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	delete g_scene;

	return 0;
}