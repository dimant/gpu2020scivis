#include "UniformGrid.h"

// given lexicographic index, find cell vertices (quads assumed)
void UniformGrid::getCell(size_t i, Cell & c)
{
	size_t cell_row = i / (_N1-1);
	size_t cell_col = i % (_N1-1);

	c.v1 = i + cell_row;
	c.v2 = c.v1 + 1;
	c.v3 = c.v2 + _N1;
	c.v4 = c.v1 + _N1;
}

// given 2D position p = px[0], py[1] find cell which contains it
size_t UniformGrid::findCell(const Point & p)
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

size_t UniformGrid::numPoints()
{
	return _N1 * _N2;
}

size_t UniformGrid::numCells()
{
	return (_N1 - 1) * (_N2 - 1);
}

void	 UniformGrid::getPoint(size_t i, Point & p)
{
	p.x = _m1 + (i % _N1) * _d1;
	p.y = _m2 + (i / _N1) * _d2;
}

size_t UniformGrid::getDimension1()
{
	return _N1;
}

size_t UniformGrid::getDimension2()
{
	return _N2;
}

const ScalarAttributes& UniformGrid::pointScalars()
{
	return _scalars;
}

void UniformGrid::sample(std::function<float(float, float)> func)
{
	float sample = 0.0f;
	Point p;

	for (int i = 0; i < numPoints(); i++)
	{
		getPoint(i, p);
		sample = func(p.x, p.y);
		_scalars.setC0Scalar(i, sample);
	}
}
