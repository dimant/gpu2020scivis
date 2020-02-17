#ifndef POLYGONISE_H
#define POLYGONISE_H

#include "glm/glm.hpp"

#include "UniformGrid3.h"

// given values u, v and isolevel t, compute
// a value between 0 and 1 corresponding to use for interpolation
#define INTERP1(u, v, t) ((t - u) / (v - u))

// Interpolate the isolevel between p1.w and p2.w
// return an interpolated vertex p and an interpolated vertex normal n
void interpolate(
	glm::vec3& p,
	glm::vec3& n,
	const float & isolevel,
	const glm::vec4 & p1, const glm::vec3 & n1,
	const glm::vec4 & p2, const glm::vec3 & n2);

// Check each cube vertex against the isolevel and compute
// a bitmask to use against the look-up table.
void getCubeIndex(int & cubeindex, const Cube & cube, const float & isolevel);

// Copies marched values to *vertices
// The pointer must have enough space for 5 triangles.
// 5 triangles, 3 vertices, 1 vertex + 1 normal, 3 coordinates each
// = 5 * 3 * 2 * 3 = 90 floats
int getTriangles(
	const int triTable[][16],
	const glm::vec3 vertlist[],
	const glm::vec3 normlist[],
	const int& cubeindex,
	float* vertices);

// implements marching cubes algorithm
int polygonise(const Cube& cube, const float& isolevel, float *vertices);

#endif
