#include "stdafx.h"
#include "line_rule.h"

using namespace std;

abstractRule* lineRule::copy() const
{
	abstractRule *copy = new lineRule;
	copy->set_param({ _a, _b });
	return copy;
}

std::string lineRule::get_name()
{
	return "Line";
}

string lineRule::get_group_name()
{
	return TWO_PARAM_RULE;
}

std::vector<std::string> lineRule::get_param_list()
{
	return { "a", "b" };
}

bool lineRule::set_param(std::vector<double> params)
{
	if (params.size() != 2)
	{
		isValid = false;
		return false;
	}

	_a = params[0];
	_b = params[1];
	isValid = true;
	return true;
}

bool lineRule::count(double &y, double x)
{
	if (isValid == false)
	{
		return false;
	}

	y = _a * x + _b;
	return true;
}