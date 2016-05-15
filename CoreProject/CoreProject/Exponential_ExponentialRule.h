#pragma once
#include <limits.h>
#include "AbstractRule.h"

class exponential_exponentialRule : public abstractRule
{
	//y = c * exp(-a1 * t) + (1 - c) * exp(-a2 * t), [0, +inf] (a >= 0, 0 <= c <= 1)
private:
	double _a1, _a2, _c;
	bool _isValid = false;
	double _min = 0, _max = LLONG_MAX;

public:
	abstractRule* copy() const;

	std::string get_name() const;

	std::string get_group_name() const;

	std::vector<std::string> get_param_list() const;

	bool set_param(std::vector<double> params);

	bool isValid() const;

	bool count(double &y, double x) const;
};