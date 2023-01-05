#include "Coord2dTree.h"

Coord2dTree::Coord2dTree() {
    root = nullptr;
}

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
        if(x.second < t -> data.second)
            t -> left = insert(x, t->left, 0);
        else
            t -> right = insert(x, t->right, 0);
    }
    return t;
}
bool Coord2dTree::insert(double lat, double lon) {
    pair<double, double> p = make_pair(lat, lon);
    try {
        root = insert(p, root, 0);
        return true;
    } catch (const char*){
        return false;
    }
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
pair<double, double> Coord2dTree::nearest(pair<double, double> p) {
    pair<double, double> best = make_pair(-1, -1);
    double best_dist = 1000000000;
    Rect BB = Rect(-90, 90, -180, 180);
    nearest(p, root, 0, BB, best, best_dist);
    if(haversine(p, best) > haversine(p.first, p.second, p.first, 180)) {
        nearest(make_pair(p.first, (p.second < 0 ? 360 + p.second : -360 + p.second)), root, 0, BB, best, best_dist);
    }
    return best;
}
void Coord2dTree::in_radius(pair<double, double> Q, Node* t, int cd, Rect BB, vector<pair<double, double>> &best, double radius){
    if((t == nullptr) || (distance(Q, BB) > 1.1*radius && radius <= 1500))
        return;

    double dist = haversine(Q, t -> data);
    if(dist < radius) {
        best.push_back(t -> data);
    }

    double curr; double curr_data;
    if(cd == 0){ curr_data = t -> data.first; }
    else { curr_data = t -> data.second; }
    int next_cd = (cd + 1) % 2;

    in_radius(Q, t -> left, next_cd, BB.trimLeft(cd, curr_data), best, radius);
    in_radius(Q, t -> right, next_cd, BB.trimRight(cd, curr_data), best, radius);
}
vector<pair<double, double>> Coord2dTree::in_radius(pair<double, double> p, double radius) {
    vector<pair<double, double>> best;
    Rect BB = Rect(-90, 90, -180, 180);
    in_radius(p, root, 0, BB, best, radius);
    if(radius > haversine(p.first, p.second, p.first, 180)) {
        in_radius(make_pair(p.first, (p.second < 0 ? 360 + p.second : -360 + p.second)), root, 0, BB, best, radius);
    }
    return best;
}