#ifndef FLIGHTS_HAVERSINE_H
#define FLIGHTS_HAVERSINE_H

#include <cmath>
using namespace std;
double haversine(double lat1, double lon1, double lat2, double lon2);
double haversine(pair<double, double> p1, pair<double, double> p2);

#endif //FLIGHTS_HAVERSINE_H
