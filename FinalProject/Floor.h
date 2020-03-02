#ifndef FLOOR_H
#define FLOOR_H

#include <memory>

#include "Model.h"
#include "Texture.h"

std::shared_ptr<Model> createFloor(GLuint program, Texture* texture);

#endif