#ifndef UNIFORMGRID3_H
#define UNIFORMGRID3_H

#include <functional>

#include <glm/glm.hpp>

#include "ScalarAttributes.h"

struct Point3
{
	size_t x;
	size_t y;
	size_t z;
};

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
	glm::vec3 n0;

	glm::vec4 v1;
	glm::vec3 n1;

	glm::vec4 v2;
	glm::vec3 n2;

	glm::vec4 v3;
	glm::vec3 n3;

	glm::vec4 v4;
	glm::vec3 n4;

	glm::vec4 v5;
	glm::vec3 n5;

	glm::vec4 v6;
	glm::vec3 n6;

	glm::vec4 v7;
	glm::vec3 n7;
};

class UniformGrid3
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

	glm::vec3 _min;

	glm::vec3 _max;

	glm::vec3 _delta;

public:
	UniformGrid3(
		size_t N1, size_t N2, size_t N3,
		glm::vec3 min, glm::vec3 max) :
		_scalars(N1 * N2 * N3),
		_N1(N1), _N2(N2), _N3(N3),
		_min(min), _max(max),
		_delta((max - min) / glm::vec3(N1, N2, N3))
	{ }

	const glm::vec3 getMin() const { return _min; }

	const glm::vec3 getMax() const { return _max; }

	size_t numPoints() const;

	size_t numCells() const;

	virtual void getPoint(size_t i, Point3 & p) const;

	virtual void getVertex(size_t i, glm::vec4 & v) const;

	void getCell(size_t i, Cell3 & c) const;

	void getCube(size_t i, Cube & cube) const;

	size_t getDimension1() const;

	size_t getDimension2() const;

	size_t getDimension3() const;

	const float getScalar(const size_t & x, const size_t & y, const size_t & z) const;

	virtual void getTris(float * data) { }

	ScalarAttributes& pointScalars();

	void sample(std::function<float(float, float, float)> func);

	void getGradient(glm::vec3& n, size_t i) const;
};

#endif
