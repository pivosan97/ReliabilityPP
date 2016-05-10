#pragma once
#include <vector>
#include "abstractRule.h"

#define diagramData std::vector<std::pair<double, double>>

diagramData count_P(const std::vector<int> &data, double dT);

double count_mean_square_deviation(const diagramData &data, const abstractRule *rule);

double count_mean_relative_suare_deviation(const diagramData &data, const abstractRule *rule);

double count_mean_weighted_suare_deviation(const diagramData &data, const abstractRule *rule);
