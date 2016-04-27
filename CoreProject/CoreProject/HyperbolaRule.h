#pragma once
#include <minmax.h>
#include "AbstractRule.h"

class hyperbolaRule : abstractRule
{
	//y = a / (x+a), [0, +inf]
private:
	double _a;
	bool _isValid = false;
	double _min = 0, _max = MAXLONGLONG;

public:
	abstractRule* copy() const;

	std::string get_name() const;

	std::string get_group_name() const;

	std::vector<std::string> get_param_list() const;

	bool set_param(std::vector<double> params);

	bool isValid() const;

	bool count(double &y, double x) const;
};