#include "UniformGrid3.h"


// given lexicographic index, find cell vertices (quads assumed)
void UniformGrid3::getCell(size_t i, Cell3 & c)
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

size_t UniformGrid3::numPoints()
{
	return _N1 * _N2 * _N3;
}

size_t UniformGrid3::numCells()
{
	return (_N1 - 1) * (_N2 - 1) * (_N3 - 1);
}

void UniformGrid3::getPoint(size_t i, Point3 & p)
{
	p.z = i / (_N1 * _N2);
	size_t t = i - p.z * (_N1 * _N2);
	p.y = (t / _N1);
	p.x = t % _N1;
}

size_t UniformGrid3::getDimension1()
{
	return _N1;
}

glm::vec2 UniformGrid3::getRange1()
{
	return glm::vec2(_m1, _M1);
}

size_t UniformGrid3::getDimension2()
{
	return _N2;
}

glm::vec2 UniformGrid3::getRange2()
{
	return glm::vec2(_m2, _M2);
}


size_t UniformGrid3::getDimension3()
{
	return _N3;
}

glm::vec2 UniformGrid3::getRange3()
{
	return glm::vec2(_m3, _M3);
}

ScalarAttributes& UniformGrid3::pointScalars()
{
	return _scalars;
}

void UniformGrid3::getCube(size_t i, Cube& quad)
{
	Cell3 cell;
	getCell(i, cell);

	getVertex(cell.v0, quad.v0);
	getVertex(cell.v1, quad.v1);
	getVertex(cell.v2, quad.v2);
	getVertex(cell.v3, quad.v3);

	getVertex(cell.v4, quad.v4);
	getVertex(cell.v5, quad.v5);
	getVertex(cell.v6, quad.v6);
	getVertex(cell.v7, quad.v7);
}

void UniformGrid3::getVertex(size_t i, glm::vec4 & v)
{
	Point3 p;
	getPoint(i, p);

	v.x = p.x;
	v.y = p.y;
	v.z = p.z;
	v.w = _scalars.getC0Scalar(i);
}

void UniformGrid3::sample(std::function<float(float, float, float)> func)
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
