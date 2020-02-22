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

void UniformGrid3::getGradients(Cube& cube) const
{
	getGradient(cube.n0, cube.p0);

	getGradient(cube.n1, cube.p1);

	getGradient(cube.n2, cube.p2);

	getGradient(cube.n3, cube.p3);

	getGradient(cube.n4, cube.p4);

	getGradient(cube.n5, cube.p5);

	getGradient(cube.n6, cube.p6);

	getGradient(cube.n7, cube.p7);
}

void UniformGrid3::getCube(size_t i, Cube& cube) const
{
	Cell3 cell;
	getCell(i, cell);

	getPoint(cell.v0, cube.p0);
	getVertex(cell.v0, cube.p0, cube.v0);

	cube.p1.x = cube.p0.x + 1;
	cube.p1.y = cube.p0.y;
	cube.p1.z = cube.p0.z;
	getVertex(cell.v1, cube.p1, cube.v1);

	cube.p2.x = cube.p1.x;
	cube.p2.y = cube.p1.y;
	cube.p2.z = cube.p1.z + 1;
	getVertex(cell.v2, cube.p2, cube.v2);

	cube.p3.x = cube.p2.x - 1;
	cube.p3.y = cube.p2.y;
	cube.p3.z = cube.p2.z;
	getVertex(cell.v3, cube.p3, cube.v3);

	cube.p4.x = cube.p0.x;
	cube.p4.y = cube.p0.y + 1;
	cube.p4.z = cube.p0.z;
	getVertex(cell.v4, cube.p4, cube.v4);

	cube.p5.x = cube.p4.x + 1;
	cube.p5.y = cube.p4.y;
	cube.p5.z = cube.p4.z;
	getVertex(cell.v5, cube.p5, cube.v5);

	cube.p6.x = cube.p5.x;
	cube.p6.y = cube.p5.y;
	cube.p6.z = cube.p5.z + 1;
	getVertex(cell.v6, cube.p6, cube.v6);

	cube.p7.x = cube.p6.x - 1;
	cube.p7.y = cube.p6.y;
	cube.p7.z = cube.p6.z;
	getVertex(cell.v7, cube.p7, cube.v7);
}

// given lexicographic index, find cell vertices (quads assumed)
inline void UniformGrid3::getCell(size_t i, Cell3 & c) const
{
	size_t cell_z = i / _divN12m1;
	size_t t = i - cell_z * _N12m1;
	size_t cell_y = t / _divN1m1;
	size_t cell_x = t - cell_y * _N1m1;

	c.v0 = i + cell_z * _N1p2 - cell_z + cell_y;
	
	c.v1 = c.v0 + 1;
	c.v3 = c.v0 + _N12;
	c.v4 = c.v0 + _N1;

	c.v2 = c.v1 + _N12;
	c.v5 = c.v1 + _N1;

	c.v6 = c.v2 + _N1;
	c.v7 = c.v3 + _N1;
}

inline void UniformGrid3::getPoint(size_t i, Point3 & p) const
{
	p.z = i / _divN12;
	size_t t = i - p.z * _N12;
	p.y = (t / _divN1);
	p.x = t - p.y * _N1;
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
	return _values[x + (y + z * _N2) * _N1];
}

void UniformGrid3::sample(std::function<float(size_t)> func)
{
	for (int i = 0; i < numPoints(); i++)
	{
		_values[i] = func(i);
	}
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

// function to find the inverse square root
// https://www.geeksforgeeks.org/fast-inverse-square-root/
inline float inverse_rsqrt(const float & number)
{
	const float x2 = number * 0.5F;

	float y = number;

	// evil floating point bit level hacking 
	// value is pre-assumed 
	const long i = 0x5f3759df - ((*(long *)&y) >> 1);

	y = *(float *)&i;

	// 1st iteration 
	y = y * (1.5F - (x2 * y * y));

	return y;
}

inline void UniformGrid3::getGradient(glm::vec3& n, const Point3 & p) const
{
	float gx;
	float gy;
	float gz;

	if (p.x == 0)
	{
		gx = getScalar(p.x + 1, p.y, p.z) - getScalar(p.x, p.y, p.z);
	}
	else if (p.x == _N1m1)
	{
		gx = getScalar(p.x, p.y, p.z) - getScalar(p.x - 1, p.y, p.z);
	}
	else
	{
		gx = getScalar(p.x + 1, p.y, p.z) - getScalar(p.x - 1, p.y, p.z);
	}

	if (p.y == 0)
	{
		gy = getScalar(p.x, p.y + 1, p.z) - getScalar(p.x, p.y, p.z);
	}
	else if (p.y == _N2m1)
	{
		gy = getScalar(p.x, p.y, p.z) - getScalar(p.x, p.y - 1, p.z);
	}
	else
	{
		gy = getScalar(p.x, p.y + 1, p.z) - getScalar(p.x, p.y - 1, p.z);
	}


	if (p.z == 0)
	{
		gz = getScalar(p.x, p.y, p.z + 1) - getScalar(p.x, p.y, p.z);
	}
	else if (p.z == _N3m1)
	{
		gz = getScalar(p.x, p.y, p.z) - getScalar(p.x, p.y, p.z - p.z);
	}
	else
	{
		gz = getScalar(p.x, p.y, p.z + 1) - getScalar(p.x, p.y, p.z - 1);
	}

	float m = -inverse_rsqrt(gx * gx + gy * gy + gz * gz);

	n.x = gx * m;
	n.y = gy * m;
	n.z = gz * m;
}
