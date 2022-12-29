
#include "coordinates.h"

pair<double, double> findClosest(const vector<pair<double, double>> &coords, const pair<double, double> &p){
    double lat = p.first;
    double lon = p.second;
    pair<double, double> best = make_pair(0, 0);
    double best_dist = 1000000000;
    for(pair<double, double> coord : coords) {
        if(haversine(lat, lon, coord.first, coord.second) < best_dist) {
            best = coord;
            best_dist = haversine(lat, lon, coord.first, coord.second);
        }
    }
    return best;
}


