#pragma once
#include "AbstractRule.h"

class hyperbolaRule : abstractRule
{
	//y = a * 1/x
private:
	double _a;
	bool isValid = false;

public:
	abstractRule* copy() const;

	std::string get_name() const;

	std::string get_group_name() const;

	std::vector<std::string> get_param_list() const;

	bool set_param(std::vector<double> params);

	bool count(double &y, double x) const;
};