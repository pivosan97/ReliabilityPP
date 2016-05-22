#include "stdafx.h"
#include <math.h>
#include "ExponentialRule.h"

using namespace std;

abstractRule* exponentialRule::copy() const
{
	abstractRule *copy = new  exponentialRule;
	copy->set_param({ _a });
	return copy;
}

std::string exponentialRule::get_name() const
{
	return "Exponential";
}

string exponentialRule::get_group_name() const
{
	return ONE_PARAM_RULE;
}

std::vector<std::string> exponentialRule::get_param_list() const
{
	return{ "a" };
}

bool exponentialRule::set_param(std::vector<double> params)
{
	if (params.size() != 1)
	{
		_isValid = false;
		return false;
	}

	_a = params[0];

	if (_a < 0)
	{
		_isValid = false;
		return false;
	}

	_isValid = true;
	return true;
}

bool exponentialRule::isValid() const
{
	return _isValid;
}

bool exponentialRule::count(double &y, double x) const
{
	if (_isValid == false)
	{
		return false;
	}

	if (x < _min || x > _max)
	{
		return false;
	}

	y = exp((-1) * _a * x);
	return true;
}