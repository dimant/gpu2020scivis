#ifndef RECTILINEARGRID_H
#define RECTILINEARGRID_H
#include <vector>

#include "UniformGrid2.h"

// INPUTS
// dimsX : a float vector of world-space x-coordinates of sample points
// dimsY : a float vector of world-space y-coordinates of sample points
class RectilinearGrid2 : public UniformGrid2
{
private:
	//Sampling positions along the X and Y axes
	std::vector<float> _dX;
	std::vector<float> _dY;

public:
	RectilinearGrid2(std::vector<float> dimsX, std::vector<float> dimsY)
		: UniformGrid2(
			dimsX.size(), //number of samples along X
			dimsY.size(), //number of samples along y	
			dimsX.front(), //minimal X value
			dimsY.front(), //minimal Y value
			dimsX.back(), //maximal X value
			dimsY.back()), //maximal Y value
			_dX(dimsX), _dY(dimsY)
		{ }

	void getPoint(size_t i, Point2 &  p);
};

#endif
