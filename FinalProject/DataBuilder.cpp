#include "DataBuilder.h"

#include "polygonise.h"

#include "VertAtt.h"

std::shared_ptr<Model> DataBuilder::createData(GLuint program, UniformGrid3 & grid)
{
	glm::vec3 center = (grid.getMax() - grid.getMin()) / 2.0f;

	// creates a 'sphere' by returning the distance from a given center
	// which can then be thresholded to the desired size
	auto scienceFunction = [center](float x, float y, float z) {
		return glm::length(glm::vec3(x, y, z) - center);
	};

	grid.sample(scienceFunction);

	float isolevel = 1.5f;

	float buffer[90];
	size_t nfloats;
	Cube cube;
	auto material = glm::vec3(0.1f, 12.0f, 2.0f);

	std::vector<VertAtt> vertices;

	for (size_t i = 0; i < grid.numCells(); i++)
	{
		grid.getCube(i, cube);

		nfloats = polygonise(cube, isolevel, buffer);

		if (nfloats > 0)
		{
			for (int j = 0; j < nfloats / 6; j++)
			{
				VertAtt va;
				va.vertex.x = buffer[j * 6 + 0];
				va.vertex.y = buffer[j * 6 + 1];
				va.vertex.z = buffer[j * 6 + 2];

				va.normal.x = buffer[j * 6 + 3];
				va.normal.y = buffer[j * 6 + 4];
				va.normal.z = buffer[j * 6 + 5];

				va.material = material;+
				va.texel = glm::vec2(0.0f);
				vertices.push_back(va);
			}
		}
	}

	VertAtt* data = new VertAtt[vertices.size()];
	std::copy(vertices.begin(), vertices.end(), data);

	return std::make_shared<Model>(program, sizeof(VertAtt) * vertices.size(), data, "textures\\sphere.jpg");
}
