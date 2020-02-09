#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <glm\glm.hpp>

#define max(x, y) ((x > y) ? x : y)
#define max3(x, y, z) (max(x, max(y, z)))
#define min(x, y) ((x < y) ? x : y)
#define min3(x, y, z) (min(x, min(y, z)))

float minAngle(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3);

bool diagonal(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3, const glm::vec3 & v4);

#endif
