#include "stdafx.h"
#include "LineRule.h"

using namespace std;

abstractRule* lineRule::copy() const
{
	abstractRule *copy = new lineRule;
	copy->set_param({ _a, _b });
	return copy;
}

std::string lineRule::get_name() const
{
	return "Line";
}

string lineRule::get_group_name() const
{
	return TWO_PARAM_RULE;
}

std::vector<std::string> lineRule::get_param_list() const
{
	return { "a", "b" };
}

bool lineRule::set_param(std::vector<double> params)
{
	if (params.size() != 2)
	{
		_isValid = false;
		return false;
	}

	_a = params[0];
	_b = params[1];
	_isValid = true;
	return true;
}

bool lineRule::isValid() const
{
	return _isValid;
}

bool lineRule::count(double &y, double x) const
{
	if (_isValid == false)
	{
		return false;
	}

	y = _a * x + _b;
	return true;
}