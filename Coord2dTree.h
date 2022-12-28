#ifndef AED2223_P12_COORD2DTREE_H
#define AED2223_P12_COORD2DTREE_H

#include <utility>
#include "Rect.h"
#include "haversine.h"
using namespace std;

struct Node {
    pair<double, double> data;
    Node *left;
    Node *right;
};

class Coord2dTree {
private:
    Node* root;
    Node* insert(pair<double, double> x, Node* t, int cd);
    void nearest(pair<double, double> Q, Node* t, int cd, Rect BB, pair<double, double> &best, double &best_dist);

public:
    Coord2dTree();
    bool insert(double lat, double lon);
    bool insert(pair<double, double> p);
    pair<double, double> find_min();
    void remove(double lat, double lon);
    void remove(pair<double, double> p);
    bool contains(double lat, double lon);
    bool contains(pair<double, double> p);
    pair<double, double> nearest(double lat, double lon);
    pair<double, double> nearest(pair<double, double> p);
};


#endif //AED2223_P12_COORD2DTREE_H
