#include "ColorMapTexture.h"

#include "math.h"

#include "triangulation.h"

void c(float f, float& R, float& G, float& B)
{
	float dx = 0.8;
	f = (f < 0) ? 0 : (f > 1) ? 1 : f; //clamp f in [0 , 1]
	float g = (6.0f - 2.0f * dx) * f + dx; //scale f to dx, 6 dx
	R = max(0, (3 - fabs(g - 4) - fabs(g - 5)) / 2);
	G = max(0, (4 - fabs(g - 2) - fabs(g - 4)) / 2);
	B = max(0, (3 - fabs(g - 1) - fabs(g - 2)) / 2);
}

void ColorMapTexture::init()
{

}