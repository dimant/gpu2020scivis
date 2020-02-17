#ifndef GRADIENTS_H
#define GRADIENTS_H

#include <glm/glm.hpp>

#include "UniformGrid3.h"

glm::vec3 getGradient(const UniformGrid3& grid, 
	const size_t & x,
	const size_t & y,
	const size_t & z);

#endif
