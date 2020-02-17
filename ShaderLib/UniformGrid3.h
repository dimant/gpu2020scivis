#ifndef UNIFORMGRID3_H
#define UINFORMGRID3_H

#include <functional>

#include "Grid.h"
#include "ScalarAttributes.h"

typedef glm::vec3 Point3;

struct Cell3
{
	size_t v0;
	size_t v1;
	size_t v2;
	size_t v3;

	size_t v4;
	size_t v5;
	size_t v6;
	size_t v7;
};

struct Cube
{
	glm::vec4 v0;
	glm::vec4 v1;
	glm::vec4 v2;
	glm::vec4 v3;

	glm::vec4 v4;
	glm::vec4 v5;
	glm::vec4 v6;
	glm::vec4 v7;
};

class UniformGrid3 : public Grid
{
private:
	//Cell sizes in this grid
	float _d1;
	float _d2;
	float _d3;

protected:
	ScalarAttributes _scalars;

	//Number of points along the x− and y−axes 
	size_t _N1;
	size_t _N2;
	size_t _N3;

	//Minimal coordinate values in this grid
	float _m1;
	float _m2;
	float _m3;

	float _M1;
	float _M2;
	float _M3;

public:
	UniformGrid3(
		size_t N1, size_t N2, size_t N3,
		glm::vec3 m,
		glm::vec3 M) :
		_scalars(N1 * N2 * N3),
		_N1(N1), _N2(N2), _N3(N3),
		_m1(m.x), _m2(m.y), _m3(m.z),
		_M1(M.x), _M2(M.y), _M3(M.z),
		_d1((M.x - m.x) / (N1 - 1)),
		_d2((M.y - m.y) / (N2 - 1)),
		_d3((M.z - m.z) / (N3 - 1))
	{ }

	size_t numPoints() const;

	size_t numCells() const;

	virtual void getPoint(size_t i, Point3 & p) const;

	virtual void getVertex(size_t i, glm::vec4 & v) const;

	void getCell(size_t i, Cell3 & c) const;

	void getCube(size_t i, Cube & quad) const;

	size_t getDimension1() const;

	glm::vec2 getRange1() const;

	float getDelta1() const { return _d1; }

	size_t getDimension2() const;

	glm::vec2 getRange2() const;

	float getDelta2() const { return _d2; }

	size_t getDimension3() const;

	glm::vec2 getRange3() const;

	float getDelta3() const { return _d3; }

	const float getScalar(size_t x, size_t y, size_t z) const;

	virtual void getTris(float * data) { }

	ScalarAttributes& pointScalars();

	void sample(std::function<float(float, float, float)> func);
};

#endif
