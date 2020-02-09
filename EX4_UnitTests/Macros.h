#ifndef MACROS_H
#define MACROS_H

#include "triangulation.h"

#define EPSILON 0.00001
#define almosteq(x, y) (abs(x - y) <= EPSILON * max3(1.0f, abs(x), abs(y)))

#endif