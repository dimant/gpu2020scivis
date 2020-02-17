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

void UniformGrid3::getCube(size_t i, Cube& quad) const
{
	Cell3 cell;
	Point3 p;
	getCell(i, cell);

	getVertex(cell.v0, quad.v0);
	getPoint(cell.v0, p);
	getGradient(quad.n0, p.x, p.y, p.z);

	getVertex(cell.v1, quad.v1);
	getPoint(cell.v1, p);
	getGradient(quad.n1, p.x, p.y, p.z);

	getVertex(cell.v2, quad.v2);
	getPoint(cell.v2, p);
	getGradient(quad.n2, p.x, p.y, p.z);

	getVertex(cell.v3, quad.v3);
	getPoint(cell.v3, p);
	getGradient(quad.n3, p.x, p.y, p.z);

	getVertex(cell.v4, quad.v4);
	getPoint(cell.v4, p);
	getGradient(quad.n4, p.x, p.y, p.z);

	getVertex(cell.v5, quad.v5);
	getPoint(cell.v5, p);
	getGradient(quad.n5, p.x, p.y, p.z);

	getVertex(cell.v6, quad.v6);
	getPoint(cell.v6, p);
	getGradient(quad.n6, p.x, p.y, p.z);

	getVertex(cell.v7, quad.v7);
	getPoint(cell.v7, p);
	getGradient(quad.n7, p.x, p.y, p.z);
}

void UniformGrid3::getVertex(size_t i, glm::vec4 & v) const
{
	Point3 p;
	getPoint(i, p);

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

void UniformGrid3::sample(std::function<float(size_t, size_t, size_t)> func)
{
	float sample = 0.0f;
	Point3 p;

	for (int i = 0; i < numPoints(); i++)
	{
		getPoint(i, p);
		sample = func(p.x, p.y, p.z);
		_scalars.setC0Scalar(i, sample);
	}
}

void UniformGrid3::getGradient(glm::vec3& n,
	const size_t & x, const size_t & y, const size_t & z) const
{
	float x1, x2;
	float gx;

	if (x == 0)
	{
		x1 = getScalar(x, y, z);
		x2 = getScalar(x + 1, y, z);
	}
	else if (x == getDimension1() - 1)
	{
		x1 = getScalar(x - 1, y, z);
		x2 = getScalar(x, y, z);
	}
	else
	{
		x1 = getScalar(x - 1, y, z);
		x2 = getScalar(x + 1, y, z);
	}

	gx = (x2 - x1);

	float y1, y2;
	float gy;

	if (y == 0)
	{
		y1 = getScalar(x, y, z);
		y2 = getScalar(x, y + 1, z);
	}
	else if (y == getDimension2() - 1)
	{
		y1 = getScalar(x, y - 1, z);
		y2 = getScalar(x, y, z);
	}
	else
	{
		y1 = getScalar(x, y - 1, z);
		y2 = getScalar(x, y + 1, z);
	}

	gy = (y2 - y1);

	float z1, z2;
	float gz;

	if (z == 0)
	{
		z1 = getScalar(x, y, z);
		z2 = getScalar(x, y, z + 1);
	}
	else if (z == getDimension3() - 1)
	{
		z1 = getScalar(x, y, z - z);
		z2 = getScalar(x, y, z);
	}
	else
	{
		z1 = getScalar(x, y, z - 1);
		z2 = getScalar(x, y, z + 1);
	}

	gz = (z2 - z1);

	n = glm::normalize(glm::vec3(gx, gy, gz));
}
