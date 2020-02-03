#ifndef SCALARATTRIBUTES_H
#define SCALARATTRIBUTES_H

#include <vector>

class ScalarAttributes
{
private:
	std::vector<float> _values;

public:
	ScalarAttributes(size_t size) : _values(size)
	{}
	
	void	 setC0Scalar(int i,float v)
	{ _values[i] = v; }
	
	float getC0Scalar(int i)
	{ return _values[i]; }

	float getMin();
	
	float getMax();
};

#endif
