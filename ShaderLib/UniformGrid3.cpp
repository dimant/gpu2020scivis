#include "UniformGrid3.h"


// given lexicographic index, find cell vertices (quads assumed)
void UniformGrid3::getCell(size_t i, Cell3 & c) const
{
	size_t cell_z = i / ((_N1 - 1) * (_N2 - 1));
	size_t t = i - cell_z * (_N1 - 1) * (_N2 - 1);
	size_t cell_y = t / (_N1 - 1);
	size_t cell_x = t % (_N1 - 1);

	size_t j = i % ((_N1 - 1) * (_N2 - 1));

	c.v0 = j + cell_y + cell_z * _N1 * _N2;
	c.v1 = c.v0 + 1;
	c.v2 = c.v1 + _N1 * _N2;
	c.v3 = c.v0 + _N1 * _N2;

	c.v4 = c.v0 + _N1;
	c.v5 = c.v1 + _N1;
	c.v6 = c.v2 + _N1;
	c.v7 = c.v3 + _N1;
}

size_t UniformGrid3::numPoints() const
{
	return _N1 * _N2 * _N3;
}

size_t UniformGrid3::numCells() const
{
	return (_N1 - 1) * (_N2 - 1) * (_N3 - 1);
}

void UniformGrid3::getPoint(size_t i, Point3 & p) const
{
	p.z = i / (_N1 * _N2);
	size_t t = i - p.z * (_N1 * _N2);
	p.y = (t / _N1);
	p.x = t % _N1;
}

size_t UniformGrid3::getDimension1() const
{
	return _N1;
}

size_t UniformGrid3::getDimension2() const
{
	return _N2;
}

size_t UniformGrid3::getDimension3() const
{
	return _N3;
}

ScalarAttributes& UniformGrid3::pointScalars()
{
	return _scalars;
}

void UniformGrid3::getCube(size_t i, Cube& cube) const
{
	Cell3 cell;
	getCell(i, cell);

	getVertex(cell.v0, cube.v0);
	getGradient(cube.n0, i);

	getVertex(cell.v1, cube.v1);
	getGradient(cube.n1, i);

	getVertex(cell.v2, cube.v2);
	getGradient(cube.n2, i);

	getVertex(cell.v3, cube.v3);
	getGradient(cube.n3, i);

	getVertex(cell.v4, cube.v4);
	getGradient(cube.n4, i);

	getVertex(cell.v5, cube.v5);
	getGradient(cube.n5, i);

	getVertex(cell.v6, cube.v6);
	getGradient(cube.n6, i);

	getVertex(cell.v7, cube.v7);
	getGradient(cube.n7, i);
}

void UniformGrid3::getVertex(size_t i, glm::vec4 & v) const
{
	Point3 point;
	getPoint(i, point);
	glm::vec3 p = _min + _delta * glm::vec3(point.x, point.y, point.z);

	v.x = p.x;
	v.y = p.y;
	v.z = p.z;
	v.w = _scalars.getC0Scalar(i);
}

const float UniformGrid3::getScalar(const size_t & x, const size_t & y, const size_t & z) const
{
	size_t i = x + y * _N1 + z * _N1 * _N2;

	return _scalars.getC0Scalar(i);
}

void UniformGrid3::sample(std::function<float(float, float, float)> func)
{
	float sample = 0.0f;
	glm::vec4 v;

	for (int i = 0; i < numPoints(); i++)
	{
		getVertex(i, v);
		sample = func(v.x, v.y, v.z);
		_scalars.setC0Scalar(i, sample);
	}
}

void UniformGrid3::getGradient(glm::vec3& n, size_t i) const
{
	float x1, x2;
	float gx;
	Point3 p;

	getPoint(i, p);

	if (p.x == 0)
	{
		x1 = getScalar(p.x, p.y, p.z);
		x2 = getScalar(p.x + 1, p.y, p.z);
	}
	else if (p.x == getDimension1() - 1)
	{
		x1 = getScalar(p.x - 1, p.y, p.z);
		x2 = getScalar(p.x, p.y, p.z);
	}
	else
	{
		x1 = getScalar(p.x - 1, p.y, p.z);
		x2 = getScalar(p.x + 1, p.y, p.z);
	}

	gx = (x2 - x1);

	float y1, y2;
	float gy;

	if (p.y == 0)
	{
		y1 = getScalar(p.x, p.y, p.z);
		y2 = getScalar(p.x, p.y + 1, p.z);
	}
	else if (p.y == getDimension2() - 1)
	{
		y1 = getScalar(p.x, p.y - 1, p.z);
		y2 = getScalar(p.x, p.y, p.z);
	}
	else
	{
		y1 = getScalar(p.x, p.y - 1, p.z);
		y2 = getScalar(p.x, p.y + 1, p.z);
	}

	gy = (y2 - y1);

	float z1, z2;
	float gz;

	if (p.z == 0)
	{
		z1 = getScalar(p.x, p.y, p.z);
		z2 = getScalar(p.x, p.y, p.z + 1);
	}
	else if (p.z == getDimension3() - 1)
	{
		z1 = getScalar(p.x, p.y, p.z - p.z);
		z2 = getScalar(p.x, p.y, p.z);
	}
	else
	{
		z1 = getScalar(p.x, p.y, p.z - 1);
		z2 = getScalar(p.x, p.y, p.z + 1);
	}

	gz = (z2 - z1);

	n = glm::normalize(glm::vec3(gx, gy, gz));
}
