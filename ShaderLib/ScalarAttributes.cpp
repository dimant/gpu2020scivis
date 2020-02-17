#include <algorithm>

#include "ScalarAttributes.h"

const float ScalarAttributes::getMin()
{
	return *std::min_element(_values.begin(), _values.end());
}

const float ScalarAttributes::getMax()
{
	return *std::max_element(_values.begin(), _values.end());
}

void ScalarAttributes::setC0Scalar(const size_t i, const float v)
{
	_values[i] = v;
}

const float ScalarAttributes::getC0Scalar(const size_t i) const
{
	return _values[i];
}