#include "UniformGrid.h"

// given lexicographic index, find cell vertices (quads assumed)
int	UniformGrid::getCell(int i, int* v)
{
	size_t cell_row = i / (_N1-1);
	size_t cell_col = i % (_N1-1);
	
	v[0] = i + (int) cell_row;
	v[1] = v[0] + 1;
	v[2] = v[1] + (int)_N1;
	v[3] = v[0] + (int)_N1;
	
	return 4;
}

// given 2D position p = px[0], py[1] find cell which contains it
int UniformGrid::findCell(float* p)
{
	int C[2];

	//compute cell coordinates C[0] ,C[1]
	C[0] = (int) floor((p[0] - _m1) * _N1 / _d1);
	C[1] = (int) floor((p[1] - _m2) * _N2 / _d2);

	//test if p is inside the dataset
	if (C[0] < 0 || C[0] >= _N1 - 1 || C[1] < 0 || C[1] >= _N2 - 1)
	{
		return -1;
	}
	else
	{
		//go from cell coordinates to cell index
		return C[0] + C[1] * (int) _N1;
	}
}
