#include <iostream>

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include <shaderlib.h>

#include "Scene.h"

Scene::Scene() :
	_camPosition(glm::vec3(0.0f, 0.0f, 0.0f))
{
	setView(glm::mat4(1.0f));
	moveCamZ(4.0f);
	setProj(glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 50.0f));

	setPolygonMode(false);
}

void Scene::addProgram(GLuint program)
{
	_programs.push_back(program);
}

void Scene::moveCamZ(const float & factor)
{
	_camPosition.z += factor;

	setView(
		glm::lookAt(
			_camPosition,
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)));

	//setVec3(_program, _camPosition, "vCameraPosition");
}

void Scene::setView(glm::mat4 view)
{
	_view = view;

	for (auto program : _programs)
	{
		setMat4(program, _view, "mView");
	}
}

void Scene::setProj(glm::mat4 proj)
{
	_proj = proj;

	for (auto program : _programs)
	{
		setMat4(program, _proj, "mProj");
	}
}

void Scene::apply()
{
	setView(_view);
	setProj(_proj);
}

void Scene::setPolygonMode(bool mode)
{
	if (mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}
