#ifndef GRADIENTS_H
#define GRADIENTS_H

#include <glm/glm.hpp>

#include "UniformGrid3.h"

glm::vec3 getGradient(const UniformGrid3& grid, size_t x, size_t y, size_t z);

#endif
