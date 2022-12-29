//
// Created by Lenovo on 28/12/2022.
//

#ifndef FLIGHTS_COORDINATES_H
#define FLIGHTS_COORDINATES_H

#include <utility>
#include <vector>
#include "haversine.h"

using namespace std;

pair<double, double> findClosest(const vector<pair<double, double>> &coords, const pair<double, double> &p);


#endif //FLIGHTS_COORDINATES_H
