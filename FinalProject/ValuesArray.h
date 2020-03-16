#ifndef VALUESARRAY_H
#define VALUESARRAY_H

template<typename T>
class ValuesArray
{
private:
	T* _values;

	size_t _count;

public:
	ValuesArray() :
		_values(NULL),
		_count(0)
	{
	}

	void connect(const T* values, size_t count)
	{
		_values = (T*) values;
		_count = count;
	}

	T* getValues() { return _values; }

	size_t getCount() { return _count; }
};
#endif