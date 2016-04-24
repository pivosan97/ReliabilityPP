#pragma once
#include "abstract_rule.h"

class lineRule : abstractRule
{
	//y = a * x + b
private:
	double _a, _b;
	bool isValid = false;

public:
	abstractRule* copy() const;

	std::string get_name();

	std::string get_group_name();

	std::vector<std::string> get_param_list();

	bool set_param(std::vector<double> params);

	bool count(double &y, double x);
};