#pragma once
#include "AbstractRule.h"

class lineRule : abstractRule
{
	//y = a * x + b
private:
	double _a, _b;
	bool _isValid = false;

public:
	abstractRule* copy() const;

	std::string get_name() const;

	std::string get_group_name() const;

	std::vector<std::string> get_param_list() const;

	bool set_param(std::vector<double> params);

	bool isValid() const;

	bool count(double &y, double x) const;
};