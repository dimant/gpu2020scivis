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
	Point3 p0;
	glm::vec4 v0;
	glm::vec3 n0;

	Point3 p1;
	glm::vec4 v1;
	glm::vec3 n1;

	Point3 p2;
	glm::vec4 v2;
	glm::vec3 n2;

	Point3 p3;
	glm::vec4 v3;
	glm::vec3 n3;

	Point3 p4;
	glm::vec4 v4;
	glm::vec3 n4;

	Point3 p5;
	glm::vec4 v5;
	glm::vec3 n5;

	Point3 p6;
	glm::vec4 v6;
	glm::vec3 n6;

	Point3 p7;
	glm::vec4 v7;
	glm::vec3 n7;
};

class UniformGrid3
{
private:
	std::vector<float> _values;

	glm::vec3 _min;

	glm::vec3 _max;

	glm::vec3 _delta;

	const size_t _N12;

	const size_t _N12m1;

protected:
	//Number of points along the x− and y−axes 
	size_t _N1;
	size_t _N2;
	size_t _N3;

public:
	UniformGrid3(
		size_t N1, size_t N2, size_t N3,
		glm::vec3 min, glm::vec3 max) :
		_values(N1 * N2 * N3),
		_N1(N1), _N2(N2), _N3(N3),
		_min(min), _max(max),
		_delta((max - min) / glm::vec3(N1, N2, N3)),
		_N12(N1*N2),
		_N12m1((N1-1)*(N2-1))
	{ }

	const glm::vec3 getMin() const { return _min; }

	const glm::vec3 getMax() const { return _max; }

	size_t numPoints() const;

	size_t numCells() const;

	void getPoint(size_t i, Point3 & p) const;

	void getVertex(size_t i, const Point3 & point, glm::vec4 & v) const;

	void getCell(size_t i, Cell3 & c) const;

	void getCube(size_t i, Cube & cube) const;

	size_t getDimension1() const;

	size_t getDimension2() const;

	size_t getDimension3() const;

	const float getScalar(const size_t & x, const size_t & y, const size_t & z) const;

	void sample(std::function<float(float, float, float)> func);

	void getGradient(glm::vec3& n, const Point3 & p) const;

	void getGradients(size_t i, Cube& cube) const;
};

#endif
