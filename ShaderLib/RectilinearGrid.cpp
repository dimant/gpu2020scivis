#include "RectilinearGrid.h"

void	 RectilinearGrid::getPoint(size_t i, Point &  p)
{
	//Compute vertex grid-coordinates row, col
	size_t row = i / _N1;
	size_t col = i % _N1;

	//Find actual vertex coordinates using the sampling-steps stored in dX[],dY[] for the X and Y axes
	p.x = _dX[col];
	p.y = _dY[row];
}
