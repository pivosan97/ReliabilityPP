#pragma once
#include <vector>
#include "abstractRule.h"

#define diagramData std::vector<std::pair<double, double>>

//transfor input data to diagram data for P(t)
diagramData count_P(const std::vector<int> &data, double dT);

//return -1 if failed, else return deviation
double count_mean_square_deviation(const diagramData &data, const abstractRule *rule);

double count_mean_relative_suare_deviation(const diagramData &data, const abstractRule *rule);

double count_mean_weighted_suare_deviation(const diagramData &data, const abstractRule *rule);
