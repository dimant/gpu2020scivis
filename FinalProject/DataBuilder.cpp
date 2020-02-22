#include "DataBuilder.h"
#include <omp.h>
#include <list>

#include "polygonise.h"

#include "VertAtt.h"

#include "ddsbase.h"

#include "triangulation.h"

void DataBuilder::loadPVM(const char* filename)
{
	unsigned char *data;
	unsigned int width, height, depth;
	unsigned int components;
	float scalex, scaley, scalez;
	unsigned char* description;
	unsigned char* courtesy;
	unsigned char* paramter;
	unsigned char* comment;

	data = readPVMvolume(filename,
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

	glm::vec3 gdelta = (gmax - gmin) / glm::vec3(width, height, depth);

	_grid = new UniformGrid3(width, height, depth, gmin, gmax);

	auto loader = [data](size_t i) { return (float)data[i]; };

	_grid->sample(loader);

	_gmid = (_grid->getMax() + _grid->getMin()) / 2.0f;
}

std::shared_ptr<Model> DataBuilder::createData(GLuint program, float isolevel)
{
	if (_grid == 0)
	{
		return 0;
	}


	const int maxThreads = 16;
	std::vector<VertAtt> vertices[maxThreads];

	for (int i = 0; i < maxThreads; i++)
	{
		vertices[i].reserve(_grid->numCells() / (maxThreads * 2));
	}

	const size_t ncells = _grid->numCells();
	const glm::vec2 texel = glm::vec2(0.0f);
	const glm::vec3 material = glm::vec3(0.1f, 12.0f, 2.0f);

	{

#pragma omp parallel for
		for (int i = 0; i < ncells; i++)
		{
			float buffer[90];
			size_t nfloats;
			Cube cube;
			int cubeindex;
			int tid = omp_get_thread_num();

			_grid->getCube(i, cube);

			/*
			   Determine the index into the edge table which
			   tells us which vertices are inside of the surface
			*/
			getCubeIndex(cubeindex, cube, isolevel);

			if (cubeindex != 0)
			{
				_grid->getGradients(cube);
				nfloats = polygonise(cube, cubeindex, isolevel, buffer);

				for (int j = 0; j < nfloats / 6; j++)
				{
					VertAtt va;
					va.vertex.x = buffer[j * 6 + 0];
					va.vertex.y = buffer[j * 6 + 1];
					va.vertex.z = buffer[j * 6 + 2];

					va.vertex -= _gmid;

					va.normal.x = buffer[j * 6 + 3];
					va.normal.y = buffer[j * 6 + 4];
					va.normal.z = buffer[j * 6 + 5];

					va.material = material;
					va.texel = texel;

					vertices[tid].push_back(va);
				}
			}
		}
	}

	size_t s = 0;

	for (int i = 0; i < maxThreads; i++)
	{
		s += vertices[i].size();
	}

	VertAtt* output = new VertAtt[s];
	VertAtt* cursor = output;

	for (int i = 0; i < maxThreads; i++)
	{
		std::copy(vertices[i].begin(), vertices[i].end(), cursor);
		cursor += vertices[i].size();
	}

	return std::make_shared<Model>(program, sizeof(VertAtt) * s, output, "textures\\sphere.jpg");
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

void DataBuilder::loadFunction()
{
	glm::vec3 gmin(-5.0f);
	glm::vec3 gmax(5.0f);
	glm::vec3 gmid = (gmax + gmin) / 2.0f;
	_grid = new UniformGrid3(70, 70, 70, gmin, gmax);

	// creates a 'sphere' by returning the distance from a given center
	//// which can then be thresholded to the desired size
	//auto scienceFunction = [gmid](float x, float y, float z) {
	//	return glm::length(glm::vec3(x, y, z) - gmid);
	//};

	auto scienceFunction = [this](float x, float y, float z) {
		float f = 3.0f;
		return glm::length(glm::vec3(x, y, z) - _gmid) + 
			sin(x * f) + 
			sin(y * f) +
			sin(z * f);
	};

	//auto normalFunction = [scienceFunction](glm::vec3 p) {
	//	glm::vec3 n;
	//	n.x = scienceFunction(p.x - 0.01, p.y, p.z) - scienceFunction(p.x + 0.01, p.y, p.z);
	//	n.y = scienceFunction(p.x, p.y - 0.01, p.z) - scienceFunction(p.x, p.y + 0.01, p.z);
	//	n.z = scienceFunction(p.x, p.y, p.z - 0.01) - scienceFunction(p.x, p.y, p.z + 0.01);
	//	return glm::normalize(n);
	//};

	_grid->sample(scienceFunction);
}
