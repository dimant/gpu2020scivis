#ifndef FLOOR_H
#define FLOOR_H

#include <memory>

#include "Model.h"

#include "ShaderState.h"

std::shared_ptr<Model> createFloor(ShaderState & shaderState);

#endif