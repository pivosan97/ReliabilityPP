#pragma once
#include <string>
#include <vector>

#define ONE_PARAM_RULE "One parameter"
#define TWO_PARAM_RULE "Two parametrs"
#define SUM_RULE "Weighted total"

class abstractRule
{
private:

public:
	//create a copy of rule
	virtual abstractRule* copy() const = 0;

	virtual std::string get_name() const = 0;

	virtual std::string get_group_name() const = 0;

	virtual std::vector<std::string> get_param_list() const = 0;
	
	//return true if param valid
	virtual bool set_param(std::vector<double> params) = 0;

	//return true if rule have valid parameters
	virtual bool isValid() const = 0;

	//return true and fill y if param valid
	virtual bool count(double &y, double x) const = 0;
};