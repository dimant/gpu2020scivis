#ifndef SCENE_H
#define SCENE_H

#include <GL\glew.h>
#include <glm\glm.hpp>

class Scene
{
private:
	const GLuint & _program;

	glm::mat4 _model;

	glm::mat4 _view;

	glm::mat4 _proj;

	glm::vec3 _position;

	float _camPositionZ;

	float _scale;

	GLenum _polygonMode;

	void setModel(const glm::mat4 & _model);

	void setView(const glm::mat4 & _model);

	void setProj(const glm::mat4 & _model);

public:
	Scene(const GLuint & program);

	void rotateModelX(const float & degrees);

	void rotateModelY(const float & degrees);

	void rotateModelZ(const float & degrees);

	void rotateModelAxis(const glm::vec3 & axis, const float & degrees);

	void translateModel(const glm::vec3 & direction);

	void scaleModel(const float & factor);

	void moveCamZ(const float & factor);

	void changePolygonMode();
};

#endif
