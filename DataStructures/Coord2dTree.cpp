#include "Coord2dTree.h"

Coord2dTree::Coord2dTree() {
    root = nullptr;
    size = 0;
}

Node* Coord2dTree::insert(pair<double, double> x, Node* t, int cd){
    if(t == nullptr) {
        t = new Node{x, nullptr, nullptr};
        size++;
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

void Coord2dTree::nearestN(pair<double, double> Q, Node* t, int cd, Rect BB, priority_queue<pair<double, pair<double, double>>>& bestN, int n){
    if(t == nullptr || (bestN.size() >= n && distance(Q, BB) > 1.1*bestN.top().first && bestN.top().first <= 4000)) return;

    double dist = haversine(Q, t -> data);
    if(bestN.size() < n)
        bestN.push(make_pair(dist, t -> data));
    else if(dist < bestN.top().first){
        bestN.push(make_pair(dist, t -> data));
        bestN.pop();
    }

    double curr; double curr_data;
    if(cd == 0){ curr = Q.first; curr_data = t -> data.first; }
    else { curr = Q.second; curr_data = t -> data.second; }
    int next_cd = (cd + 1) % 2;

    if(curr < curr_data){
        nearestN(Q, t -> left, next_cd, BB.trimLeft(cd, curr_data), bestN, n);
        nearestN(Q, t -> right, next_cd, BB.trimRight(cd, curr_data), bestN, n);
    }
    else {
        nearestN(Q, t -> right, next_cd, BB.trimRight(cd, curr_data), bestN, n);
        nearestN(Q, t -> left, next_cd, BB.trimLeft(cd,curr_data), bestN, n);
    }
}

vector<pair<double, double>> Coord2dTree::nearestN(pair<double, double> Q, int n) {
    if(n == 0) return {};
    if(n > size){
        cout << "Demasiados elementos pedidos" << endl;
        return {};
    }
    double lat = Q.first;
    double lon = Q.second;
    priority_queue<pair<double, pair<double, double>>> bestN;
    Rect BB = Rect(-90, 90, -180, 180);

    nearestN(Q, root, 0, BB, bestN, n);

    vector<pair<double, double>> best;

    if(!bestN.empty() && bestN.top().first > haversine(Q.first, Q.second, Q.first, 180)) {
        priority_queue<pair<double, pair<double, double>>> bestN2;
        nearestN(make_pair(lat, (lon < 0 ? 360 + lon : -360 + lon)), root, 0, BB, bestN2, n);
        set<pair<double, pair<double, double>>> s;
        while(!bestN.empty()){
            s.insert({((double) round(100*bestN.top().first)) / 100, bestN.top().second});
            bestN.pop();
        }
        while(!bestN2.empty()){
            s.insert({((double) round(100*bestN2.top().first)) / 100, bestN2.top().second});
            bestN2.pop();
        }
        int i = 0;
        for(auto it = s.begin(); it != s.end(); it++){
            if(i >= n) break;
            best.push_back(it -> second);
            i++;
        }

    } else while(!bestN.empty()){
        best.push_back(bestN.top().second);
        bestN.pop();
    }
    return best;
}
