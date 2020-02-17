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
	
	void setC0Scalar(size_t i, float v);
	
	const float getC0Scalar(const size_t i)const;

	const float getMin();
	
	const float getMax();
};

#endif
