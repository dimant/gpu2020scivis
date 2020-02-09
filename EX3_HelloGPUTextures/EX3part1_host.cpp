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

Scene* g_scene;
MouseInput* g_mouseInput;

bool g_enableAutoRotation = false;

GLint initModelShaders(GLuint & program)
{
	GLint status = GL_FALSE;

	shaderFile vertexShader{ GL_VERTEX_SHADER, "vshaderEx2.glsl" };
	shaderFile fragmentShader{ GL_FRAGMENT_SHADER, "fshaderEx2.glsl" };
	std::vector<shaderFile> shaderFiles{ vertexShader, fragmentShader };

	ISOK(buildShaderProgram(program, shaderFiles));

	return status;
}

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

GLint initVao(GLuint & vao, const GLuint & program)
{
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tilted_rect), tilted_rect, GL_STATIC_DRAW);

	// 3 floats for x, y, z coordinates
	GLuint locPosition = glGetAttribLocation(program, "in_vPosition");
	glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(locPosition);

	// 3 floats for r, g, b colors
	GLuint locColor = glGetAttribLocation(program, "in_vColor");
	glVertexAttribPointer(locColor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(locColor);

	// 2 floats for x, y texel coordinates
	GLuint locTexCoord = glGetAttribLocation(program, "in_vTexCoord");
	glVertexAttribPointer(locTexCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	return GL_TRUE;
}

GLint loadTexture(GLuint & texture, const std::string & path)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;
	stbi_uc * data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		std::cerr << "Could not load texture at path: " << path << std::endl;
		return GL_FALSE;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return GL_TRUE;
}

int Xmain(int argc, char** argv)
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

	std::cout << "GLEW Version : " << GLEW_VERSION << std::endl;
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "glewInit failed, aborting." << std::endl;
	}

	GLuint program;
	GLint status = initModelShaders(program);

	if (GL_TRUE == status)
	{
		std::cout << "Successfully built shader program." << std::endl;
	}

	glUseProgram(program);

	GLuint vao;
	ISOK(initVao(vao, program));

	g_scene = new Scene(program);
	g_mouseInput = new MouseInput(g_scene);

	// initialize callbacks after constructing state keeping objects
	initCallbacks(window);

	GLuint texture;
	ISOK(loadTexture(texture, "textures\\brickwall.jpg"));

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	printHelp();
	
	while (0 == glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(can_cube_verts_cols));
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
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