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

	SetMat4Callback _setModelCallback;

	glm::mat4 _view;

	glm::mat4 _proj;

	glm::vec3 _camPosition;

	GLenum _polygonMode;

	void setView(const glm::mat4 & view);

	void setProj(const glm::mat4 & proj);

public:
	Scene(const GLuint & program);

	void apply();

	void moveCamZ(const float & factor);

	void changePolygonMode();
};

#endif
