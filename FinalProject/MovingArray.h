#ifndef MOVINGARRAY_H
#define MOVINGARRAY_H

#include "GL/glew.h"

class MovingArray
{
private:
	float* _data;

	size_t _size;

	float _average;

public:
	MovingArray(size_t size) :
		_average(0.0f)
	{
		_size = size;
		_data = new float[size];

		for (int i = 0; i < size; i++)
		{
			_data[i] = 0.0f;
		}
	}

	~MovingArray()
	{
		delete _data;
	}

	size_t getCount() { return _size; }

	void add(float value)
	{
		_average -= _data[0] / _size;
		_average += value / _size;

		for (int i = 0; i < _size - 1; i++)
		{
			_data[i] = _data[i + 1];
		}

		_data[_size - 1] = value;
	}

	const float* getValues() const { return _data; }

	float getAverage() const { return _average; }
};

#endif
