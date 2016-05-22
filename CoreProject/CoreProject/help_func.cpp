#pragma once
#include "stdafx.h"
#include "help_func.h"

using namespace std;

diagramData count_P(const vector<int> &data, double dT)
{
	diagramData out;

	int N = 0;
	for (int i = 0; i < data.size(); i++)
	{
		N += data[i];
	}

	out.push_back(make_pair(0, 1));
	double temp = 0;
	for (int i = 0; i < data.size(); i++)
	{
		temp += data[i];
		out.push_back(make_pair((i + 1) * dT, 1 - temp / N));
	}

	return out;
}

double count_mean_square_deviation(const diagramData &data, const abstractRule *rule)
{
	int K = data.size();

	if (K == 0)
	{
		return -1;
	}

	double sum = 0;
	for (int i = 0; i < K; i++)
	{
		double y;
		if (rule->count(y, data[i].first))
		{
			sum += (data[i].second - y) * (data[i].second - y);
		}
		else
		{
			return -1;
		}
	}

	return sum / K;
}

double count_mean_relative_suare_deviation(const diagramData &data, const abstractRule *rule)
{
	int K = data.size();

	if (K == 0)
	{
		return -1;
	}

	double sum = 0;
	for (int i = 0; i < K-1; i++)
	{
		double y;
		if (rule->count(y, data[i].first))
		{
			if (data[i].second != 0)
			{
				sum += ((data[i].second - y) / data[i].second) * ((data[i].second - y) / data[i].second);
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}

	return sum / (K-1);
}

double count_mean_weighted_suare_deviation(const diagramData &data, const abstractRule *rule)
{
	int K = data.size();

	if (K == 0)
	{
		return -1;
	}

	double sum = 0;
	for (int i = 0; i < K-1; i++)
	{
		double y;
		if (rule->count(y, data[i].first))
		{
			if (data[i].second != 0)
			{
				sum += (data[i].second - y) * (data[i].second - y) / data[i].second;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}

	return sum / (K-1);
}