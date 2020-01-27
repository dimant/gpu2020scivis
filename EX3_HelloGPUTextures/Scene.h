#ifndef SCENE_H
#define SCENE_H

#include <functional>
	
#include <GL\glew.h>
#include <glm\glm.hpp>

typedef std::function<void(const glm::mat4 &)> SetMat4Callback;

typedef std::function<void(glm::vec3)> SetVec3Callback;

class Scene
{
private:
	const GLuint & _program;

	glm::mat4 _model;

	SetMat4Callback _setModelCallback;

	glm::mat4 _view;

	glm::mat4 _proj;

	glm::vec3 _position;

	glm::vec3 _camPosition;

	float _scale;

	GLenum _polygonMode;

	void setModel(const glm::mat4 & _model);

	void setView(const glm::mat4 & _model);

	void setProj(const glm::mat4 & _model);

public:
	Scene(const GLuint & program);

	void apply();

	void registerModelChanged(SetMat4Callback callback);

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
