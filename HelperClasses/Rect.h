#ifndef FLIGHTS_RECT_H
#define FLIGHTS_RECT_H

#include <utility>
#include <queue>
#include <functional>
#include "Haversine.h"
using namespace std;

class Rect {
public:
    double lat1;
    double lat2;
    double lon1;
    double lon2;

    Rect(double lat1, double lat2, double lon1, double lon2);
    Rect trimLeft(int cd, double data) const;
    Rect trimRight(int cd, double data) const;
};

double distance(pair<double, double> Q, Rect BB);

#endif //FLIGHTS_RECT_H
