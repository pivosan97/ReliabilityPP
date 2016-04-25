#include "stdafx.h"
#include "HyperbolaRule.h"

using namespace std;

abstractRule* hyperbolaRule::copy() const
{
	abstractRule *copy = new  hyperbolaRule;
	copy->set_param({ _a });
	return copy;
}

std::string hyperbolaRule::get_name() const
{
	return "Hyperbola";
}

string hyperbolaRule::get_group_name() const
{
	return ONE_PARAM_RULE;
}

std::vector<std::string> hyperbolaRule::get_param_list() const
{
	return{ "a" };
}

bool hyperbolaRule::set_param(std::vector<double> params)
{
	if (params.size() != 1)
	{
		isValid = false;
		return false;
	}

	_a = params[0];
	isValid = true;
	return true;
}

bool hyperbolaRule::count(double &y, double x) const
{
	if (isValid == false)
	{
		return false;
	}

	y = _a / x;
	return true;
}