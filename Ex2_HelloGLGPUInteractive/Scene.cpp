#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\matrix_access.hpp>
#include <gtc\matrix_inverse.hpp>

#include "Scene.h"

Scene::Scene(GLuint program) 
{
	_program = program;
	_scale = 1.0f;

	setModel(glm::mat4(1.0f));
	setView(glm::mat4(1.0f));
	setProj(glm::mat4(1.0f));
}

void setMatrix(GLuint program, const glm::mat4 & matrix, const char* name)
{
	glUniformMatrix4fv(
		glGetUniformLocation(program, name),
		1,
		GL_FALSE,
		glm::value_ptr(matrix));
}

void Scene::setModel(const glm::mat4 & model)
{
	_model = model;

	setMatrix(_program, _model, "mModel");
}

void Scene::setView(const glm::mat4 & view)
{
	_view = view;

	setMatrix(_program, _model, "mView");
}

void Scene::setProj(const glm::mat4 & proj)
{
	_proj = proj;

	setMatrix(_program, _model, "mProj");
}

void Scene::scale(float factor)
{
	_scale *= factor;
	_model = glm::scale(_model, glm::vec3(factor));

	setModel(_model);
}