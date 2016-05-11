#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "AbstractRule.h"

#define diagramData std::vector<std::pair<double, double>>
#define RANGE_MULT 1.2 //increase diagram range
#define POINT_NUM 100 //point in diagram

class rulesEngine
{
private:
	diagramData _testData;
	std::unordered_map<std::string, std::unordered_map<std::string, abstractRule*>> _availibleRules;
	std::unordered_map<int, abstractRule*> _usedRules;
	abstractRule *_result = NULL;
	int _ruleID = 0;
	double _range = -1; //-1 means that test data is not loaded

public:
	~rulesEngine();

	///////_FOR VIEW CONTROLER_////////
	//return map <ruleGroupName, ruleName>
	std::unordered_map<std::string, std::vector<std::string>> get_rules_map() const;

	//if ok -> return true and fill params, else return false
	bool get_rule_param(std::vector<std::string> &params, const std::string &ruleName) const;

	//if ok -> return diagram range and fill data, else return 0
	double load_start_data(diagramData &data, const std::string &fileName);

	//if ok -> return diagram range, else return 0
	double set_data(int N, double dT, const diagramData &data);

	//if ok -> return ruleID and fill data & sd & rsd & wsd, else return 0
    int create_new_rule(diagramData& data , double &sd, double &rsd, double &wsd,
		const std::string &ruleGroup, const std::string &ruleName, const std::vector<double> ruleParam);

	//return true if valid id
	bool remove_rule(int id);

	//return true if valid id, if id==0 then set _result=NULL and return true
	bool set_result_rule(int id);

	///////_FOR APPLICATION_////////
	//create copy of rule and save it, so you should free mem
	void add_rule(const abstractRule* r);

	//return copy of resul rule, so you should free mem
	abstractRule* get_result() const;

	bool is_empty();
};