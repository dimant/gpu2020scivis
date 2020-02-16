#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include <functional>

#include "Grid.h"
#include "ScalarAttributes.h"

typedef glm::vec2 Point2;

struct Cell2
{
	size_t v1;
	size_t v2;
	size_t v3;
	size_t v4;
};

struct Quad
{
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 v4;
};

class UniformGrid2 : public Grid
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
	UniformGrid2(size_t N1, size_t N2, float m1, float m2, float M1, float M2) :
		_scalars(N1 * N2),
		_N1(N1), _N2(N2),
		_m1(m1), _m2(m2),
		_M1(M1), _M2(M2),
		_d1((M1 - m1) / (N1 - 1)),
		_d2((M2 - m2) / (N2 - 1))
	{ }

	size_t numPoints();

	size_t numCells();

	size_t numVertices();

	virtual void getPoint(size_t i, Point2 & p);

	virtual void getVertex(size_t i, glm::vec3 & v);

	void getCell(size_t i, Cell2 & c);

	void getQuad(size_t i, Quad & quad);

	size_t getDimension1();

	glm::vec2 getRange1();

	size_t getDimension2();

	glm::vec2 getRange2();

	size_t findCell(const Point2 & p);

	void getTris(float * data);

	ScalarAttributes& pointScalars();

	void sample(std::function<float(float, float)> func);
};

#endif
