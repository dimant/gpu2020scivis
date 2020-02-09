#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include <functional>

#include "Grid.h"
#include "ScalarAttributes.h"

class UniformGrid : public Grid
{
private:
	//Cell sizes in this grid
	float _d1;
	float _d2;

protected:
	ScalarAttributes _scalars;

	//Number of points along the x− and y−axes 
	size_t _N1;
	size_t _N2;

	//Minimal coordinate values in this grid
	float _m1;
	float _m2;

	float _M1;
	float _M2;

public:
	UniformGrid(size_t N1, size_t N2, float m1, float m2, float M1, float M2) :
		_scalars(N1 * N2),
		_N1(N1), _N2(N2),
		_m1(m1), _m2(m2),
		_M1(M1), _M2(M2),
		_d1((M1 - m1) / (N1 - 1)),
		_d2((M2 - m2) / (N2 - 1))
	{ }

	size_t numPoints();

	size_t numCells();

	virtual void	 getPoint(size_t i, Point & p);

	void getCell(size_t i, Cell & c);

	size_t getDimension1();

	size_t getDimension2();

	size_t findCell(const Point & p);

	const ScalarAttributes& pointScalars();

	void sample(std::function<float(float, float)> func);
};

#endif