#ifndef SCENE_H
#define SCENE_H

#include <GL\glew.h>
#include <glm\glm.hpp>

class Scene
{
private:
	GLuint _program;

	glm::mat4 _model;

	glm::mat4 _view;

	glm::mat4 _proj;

	float _camPositionZ;

	float _scale;

	void setModel(const glm::mat4 & _model);

	void setView(const glm::mat4 & _model);

	void setProj(const glm::mat4 & _model);

public:
	Scene(GLuint program);

	void scaleModel(const float & factor);

	void rotateModelX(const float & degrees);

	void rotateModelY(const float & degrees);

	void rotateModelZ(const float & degrees);

	void moveCamZ(const float & factor);
};

#endif
