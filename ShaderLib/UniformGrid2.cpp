#include "UniformGrid2.h"

#include "triangulation.h"

// given lexicographic index, find cell vertices (quads assumed)
void UniformGrid2::getCell(size_t i, Cell2 & c)
{
	size_t cell_row = i / (_N1-1);
	size_t cell_col = i % (_N1-1);

	c.v1 = i + cell_row;
	c.v2 = c.v1 + 1;
	c.v3 = c.v2 + _N1;
	c.v4 = c.v1 + _N1;
}

// given 2D position p = px[0], py[1] find cell which contains it
size_t UniformGrid2::findCell(const Point2 & p)
{
	size_t n1, n2;

	//test if p is inside the dataset
	if (p.x < _m1 || p.x >= _N1 - 1 || p.y < _m2 || p.y >= _N2 - 1)
	{
		return -1;
	}

	//compute cell coordinates C[0] ,C[1]
	n1 = (size_t) floor((p.x - _m1) * _N1 / _d1);
	n2 = (size_t) floor((p.x - _m2) * _N2 / _d2);

	//go from cell coordinates to cell index
	return n1 + n2 * _N1;
}

size_t UniformGrid2::numPoints()
{
	return _N1 * _N2;
}

size_t UniformGrid2::numCells()
{
	return (_N1 - 1) * (_N2 - 1);
}

size_t UniformGrid2::numVertices()
{
	// 2 tris, 3 vertices each
	return numCells() * 2 * 3;
}

void UniformGrid2::getPoint(size_t i, Point2 & p)
{
	p.x = _m1 + (i % _N1) * _d1;
	p.y = _m2 + (i / _N1) * _d2;
}

size_t UniformGrid2::getDimension1()
{
	return _N1;
}

glm::vec2 UniformGrid2::getRange1()
{
	return glm::vec2(_m1, _M1);
}

size_t UniformGrid2::getDimension2()
{
	return _N2;
}

glm::vec2 UniformGrid2::getRange2()
{
	return glm::vec2(_m2, _M2);
}

ScalarAttributes& UniformGrid2::pointScalars()
{
	return _scalars;
}

void UniformGrid2::getVertex(size_t i, glm::vec3 & v)
{
	Point2 p;
	getPoint(i, p);

	v.x = p.x;
	v.y = p.y;
	v.z = _scalars.getC0Scalar(i);
}

void UniformGrid2::getQuad(size_t i, Quad & quad)
{
	Cell2 cell;
	getCell(i, cell);

	getVertex(cell.v1, quad.v1);
	getVertex(cell.v2, quad.v2);
	getVertex(cell.v3, quad.v3);
	getVertex(cell.v4, quad.v4);
}

void UniformGrid2::getTris(float* data)
{
	int i;
	Quad q;
	float* cursor = data;

	for (i = 0; i < numCells(); i++)
	{
		getQuad(i, q);

		cursor += triangulate(q, cursor);
	}
}

void UniformGrid2::sample(std::function<float(float, float)> func)
{
	float sample = 0.0f;
	Point2 p;

	for (int i = 0; i < numPoints(); i++)
	{
		getPoint(i, p);
		sample = func(p.x, p.y);
		_scalars.setC0Scalar(i, sample);
	}
}
