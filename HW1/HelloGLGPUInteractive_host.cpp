#include <iostream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include <shaderlib.h>

#include "vertexArrays.h"
#include "Scene.h"

Scene* g_scene;

GLint initShaders(GLuint & program)
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
		}
	}
}

GLint initVao(GLuint & vao, const GLuint & program)
{
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(can_cube_verts_cols), can_cube_verts_cols, GL_STATIC_DRAW);

	// 3 floats for x, y, z coordinates
	GLuint locPosition = glGetAttribLocation(program, "in_vPosition");
	glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(locPosition);

	// 3 floats for r, g, b colors
	GLuint locColor = glGetAttribLocation(program, "in_vColor");
	glVertexAttribPointer(locColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(locColor);

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

	glfwSetFramebufferSizeCallback(window, scaleCallback);

	glfwSetKeyCallback(window, keyCallback);

	std::cout << "GLEW Version : " << GLEW_VERSION << std::endl;
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "glewInit failed, aborting." << std::endl;
	}

	GLuint program;
	GLint status = initShaders(program);

	if (GL_TRUE == status)
	{
		std::cout << "Successfully built shader program." << std::endl;
	}

	glUseProgram(program);

	GLuint vao;
	ISOK(initVao(vao, program));

	g_scene = new Scene(program);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	while (0 == glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(can_cube_verts_cols));
		glBindVertexArray(0);
		glFlush();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	delete g_scene;

	return 0;
}