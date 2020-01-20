#include <iostream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include <shaderlib.h>

#include "vertexArrays.h"

#define ISOK(X) if(GL_TRUE != (X)) return GL_FALSE;

GLint compileShaders(GLuint & program)
{
	GLint status = GL_FALSE;

	std::vector<GLuint> shaders;

	std::string vshaderSource = readFile("vshaderEx1.glsl");
	GLuint vshader;
	ISOK(compileShader(vshaderSource, GL_VERTEX_SHADER, vshader));
	shaders.push_back(vshader);

	std::string fshaderSource = readFile("fshaderEx1.glsl");
	GLuint fshader;
	ISOK(compileShader(fshaderSource, GL_FRAGMENT_SHADER, fshader));
	shaders.push_back(fshader);

	ISOK(linkShaders(shaders, program));

	return status;
}

GLint initVao(GLuint & vao)
{
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	// 3 floats for x, y, z coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 3 floats for r, g, b colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return GL_TRUE;
}

void scaleCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
	if (GLFW_TRUE != glfwInit())
	{
		std::cerr << "ERROR: could not start GLFW3\n" << std::endl;
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle!", NULL, NULL);
	if (NULL == window) 
	{
		std::cerr << "ERROR: could not open window with GLFW3\n" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, scaleCallback);

	std::cout << "GLEW Version : " << GLEW_VERSION << std::endl;
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) 
	{
		std::cout << "glewInit failed, aborting." << std::endl;
	}

	GLuint vao; 
	ISOK(initVao(vao));

	GLuint program;
	GLint status = compileShaders(program);

	if (GL_TRUE == status)
	{
		std::cout << "Successfully compiled shaders." << std::endl;
	}

	glUseProgram(program);
	
	while (0 == glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
