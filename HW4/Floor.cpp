#include "Floor.h"

#define floor_n0 0.0f, 1.0f, 0.0f,
#define floor_m0 0.1f,  1.0f, 2.0f,

float floorVertices[] = {
	// face 1 front
	-5.0f, -1.0f, 5.0f, 0.0f, 0.0f, floor_n0 floor_m0
	5.0f, -1.0f, 5.0f, 1.0f, 0.0f, floor_n0 floor_m0
	5.0f, -1.0f, -5.0f, 1.0f, 1.0f, floor_n0 floor_m0

	5.0f, -1.0f, -5.0f, 1.0f, 1.0f, floor_n0 floor_m0
	-5.0f, -1.0f, -5.0f, 0.0f, 1.0f, floor_n0 floor_m0
	-5.0f, -1.0f, 5.0f, 0.0f, 0.0f, floor_n0 floor_m0
};

std::shared_ptr<Model> createFloor(ShaderState & shaderState)
{
	return std::make_shared<Model>(
		sizeof(floorVertices),
		floorVertices,
		"textures\\sphere.jpg",
		"ModelFShader.glsl",
		"ModelVShader.glsl",
		shaderState);
}