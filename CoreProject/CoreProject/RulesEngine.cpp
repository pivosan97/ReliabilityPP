#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "help_func.h"
#include "RulesEngine.h"

using namespace std;

unordered_map<string, vector<string>> rulesEngine::get_rules_map() const
{
	unordered_map<string, vector<string>> res;
	
	auto it1 = _availibleRules.begin();
	while (it1 != _availibleRules.end())
	{
		auto it2 = it1->second.begin();
		while (it2 != it1->second.end())
		{
			res[it1->first].push_back(it2->first);
			it2++;
		}
		it1++;
	}

	return res;
}

bool rulesEngine::get_rule_param(vector<string> &params, const string &ruleName) const
{
	auto it1 = _availibleRules.begin();
	while (it1 != _availibleRules.end())
	{
		auto it2 = it1->second.begin();
		while (it2 != it1->second.end())
		{
			if (it2->second->get_name().compare(ruleName) == 0)
			{
				params = it2->second->get_param_list();
				return true;
			}

			it2++;
		}

		it1++;
	}

	return false;
}

double rulesEngine::load_start_data(diagramData &data, const string &fileName)
{
	ifstream in(fileName);
	
	int N;
	double dT;
	in >> N;
	in >> dT;
	
	vector<int> buf;
	int temp;
	for (int i = 0; i < N; i++)
	{
		in >> temp;
		buf.push_back(temp);
	}

	_range = N * dT * RANGE_MULT;
	_testData = count_P(buf, dT);
	data = _testData;
	return _range;
}

double rulesEngine::set_data(int N, double dT, const diagramData &data)
{
	if (data.size() != N)
	{
		return 0;
	}

	_testData = data;
	_range = N * dT * RANGE_MULT;
	return _range;
}

int rulesEngine::create_new_rule(diagramData& data, double &sd, double &rsd, double &wsd,
	 const std::string &ruleName, const std::vector<double> ruleParam)
{
	auto it1 = _availibleRules.begin();
	while (it1 != _availibleRules.end())
	{
		auto it2 = it1->second.begin();
		while (it2 != it1->second.end())
		{
			if (it2->second->get_name().compare(ruleName) == 0)
			{
				abstractRule *copy = it2->second->copy();
				if (copy->set_param(ruleParam) == false)
				{
					delete copy;
					return false;
				}

				data.clear();
				for (int i = 0; i < POINT_NUM; i++)
				{
					double y, x = i * _range / POINT_NUM;

					if (copy->count(y, x))
					{
						data.push_back(make_pair(x, y));
					}
				}

				_ruleID++;
				_usedRules[_ruleID] = copy;

				sd = count_mean_square_deviation(_testData, copy);
				rsd = count_mean_relative_suare_deviation(_testData, copy);
				wsd = count_mean_weighted_suare_deviation(_testData, copy);

				return _ruleID;
			}

			it2++;
		}

		it1++;
	}

	return false;
}

bool rulesEngine::remove_rule(int id)
{
	if (_usedRules.find(id) == _usedRules.end())
	{
		return false;
	}

	delete _usedRules[id];
	_usedRules.erase(id);
	return true;
}

bool rulesEngine::set_result_rule(int id)
{
	if (id == 0)
	{
		_result = NULL;
		return true;
	}

	if (_usedRules.find(id) == _usedRules.end())
	{
		return false;
	}

	_result = _usedRules[id]->copy();
	return true;
}

rulesEngine::~rulesEngine()
{
	//remove result rule
	if (_result != NULL)
	{
		delete _result;
		_result = NULL;
	}

	//remove availible rules
	auto it1 = _availibleRules.begin();
	while (it1 != _availibleRules.end())
	{
		auto it2 = it1->second.begin();
		while (it2 != it1->second.end())
		{
			delete it2->second;
			it2++;
		}
		it1++;
	}

	//remove used rules
	auto it3 = _usedRules.begin();
	while (it3 != _usedRules.end())
	{
		delete it3->second;
		it3++;
	}
}

void rulesEngine::add_rule(const abstractRule* r)
{
	abstractRule *copy = r->copy();
	_availibleRules[copy->get_group_name()][copy->get_name()] = copy;
}

abstractRule* rulesEngine::get_result() const
{
	return _result->copy();
}

bool rulesEngine::is_empty()
{
	return !_testData.size();
}
