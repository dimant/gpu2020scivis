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

#include "Floor.h"

#include "UniformGrid2.h"
#include "RectilinearGrid2.h"

#include "DataBuilder.h"
#include "IsoBuilder.h"

UI* g_ui;
Scene* g_scene;
Light* g_light;
MouseInput* g_mouseInput;
IsoBuilder* g_isoBuilder;
LineStrip* g_lineStrip;

bool g_autoRotate = true;
bool g_quit = false;


// 0.25 for | 2 | < x, y <= | 3 |
// 0.1 for | 1 | < x, y <= | 2 |
// 0.025 for 0 <= x, y <= | 1 |

RectilinearGrid2 createRectGrid()
{
	std::vector<float> dimsX;
	std::vector<float> dimsY;

	float d = -3.0f;

	dimsX.push_back(d);
	dimsY.push_back(d);

	while (d <= 3.0f)
	{
		if (d < -2.0f)
		{
			d += 0.25f;
		}
		else if (d < -1.0f)
		{
			d += 0.1f;
		}
		else if (d < 1.0f)
		{
			d += 0.025f;
		}
		else if (d < 2.0f)
		{
			d += 0.1f;
		}
		else
		{
			d += 0.25f;
		}

		dimsX.push_back(d);
		dimsY.push_back(d);
	}

	return RectilinearGrid2(dimsX, dimsY);
}

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

GLuint lex(const std::vector<GLuint>& n, const std::vector<GLuint>& N)
{
	size_t k, l;
	size_t d = N.size() - 1;

	GLuint sum = 0;
	GLuint prod = 1;

	for (k = 2; k <= d; k++)
	{
		prod = 1;

		for (l = 1; l < k - 1; l++)
		{
			prod *= N[l - 1];
		}

		sum += n[k - 1] * prod;
	}

	return n[0] + sum;
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

	auto grid = createRectGrid();

	std::vector<GLuint> programs;
	TransformableContainer tc;
	DataBuilder dataBuilder;
	auto data = dataBuilder.createData(grid);

	data->init(programs);
	tc.add(data.get());

	UI ui;
	g_ui = &ui;
	g_ui->init(window, glslVersion);

	Light light(programs);
	light.setPosition(glm::vec3(0.0f, 3.0f, 3.0f));
	g_light = &light;

	tc.add(&light);

	Scene scene(programs);
	scene.apply();
	g_scene = &scene;

	//auto floor = createFloor(program);
	//floor->init();

	//size_t N = (size_t) round(6.0f / 0.25f);
	//float m = -3;
	//float M = 3;
	//UniformGrid grid(N, N, m, m, M, M);

	float initialThreshold = 0.5f;
	IsoBuilder isoBuilder(grid);
	g_isoBuilder = &isoBuilder;
	g_lineStrip = new LineStrip(data->getProgram(), grid.numVertices(), NULL);
	g_lineStrip->init();
	isoBuilder.createIsoLine(initialThreshold, g_lineStrip);

	tc.add(g_lineStrip);

	MouseInput mouseInput(tc, light);
	g_mouseInput = &mouseInput;

	g_ui->IsoThresholdHandler.Value = initialThreshold;
	g_ui->IsoThresholdHandler.connect([](float v) { g_isoBuilder->createIsoLine(v, g_lineStrip); });

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
	light.setDirectionalLight(g_ui->EnableDirectionalLightHandler.Value);
	g_ui->EnableDirectionalLightHandler.connect([](bool v) { g_light->setDirectionalLight(v); });

	g_ui->EnableWireFrameHandler.Value = false;
	g_scene->setPolygonMode(g_ui->EnableWireFrameHandler.Value);
	g_ui->EnableWireFrameHandler.connect([](bool v) { g_scene->setPolygonMode(v); });

	g_ui->EnableAttenuationLightHandler.Value = true;
	light.setEnableAttenuation(g_ui->EnableAttenuationLightHandler.Value);
	g_ui->EnableAttenuationLightHandler.connect([](bool v) { g_light->setEnableAttenuation(v); });

	g_ui->ShinynessExponentHandler.Value = 4;
	light.setShininess((float)(1 << g_ui->ShinynessExponentHandler.Value));
	g_ui->ShinynessExponentHandler.connect([](int e) { g_light->setShininess((float)(1 << e)); });

	g_ui->LightDistanceHandler.Value = light.getLightDistance();
	g_ui->LightDistanceHandler.connect([](float d) { g_light->setLightDistance(d); });

	float coneAngle = 12.5f;
	g_ui->SpotConeAngleHandler.Value = coneAngle;
	light.setConeAngle(coneAngle);
	g_ui->SpotConeAngleHandler.connect([](float a) { g_light->setConeAngle(a); });

	float coneFalloff = 32.0f;
	g_ui->SpotConeFalloffHandler.Value = coneFalloff;
	light.setConeFalloff(coneFalloff);
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

	while (0 == glfwWindowShouldClose(window) && false == g_quit)
	{
		glfwPollEvents();

		g_ui->render();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//floor->draw();
		data->draw();
		g_lineStrip->draw();

		g_ui->draw();

		glFlush();

		glfwSwapBuffers(window);
		timeCallback();
	}

	//floor->destroy();
	data->destroy();
	g_lineStrip->destroy();

	g_ui->destroy();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
