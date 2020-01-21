#include <iostream>

#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include "Scene.h"

Scene::Scene(GLuint program) 
{
	_program = program;
	_scale = 1.0f;
	_camPositionZ = 0.0f;

	setModel(glm::mat4(1.0f));
	setView(glm::mat4(1.0f));
	setProj(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f));
}

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