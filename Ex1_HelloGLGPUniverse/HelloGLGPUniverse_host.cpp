// Hello_GL_GPUniverse
// starter code for Host OpenGL Application for Lecture 1

// #includes and global defs
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "vertexArrays.h"
#include "shaderlib.h"

#define ISOK(X) if(GL_TRUE != (X)) return GL_FALSE;

// HERE

// Define framebuffer callback function
// HERE

// Define init( ) function for shader, VAO/VBO/EBO setup
// HERE

// Define main( ) entry point function
// - should contain GLFW and GLEW initialization steps
// - call init( ) function
// - enter main render loop and do OpenGL drawing
// HERE


void handleStatus(GLint status)
{
	if (GL_TRUE != status)
	{
		glfwTerminate();
	}
}

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

GLuint init()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	// 3 floats for x, y, z coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return vao;
}

int main(int argc, char** argv)
{
	// start GL context and O/S window using the GLFW helper library
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

	std::cout << "GLEW Version : " << GLEW_VERSION << std::endl;
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) 
	{
		std::cout << "glewInit failed, aborting." << std::endl;
	}

	GLuint vao = init();
	GLuint program;
	GLint status = compileShaders(program);

	if (GL_TRUE == status)
	{
		std::cout << "Successfully compiled shaders." << std::endl;
	}

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}

