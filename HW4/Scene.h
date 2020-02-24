#ifndef SCENE_H
#define SCENE_H

#include <functional>
	
#include <GL\glew.h>
#include <glm\glm.hpp>

#include "ShaderState.h"

typedef std::function<void(const glm::mat4 &)> SetMat4Callback;

typedef std::function<void(glm::vec3)> SetVec3Callback;

class Scene
{
private:
	const std::vector<GLuint> & _programs;

	ShaderState & _shaderState;

	SetMat4Callback _setModelCallback;

	glm::mat4 _view;

	glm::mat4 _proj;

	glm::vec3 _camPosition;

public:
	Scene(const std::vector<GLuint> & programs, ShaderState & shaderState);

	void setView(glm::mat4 view);

	void setProj(glm::mat4 proj);

	void apply();

	void moveCamZ(const float & factor);

	void setPolygonMode(bool mode);
};

#endif
