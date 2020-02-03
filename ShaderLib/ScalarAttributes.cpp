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
