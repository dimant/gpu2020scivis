#include "DataBuilder.h"

#include "polygonise.h"

#include "VertAtt.h"

#include "ddsbase.h"

#define ROUNDINT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))

std::shared_ptr<Model> DataBuilder::createData(GLuint program, float isolevel, char* filename)
{

	unsigned char *data;
	unsigned int width, height, depth;
	unsigned int components;
	float scalex, scaley, scalez;
	unsigned char* description;
	unsigned char* courtesy;
	unsigned char* paramter;
	unsigned char* comment;

	const char* fname = "C:\\Users\\diman\\Downloads\\CT-Chest.pvm";

	data = readPVMvolume(fname,
		&width, &height, &depth,
		&components,
		&scalex, &scaley, &scalez,
		&description, &courtesy, &paramter, &comment);

	UniformGrid3 grid(
		width, height, depth,
		glm::vec3(0.0f),
		glm::vec3(width*scalex, height*scaley, depth*scalez));

	auto loader = [data, width, height, depth](size_t x, size_t y, size_t z) {
		int _x = ROUNDINT(x);
		int _y = ROUNDINT(y);
		int _z = ROUNDINT(z);
		return (float)data[_x + (_y + _z * height) * width];
	};

	grid.sample(loader);

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

				va.vertex -= glm::vec3(width/2, height/2, depth/2);

				va.normal.x = buffer[j * 6 + 3];
				va.normal.y = buffer[j * 6 + 4];
				va.normal.z = buffer[j * 6 + 5];

				va.material = material; +
				va.texel = glm::vec2(0.0f);
				vertices.push_back(va);
			}
		}
	}

	VertAtt* output = new VertAtt[vertices.size()];
	std::copy(vertices.begin(), vertices.end(), output);

	return std::make_shared<Model>(program, sizeof(VertAtt) * vertices.size(), output, "textures\\sphere.jpg");
}

float fbm(float x, float y)
{
	float amplitude = 1.;
	float frequency = 1.;
	float z = sin(x * frequency);
	float t = 0.01*(-y * 130.0);
	z += sin(x*frequency*2.1 + t)*4.5;
	z += sin(x*frequency*1.72 + t * 1.121)*4.0;
	z += sin(x*frequency*2.221 + t * 0.437)*5.0;
	z += sin(x*frequency*3.1122 + t * 4.269)*2.5;
	z *= amplitude * 0.06;
	return z;
}

std::shared_ptr<Model> DataBuilder::createData(GLuint program, float isolevel)
{
	UniformGrid3 grid(70, 70, 70, glm::vec3(0.0f), glm::vec3(10.0f));

	glm::vec3 center = (grid.getMax() - grid.getMin()) / 2.0f;

	// creates a 'sphere' by returning the distance from a given center
	//// which can then be thresholded to the desired size
	//auto scienceFunction = [center](float x, float y, float z) {
	//	return glm::length(glm::vec3(x, y, z) - center);
	//};

	auto scienceFunction = [center](float x, float y, float z) {
		float f = 3.0f;
		return glm::length(glm::vec3(x, y, z) - center) + 
			sin(x * f) + 
			sin(y * f) +
			sin(z * f);
	};


	auto normalFunction = [scienceFunction](glm::vec3 p) {
		glm::vec3 n;
		n.x = scienceFunction(p.x - 0.01, p.y, p.z) - scienceFunction(p.x + 0.01, p.y, p.z);
		n.y = scienceFunction(p.x, p.y - 0.01, p.z) - scienceFunction(p.x, p.y + 0.01, p.z);
		n.z = scienceFunction(p.x, p.y, p.z - 0.01) - scienceFunction(p.x, p.y, p.z + 0.01);
		return glm::normalize(n);
	};

	grid.sample(scienceFunction);

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

				va.vertex -= glm::vec3(5.0f);

				va.normal.x = buffer[j * 6 + 3];
				va.normal.y = buffer[j * 6 + 4];
				va.normal.z = buffer[j * 6 + 5];

				//va.normal = normalFunction(va.vertex);

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
