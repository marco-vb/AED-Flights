#ifndef AED2223_P12_COORD2DTREE_H
#define AED2223_P12_COORD2DTREE_H

#include <utility>
#include <list>
#include "Rect.h"
#include "haversine.h"
#include "coordinates.h"
using namespace std;

struct Node {
    pair<double, double> data;
    Node *left;
    Node *right;
};

class Coord2dTree {
private:
    vector<pair<double, double>> all;
    Node* root;
    Node* insert(pair<double, double> x, Node* t, int cd);
    void nearest(pair<double, double> Q, Node* t, int cd, Rect BB, pair<double, double> &best, double &best_dist);
    void in_radius(pair<double, double> Q, Node* t, int cd, Rect BB, vector<pair<double, double>> &best, double radius);

        public:
    Coord2dTree();
    bool insert(double lat, double lon);
    bool insert(pair<double, double> p);
    pair<double, double> nearest(double lat, double lon);
    pair<double, double> nearest(pair<double, double> p);
    vector<pair<double, double>> in_radius(double lat, double lon, double radius);
    vector<pair<double, double>> in_radius(pair<double, double> p, double radius);
};


#endif //AED2223_P12_COORD2DTREE_H
