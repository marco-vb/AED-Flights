#include "Coord2dTree.h"

Coord2dTree::Coord2dTree() {
    root = nullptr;
}

Node* Coord2dTree::insert(pair<double, double> x, Node* t, int cd){
    if(t == nullptr) {
        t = new Node{x, nullptr, nullptr};
        all.push_back(x);
    }
    else if (x == t -> data)
        throw "Error! Duplicate point!";

    else if(cd == 0){
        if(x.first < t -> data.first)
            t -> left = insert(x, t->left, 1);
        else
            t -> right = insert(x, t->right, 1);
    }

    else{
        if(x.second < t -> data.second)
            t -> left = insert(x, t->left, 0);
        else
            t -> right = insert(x, t->right, 0);
    }
    return t;
}

bool Coord2dTree::insert(double lat, double lon) {
    pair<double, double> p = make_pair(lat, lon);
    root = insert(p, root, 0);
}
bool Coord2dTree::insert(pair<double, double> p){
    root = insert(p, root, 0);
}


void Coord2dTree::nearest(pair<double, double> Q, Node* t, int cd, Rect BB, pair<double, double> &best, double &best_dist){
    if(t == nullptr || distance(Q, BB) > best_dist) return;

    double dist = haversine(Q, t -> data);
    if(dist < best_dist) {
        best = t -> data;
        best_dist = dist;
    }

    double curr; double curr_data;
    if(cd == 0){ curr = Q.first; curr_data = t -> data.first; }
    else { curr = Q.second; curr_data = t -> data.second; }
    int next_cd = (cd + 1) % 2;

    if(curr < curr_data){
        nearest(Q, t -> left, next_cd, BB.trimLeft(cd, curr_data), best, best_dist);
        nearest(Q, t -> right, next_cd, BB.trimRight(cd, curr_data), best, best_dist);
    }
    else {
        nearest(Q, t -> right, next_cd, BB.trimRight(cd, curr_data), best, best_dist);
        nearest(Q, t -> left, next_cd, BB.trimLeft(cd,curr_data), best, best_dist);
    }
}

pair<double, double> Coord2dTree::nearest(double lat, double lon) {
    pair<double, double> Q = make_pair(lat, lon);
    pair<double, double> best = make_pair(0, 0);
    double best_dist = 1000000000;
    Rect BB = Rect(-90, 90, -180, 180);
    nearest(Q, root, 0, BB, best, best_dist);
    if(haversine(Q, best) > haversine(Q.first, Q.second, Q.first, 180)) {
        best = findClosest(all, Q);
    }
    return best;
}

pair<double, double> Coord2dTree::nearest(pair<double, double> p) {
    pair<double, double> best = make_pair(0, 0);
    double best_dist = 1000000000;
    Rect BB = Rect(-90, 90, -180, 180);
    nearest(p, root, 0, BB, best, best_dist);
    return best;
}

 /*
Node* Coord2dTree::insert(pair<double, double> x, Node* t, int cd){
    if(t == nullptr) {
        t = new Node{x, nullptr, nullptr};
    }
    else if (x == t -> data)
        throw "Error! Duplicate point!";

    else if(cd == 0){
        if(x.first < t -> data.first)
            t -> left = insert(x, t->left, 1);
        else
            t -> right = insert(x, t->right, 1);
    }

    else{
        if(x.second >= 0 && x.second < t -> data.second && x.second > t -> data.second - 180 ||
           x.second < 0 && x.second > t -> data.second && x.second < t -> data.second + 180)
            t -> left = insert(x, t->left, 0);
        else
            t -> right = insert(x, t->right, 0);
    }
    return t;
}

bool Coord2dTree::insert(double lat, double lon) {
    pair<double, double> p = make_pair(lat, lon);
    root = insert(p, root, 0);
}
bool Coord2dTree::insert(pair<double, double> p){
    root = insert(p, root, 0);
}

void Coord2dTree::nearest(pair<double, double> Q, Node* t, int cd, Rect BB, pair<double, double> &best, double &best_dist){
    if(t == nullptr || distance(Q, BB) > best_dist) return;
    double dist = haversine(Q, t -> data);

    if(dist < best_dist) {
        best = t -> data;
        best_dist = dist;
    }

    if(cd == 0){
        double lat = t -> data.first;
        if(Q.first < lat) {
            nearest(Q, t->left, 1, BB.trimLeft(0, lat), best, best_dist);
            nearest(Q, t->right, 1, BB.trimRight(0, lat), best, best_dist);
        }
        else {
            nearest(Q, t->right, 1, BB.trimRight(0, lat), best, best_dist);
            nearest(Q, t->left, 1, BB.trimLeft(0, lat), best, best_dist);
        }
    }

    else{
        double lon = t -> data.second;
        if(Q.second >= 0 && Q.second < lon && Q.second > lon - 180 ||
           Q.second < 0 && Q.second > lon && Q.second < lon + 180) {
            nearest(Q, t->left, 0, BB.trimLeft(1, lon), best, best_dist);
            nearest(Q, t->right, 0, BB.trimRight(1, lon), best, best_dist);
        }
        else {
            nearest(Q, t->right, 0, BB.trimRight(1, lon), best, best_dist);
            nearest(Q, t->left, 0, BB.trimLeft(1, lon), best, best_dist);
        }
    }
} */