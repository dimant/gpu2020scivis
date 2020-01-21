#include <iostream>

#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include "Scene.h"
#include "rotateAxis.h"

void setMatrix(GLuint program, const glm::mat4 & matrix, const char* name)
{
	GLint ptr = glGetUniformLocation(program, name);

	if (ptr < 0)
	{
		std::cerr << "Shader variable name cannot be resolved: " << name << std::endl;
		return;
	}

	glUniformMatrix4fv(
		ptr,
		1,
		GL_FALSE,
		glm::value_ptr(matrix));
}

Scene::Scene(GLuint program) 
{
	_program = program;
	_scale = 1.0f;
	_camPositionZ = 0.0f;

	setModel(glm::mat4(1.0f));
	setView(glm::mat4(1.0f));
	moveCamZ(3.0f);
	//setProj(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f));
	setProj(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f));

	_polygonMode = GL_LINE;
	changePolygonMode();
}

void Scene::moveCamZ(const float & factor)
{
	_camPositionZ += factor;

	setView(
		glm::lookAt(
			glm::vec3(0.0f, 0.0f, _camPositionZ),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Scene::setModel(const glm::mat4 & model)
{
	_model = model;

	setMatrix(_program, _model, "mModel");
}

void Scene::setView(const glm::mat4 & view)
{
	_view = view;

	setMatrix(_program, _view, "mView");
}

void Scene::setProj(const glm::mat4 & proj)
{
	_proj = proj;

	setMatrix(_program, _proj, "mProj");
}

void Scene::scaleModel(const float & factor)
{
	_scale *= factor;
	_model = glm::scale(_model, glm::vec3(factor));

	setModel(_model);
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
	glm::mat4 trans = rotateAxis(axis, degrees);
	_model = _model * trans;

	setModel(_model);
}

