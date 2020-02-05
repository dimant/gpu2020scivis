#include <algorithm>

#include "ScalarAttributes.h"

float ScalarAttributes::getMin()
{
	return *std::min_element(_values.begin(), _values.end());
}

float ScalarAttributes::getMax()
{
	return *std::max_element(_values.begin(), _values.end());
}

void	 ScalarAttributes::setC0Scalar(int i, float v)
{
	_values[i] = v;
}

float ScalarAttributes::getC0Scalar(int i)
{
	return _values[i];
}