#include <iostream>

#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include <shaderlib.h>

#include "Scene.h"
#include "rotateAxis.h"

Scene::Scene(const GLuint & program) :
	_program(program),
	_scale(1.0f),
	_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	_camPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	_polygonMode(GL_LINE)
{
	setModel(glm::mat4(1.0f));
	setView(glm::mat4(1.0f));
	moveCamZ(3.0f);
	setProj(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f));
	//setProj(glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f));

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

	setVec3(_program, _camPosition, "vCameraPosition");
}

void Scene::setModel(const glm::mat4 & model)
{
	_model = model;

	setMat4(_program, _model, "mModel");

	if (_setModelCallback)
	{
		_setModelCallback(_model);
	}
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

void Scene::registerModelChanged(SetMat4Callback callback)
{
	_setModelCallback = callback;
}

void Scene::apply()
{
	setModel(_model);
	setView(_view);
	setProj(_proj);
}

void Scene::rotateModelX(const float & degrees)
{
	_model = glm::rotate(_model, (float)glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));

	setModel(_model);
}

void Scene::rotateModelY(const float & degrees)
{
	_model = glm::rotate(_model, (float)glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));

	setModel(_model);
}

void Scene::rotateModelZ(const float & degrees)
{
	_model = glm::rotate(_model, (float)glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));

	setModel(_model);
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

void Scene::rotateModelAxis(const glm::vec3 & axis, const float & degrees)
{
	glm::mat4 trans = rotateAxis(_position, axis, degrees);
	_model = _model * trans;

	setModel(_model);
}

void Scene::translateModel(const glm::vec3 & direction)
{
	_position = _position + direction;

	_model = glm::translate(_model, direction);

	setModel(_model);
}

void Scene::scaleModel(const float & factor)
{
	_scale *= factor;
	_model = glm::scale(_model, glm::vec3(factor));

	setModel(_model);
}
