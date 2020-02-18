#include "UniformGrid3.h"

size_t UniformGrid3::numPoints() const
{
	return _N1 * _N2 * _N3;
}

size_t UniformGrid3::numCells() const
{
	return (_N1 - 1) * (_N2 - 1) * (_N3 - 1);
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

void UniformGrid3::getGradients(size_t i, Cube& cube) const
{
	Cell3 cell;
	Point3 point;
	getCell(i, cell);

	getPoint(cell.v0, point);
	getGradient(cube.n0, point);

	getPoint(cell.v0, point);
	getGradient(cube.n1, point);

	getPoint(cell.v0, point);
	getGradient(cube.n2, point);

	getPoint(cell.v0, point);
	getGradient(cube.n3, point);

	getPoint(cell.v0, point);
	getGradient(cube.n4, point);

	getPoint(cell.v0, point);
	getGradient(cube.n5, point);

	getPoint(cell.v0, point);
	getGradient(cube.n6, point);

	getPoint(cell.v0, point);
	getGradient(cube.n7, point);
}

void UniformGrid3::getCube(size_t i, Cube& cube) const
{
	Cell3 cell;
	Point3 point;
	getCell(i, cell);

	getPoint(cell.v0, point);
	getVertex(cell.v0, point, cube.v0);

	getPoint(cell.v1, point);
	getVertex(cell.v1, point, cube.v1);

	getPoint(cell.v2, point);
	getVertex(cell.v2, point, cube.v2);

	getPoint(cell.v3, point);
	getVertex(cell.v3, point, cube.v3);

	getPoint(cell.v4, point);
	getVertex(cell.v4, point, cube.v4);

	getPoint(cell.v5, point);
	getVertex(cell.v5, point, cube.v5);

	getPoint(cell.v6, point);
	getVertex(cell.v6, point, cube.v6);

	getPoint(cell.v7, point);
	getVertex(cell.v7, point, cube.v7);
}


// given lexicographic index, find cell vertices (quads assumed)
inline void UniformGrid3::getCell(size_t i, Cell3 & c) const
{
	size_t cell_z = i / _N12m1;
	size_t t = i - cell_z * _N12m1;
	size_t cell_y = t / (_N1 - 1);
	size_t cell_x = t % (_N1 - 1);

	size_t j = i % _N12m1;

	c.v0 = j + cell_y + cell_z * _N12;
	c.v1 = c.v0 + 1;
	c.v2 = c.v1 + _N12;
	c.v3 = c.v0 + _N12;

	c.v4 = c.v0 + _N1;
	c.v5 = c.v1 + _N1;
	c.v6 = c.v2 + _N1;
	c.v7 = c.v3 + _N1;
}

inline void UniformGrid3::getPoint(size_t i, Point3 & p) const
{
	p.z = i / _N12;
	size_t t = i - p.z * _N12;
	p.y = (t / _N1);
	p.x = t % _N1;
}

inline void UniformGrid3::getVertex(size_t i, const Point3 & point, glm::vec4 & v) const
{
	v.x = _min.x + _delta.x * point.x;
	v.y = _min.y + _delta.y * point.y;
	v.z = _min.z + _delta.z * point.z;
	v.w = _values[i];
}

inline const float UniformGrid3::getScalar(const size_t & x, const size_t & y, const size_t & z) const
{
	return _values[x + y * _N1 + z * _N1 * _N2];
}

void UniformGrid3::sample(std::function<float(float, float, float)> func)
{
	Point3 p;
	float sample = 0.0f;
	glm::vec4 v;

	for (int i = 0; i < numPoints(); i++)
	{
		getPoint(i, p);
		getVertex(i, p, v);
		sample = func(v.x, v.y, v.z);
		_values[i] = sample;
	}
}

inline void UniformGrid3::getGradient(glm::vec3& n, const Point3 & p) const
{
	float x1, x2;
	float gx;

	if (p.x == 0)
	{
		x1 = getScalar(p.x, p.y, p.z);
		x2 = getScalar(p.x + 1, p.y, p.z);
	}
	else if (p.x == _N1 - 1)
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
	else if (p.y == _N2 - 1)
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
	else if (p.z == _N3 - 1)
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

	float m = -1.0f / glm::sqrt(gx * gx + gy * gy + gz * gz);

	n.x = gx * m;
	n.y = gy * m;
	n.z = gz * m;
}
