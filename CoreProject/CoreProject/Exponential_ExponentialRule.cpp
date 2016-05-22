#include "stdafx.h"
#include <math.h>
#include "Exponential_ExponentialRule.h"

using namespace std;

abstractRule* exponential_exponentialRule::copy() const
{
	abstractRule *copy = new  exponential_exponentialRule;
	copy->set_param({ _a1, _a2, _c });
	return copy;
}

std::string exponential_exponentialRule::get_name() const
{
	return "Exponential_Exponential";
}

string exponential_exponentialRule::get_group_name() const
{
	return SUM_RULE;
}

std::vector<std::string> exponential_exponentialRule::get_param_list() const
{
	return{ "a1", "a2", "c" };
}

bool exponential_exponentialRule::set_param(std::vector<double> params)
{
	if (params.size() != 3)
	{
		_isValid = false;
		return false;
	}

	_a1 = params[0];
	_a2 = params[1];
	_c = params[2];

	if (_a1 < 0 || _a2 < 0 || _c > 1 || _c < 0)
	{
		_isValid = false;
		return false;
	}

	_isValid = true;
	return true;
}

bool exponential_exponentialRule::isValid() const
{
	return _isValid;
}

bool exponential_exponentialRule::count(double &y, double x) const
{
	if (_isValid == false)
	{
		return false;
	}

	if (x < _min || x > _max)
	{
		return false;
	}

	y = _c * exp((-1) * _a1 * x) + (1 - _c) * exp((-1) * _a2 * x);
	return true;
}