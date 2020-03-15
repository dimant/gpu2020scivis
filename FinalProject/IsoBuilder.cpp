#include "IsoBuilder.h"

#include <list>
#include <vector>
#include <algorithm>

#include "VertAtt.h"

void IsoBuilder::createIsoLine(float threshold, LineStrip* lineStrip, float z)
{
	std::list<glm::vec3> list;

	size_t nx = _grid.getDimension1();
	size_t ny = _grid.getDimension2();
	size_t x, y, i = 0;

	ScalarAttributes& scalars = _grid.pointScalars();
	std::vector<int> thresholdField(_grid.numPoints());

	for (y = 0; y < ny; y++)
	{
		for (x = 0; x < nx; x++)
		{
			i = x + y * nx;
			float s = scalars.getC0Scalar(i);
			if (s > threshold)
			{
				thresholdField[i] = 1;
			}
			else
			{
				thresholdField[i] = 0;
			}
		}
	}

	Cell2 cell;
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 p4;

	int r;

	auto interpolate = [threshold] (glm::vec3 u, glm::vec3 v) {
		return (u * (v.z - threshold) + v * (threshold - u.z)) / (v.z - u.z);
	};

	for (i = 0; i < _grid.numCells(); i++)
	{
		r = 0;
		_grid.getCell(i, cell);

		r |= thresholdField[cell.v1] << 0;
		r |= thresholdField[cell.v2] << 1;
		r |= thresholdField[cell.v3] << 2;
		r |= thresholdField[cell.v4] << 3;

		_grid.getVertex(cell.v1, p1);
		_grid.getVertex(cell.v2, p2);
		_grid.getVertex(cell.v3, p3);
		_grid.getVertex(cell.v4, p4);

		switch (r)
		{
		case 0: case 15:
			break;
		case 1: case 14:
			list.push_back(interpolate(p4, p1));
			list.push_back(interpolate(p2, p1));
			break;
		case 2: case 13:
			list.push_back(interpolate(p1, p2));
			list.push_back(interpolate(p3, p2));
			break;
		case 3: case 12:
			list.push_back(interpolate(p4, p1));
			list.push_back(interpolate(p3, p2));
			break;
		case 4: case 11:
			list.push_back(interpolate(p4, p3));
			list.push_back(interpolate(p2, p3));
			break;
		case 5:
			list.push_back(interpolate(p4, p1));
			list.push_back(interpolate(p2, p1));
			list.push_back(interpolate(p4, p3));
			list.push_back(interpolate(p2, p3));
			break;
		case 6: case 9:
			list.push_back(interpolate(p4, p3));
			list.push_back(interpolate(p1, p2));
			break;
		case 7: case 8:
			list.push_back(interpolate(p4, p1));
			list.push_back(interpolate(p4, p3));
			break;
		case 10:
			list.push_back(interpolate(p1, p4));
			list.push_back(interpolate(p3, p4));
			list.push_back(interpolate(p1, p2));
			list.push_back(interpolate(p3, p2));
			break;
		}
	}

	size_t ndata = sizeof(VertAtt) * list.size();
	VertAtt* data = new VertAtt[ndata];

	i = 0;
	for (auto v : list)
	{
		v.z = z;
		data[i].vertex = v;
		data[i].normal = glm::vec3(0.0f, 1.0f, 0.0f);
		data[i].texel = glm::vec2(0.0f);
		data[i].material = glm::vec3(0.1f, 12.0f, 2.0f);
		i++;
	}

	lineStrip->reset(ndata, data);
}