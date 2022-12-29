
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

vector<pair<double, double>> findInRadius(const vector<pair<double, double>> &coords, const pair<double, double> &p, double radius){
    double lat = p.first;
    double lon = p.second;
    vector<pair<double, double>> best;
    for(pair<double, double> coord : coords) {
        if(haversine(lat, lon, coord.first, coord.second) < radius) {
            best.push_back(coord);
        }
    }
    return best;
}

vector<pair<double, double>> findClosest(const vector<pair<double, double>> &coords, const pair<double, double> &p, int n){
    double lat = p.first;
    double lon = p.second;
    vector<pair<double, double>> best;
    for(pair<double, double> coord : coords) {
        if(best.size() < n) {
            best.push_back(coord);
        }
        else {
            int index = 0;
            double max_dist = 0;
            for(int i = 0; i < best.size(); i++) {
                if(haversine(lat, lon, best[i].first, best[i].second) > max_dist) {
                    max_dist = haversine(lat, lon, best[i].first, best[i].second);
                    index = i;
                }
            }
            if(haversine(lat, lon, coord.first, coord.second) < max_dist) {
                best[index] = coord;
            }
        }
    }
    return best;
}


