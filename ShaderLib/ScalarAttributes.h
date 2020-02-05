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
	
	void	 setC0Scalar(int i, float v);
	
	float getC0Scalar(int i);

	float getMin();
	
	float getMax();
};

#endif
