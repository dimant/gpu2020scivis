#include "DataBuilder.h"

#include <list>

#include "polygonise.h"

#include "VertAtt.h"

#include "ddsbase.h"

#include "triangulation.h"

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

	if (components == 2)
	{
		data = quantize(data, width, height, depth, true, false, false);
	}

	glm::vec3 gmin(0.0f);

	unsigned int max_side = max3(width, height, depth);
	float factor = 15.0 / (float)max_side;

	glm::vec3 gmax(width*scalex, height*scaley, depth*scalez);
	gmax *= factor;

	glm::vec3 gmid = (gmax + gmin) / 2.0f;
	glm::vec3 gdelta = (gmax - gmin) / glm::vec3(width, height, depth);
	//glm::vec3 idelta = 1.0f / gdelta;

	UniformGrid3 grid(width, height, depth, gmin, gmax);

	//auto loader = [data, width, height, depth, idelta](float x, float y, float z) {
	//	int _x = ROUNDINT(x * idelta.x);
	//	int _y = ROUNDINT(y * idelta.y);
	//	int _z = ROUNDINT(z * idelta.z);
	//	return (float)data[_x + (_y + _z * height) * width];
	//};

	auto loader = [data](size_t i) { return (float)data[i]; };

	grid.sample(loader);

	auto material = glm::vec3(0.1f, 12.0f, 2.0f);

	std::vector<VertAtt> vertices;
	vertices.reserve(grid.numCells() / 2);
	size_t ncells = grid.numCells();
	glm::vec2 texel = glm::vec2(0.0f);

	float buffer[90];
	size_t nfloats;
	Cube cube;
	int cubeindex;

	for (size_t i = 0; i < ncells; i++)
	{
		grid.getCube(i, cube);

		/*
		   Determine the index into the edge table which
		   tells us which vertices are inside of the surface
		*/
		getCubeIndex(cubeindex, cube, isolevel);

		if (cubeindex != 0)
		{
			grid.getGradients(cube);
			nfloats = polygonise(cube, cubeindex, isolevel, buffer);

			for (int j = 0; j < nfloats / 6; j++)
			{
				VertAtt va;
				va.vertex.x = buffer[j * 6 + 0];
				va.vertex.y = buffer[j * 6 + 1];
				va.vertex.z = buffer[j * 6 + 2];

				va.vertex -= gmid;

				va.normal.x = buffer[j * 6 + 3];
				va.normal.y = buffer[j * 6 + 4];
				va.normal.z = buffer[j * 6 + 5];

				va.material = material;
				va.texel = texel;
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
	glm::vec3 gmin(-5.0f);
	glm::vec3 gmax(5.0f);
	glm::vec3 gmid = (gmax + gmin) / 2.0f;
	UniformGrid3 grid(70, 70, 70, gmin, gmax);

	// creates a 'sphere' by returning the distance from a given center
	//// which can then be thresholded to the desired size
	auto scienceFunction = [gmid](float x, float y, float z) {
		return glm::length(glm::vec3(x, y, z) - gmid);
	};

	//auto scienceFunction = [center](float x, float y, float z) {
	//	float f = 3.0f;
	//	return glm::length(glm::vec3(x, y, z) - center) + 
	//		sin(x * f) + 
	//		sin(y * f) +
	//		sin(z * f);
	//};


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
	int cubeindex;
	auto material = glm::vec3(0.1f, 12.0f, 2.0f);
	const glm::vec2 texel = glm::vec2(0.0f);

	std::list<VertAtt> vertices;

	for (size_t i = 0; i < grid.numCells(); i++)
	{
		grid.getCube(i, cube);
		getCubeIndex(cubeindex, cube, isolevel);

		if (cubeindex != 0)
		{
			grid.getGradients(cube);
			nfloats = polygonise(cube, cubeindex, isolevel, buffer);
			for (int j = 0; j < nfloats / 6; j++)
			{
				VertAtt va;
				va.vertex.x = buffer[j * 6 + 0];
				va.vertex.y = buffer[j * 6 + 1];
				va.vertex.z = buffer[j * 6 + 2];

				va.vertex -= gmid;

				va.normal.x = buffer[j * 6 + 3];
				va.normal.y = buffer[j * 6 + 4];
				va.normal.z = buffer[j * 6 + 5];

				va.material = material;
				va.texel = texel;
				vertices.push_back(va);
			}
		}
	}

	VertAtt* data = new VertAtt[vertices.size()];
	std::copy(vertices.begin(), vertices.end(), data);

	return std::make_shared<Model>(program, sizeof(VertAtt) * vertices.size(), data, "textures\\sphere.jpg");
}
