#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "abstract_rule.h"

#define diagramData std::vector<std::pair<double, double>>

class rulesEngine
{
private:
	diagramData _testData;
	std::unordered_map<std::string, std::unordered_map<std::string, abstractRule*>> _availibleRules;
	std::unordered_map<int, abstractRule*> _usedRules;
	abstractRule *_result = NULL;
	int _ruleID = 0;
	double _range = -1; //-1 means that test data is not loaded
#define RANGE_MULT 1.2 //increase diagram range
#define POINT_NUM 100 //point in diagram

public:
	~rulesEngine();

	//For view controler
	//return map <ruleGroupName, ruleName>
	std::unordered_map<std::string, std::vector<std::string>> get_rules_map();

	//if ok -> return range and fill data, else return 0
	double load_start_data(diagramData &data, const std::string &fileName); 

	//if ok -> return ruleID and fill data, else return 0
    int create_new_rule(diagramData& data ,const std::string &ruleGroup, const std::string &ruleName, const std::vector<double> ruleParam);

	bool remove_rule(int id);

	//For application
	//create copy of rule and save it, so you should free mem
	void add_rule(const abstractRule* r);

	//return copy of resul rule, so you should free mem
	abstractRule* get_result();
};