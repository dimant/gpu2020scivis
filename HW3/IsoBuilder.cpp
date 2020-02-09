#include "IsoBuilder.h"

#include <vector>

std::shared_ptr<LineStrip> IsoBuilder::createIsoLine(
	GLuint program,
	UniformGrid & grid,
	float threshold)
{
	std::vector<glm::vec3> data(2);

	data.push_back(glm::vec3(-3.0f, -3.0f, -3.0f));
	data.push_back(glm::vec3(3.0f, 3.0f, 3.0f));

	return std::make_shared<LineStrip>(program, sizeof(glm::vec3) * data.size(), &data[0]);
}