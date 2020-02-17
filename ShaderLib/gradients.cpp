#include "Gradients.h"

glm::vec3 getGradient(const UniformGrid3& grid, size_t x, size_t y, size_t z)
{
	float x1, x2;
	float dx = grid.getDelta1();
	float gx;

	if (x == 0)
	{
		x1 = grid.getScalar(x, y, z);
		x2 = grid.getScalar(x + 1, y, z);
	}
	else if (x == grid.getDimension1() - 1)
	{
		x1 = grid.getScalar(x - 1, y, z);
		x2 = grid.getScalar(x, y, z);
	}
	else
	{
		x1 = grid.getScalar(x - 1, y, z);
		x2 = grid.getScalar(x + 1, y, z);
	}

	gx = (x2 - x1) / (2.0f * dx);

	float y1, y2;
	float dy = grid.getDelta2();
	float gy;

	if (y == 0)
	{
		y1 = grid.getScalar(x, y, z);
		y2 = grid.getScalar(x, y + 1, z);
	}
	else if (y == grid.getDimension2() - 1)
	{
		y1 = grid.getScalar(x, y - 1, z);
		y2 = grid.getScalar(x, y, z);
	}
	else
	{
		y1 = grid.getScalar(x, y - 1, z);
		y2 = grid.getScalar(x, y + 1, z);
	}

	gy = (y2 - y1) / (2.0f * dy);

	float z1, z2;
	float dz = grid.getDelta3();
	float gz;

	if (z == 0)
	{
		z1 = grid.getScalar(x, y, z);
		z2 = grid.getScalar(x, y, z + 1);
	}
	else if (z == grid.getDimension3() - 1)
	{
		z1 = grid.getScalar(x, y, z - z);
		z2 = grid.getScalar(x, y, z);
	}
	else
	{
		z1 = grid.getScalar(x, y, z - 1);
		z2 = grid.getScalar(x, y, z + 1);
	}

	gz = (z2 - z1) / (2.0f * dz);

	return glm::normalize(glm::vec3(gx, gy, gz));
}
