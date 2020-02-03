#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

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

public:
	UniformGrid(size_t N1, size_t N2, float m1, float m2, float M1, float M2) :
		_scalars(N1 * N2),
		_N1(N1), _N2(N2),
		_m1(m1), _m2(m2),
		_d1((M1 - m1) / (N1 - 1)),
		_d2((M2 - m2) / (N2 - 1))
	{ }

	size_t numPoints() 
	{ return _N1 * _N2; }

	size_t numCells()
	{ return (_N1 - 1) * (_N2 - 1); }

	void	 getPoint(int i,float* p) 
	{
		p[0] = _m1 + (i % _N1) * _d1;
		p[1] = _m2 + (i / _N1) * _d2;
	}

	int getCell(int i,int* c);

	size_t getDimension1()
	{ return _N1; }

	size_t getDimension2()
	{ return _N2; }

	int findCell(float*);

	ScalarAttributes& pointScalars()
	{ return _scalars; }
};

#endif
