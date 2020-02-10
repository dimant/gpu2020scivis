#include "DataBuilder.h"

#include "VertAtt.h"

std::shared_ptr<Model> DataBuilder::createData(GLuint program, UniformGrid & grid)
{
	auto scienceFunction = [](float x, float y) {
		float d = 0.8;
		float x1 = x + d;
		float x2 = x - d;
		float y1 = y + d;
		float y2 = y - d;
		return exp(-(x1 * x1 + y1 * y1)) + exp(-(x2 * x2 + y2 * y2));
	};
	//auto scienceFunction = [](float x, float y) { return sin(1 / (x * x + y * y)); };

	// fractional brownian motion
	//auto scienceFunction = [](float x, float y) {
	//	float amplitude = 1.;
	//	float frequency = 1.;
	//	float z = sin(x * frequency);
	//	float t = 0.01*(-y * 130.0);
	//	z += sin(x*frequency*2.1 + t)*4.5;
	//	z += sin(x*frequency*1.72 + t * 1.121)*4.0;
	//	z += sin(x*frequency*2.221 + t * 0.437)*5.0;
	//	z += sin(x*frequency*3.1122 + t * 4.269)*2.5;
	//	z *= amplitude * 0.06;
	//	return z;
	//};

	// assuming that v.z = f(x, y)
	auto normalFunction = [](glm::vec3 v) {
		return glm::vec3(
			-2 * v.x * v.z,
			-2 * v.y * v.z,
			1.0f);
	};

	//auto normalFunction = [](glm::vec3 v) {
	//	return glm::vec3(0.0f, 1.0f, 0.0f);
	//};

	grid.sample(scienceFunction);

	size_t nVert = grid.numVertices();

	// three coordinates per vertex
	size_t sizeTris = nVert * 3;
	float* tris = new float[sizeTris];
	float* triCursor = tris;

	// triangulate sampled grid
	grid.getTris(tris);

	// populate data representation
	VertAtt* data = new VertAtt[nVert];

	auto material = glm::vec3(0.1f, 12.0f, 2.0f);

	float d1 = grid.getRange1().y - grid.getRange1().x;
	float m1 = grid.getRange1().x;
	float d2 = grid.getRange2().y - grid.getRange2().x;
	float m2 = grid.getRange2().x;

	for (int i = 0; i < nVert; i++)
	{
		data[i].vertex = *((glm::vec3*) triCursor);
		triCursor += 3;

		data[i].texel = glm::vec2(
			(data[i].vertex.x + m1) / d1,
			(data[i].vertex.y + m2) / d2
		);
		data[i].normal = normalFunction(data[i].vertex);
		data[i].material = material;
	}

	return std::make_shared<Model>(program, sizeof(VertAtt) * nVert, data, "textures\\sphere.jpg");
}
