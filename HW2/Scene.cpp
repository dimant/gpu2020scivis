#include <iostream>

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include <shaderlib.h>

#include "Scene.h"

Scene::Scene(const GLuint & program) :
	_program(program),
	_camPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	_polygonMode(GL_LINE)
{
	setView(glm::mat4(1.0f));
	moveCamZ(4.0f);
	setProj(glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f));

	changePolygonMode();
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

void Scene::setView(const glm::mat4 & view)
{
	_view = view;

	setMat4(_program, _view, "mView");
}

void Scene::setProj(const glm::mat4 & proj)
{
	_proj = proj;

	setMat4(_program, _proj, "mProj");
}

void Scene::apply()
{
	setView(_view);
	setProj(_proj);
}

void Scene::changePolygonMode()
{
	if (_polygonMode == GL_LINE)
	{
		_polygonMode = GL_FILL;
	}
	else
	{
		_polygonMode = GL_LINE;
	}

	glPolygonMode(GL_FRONT_AND_BACK, _polygonMode);
}
