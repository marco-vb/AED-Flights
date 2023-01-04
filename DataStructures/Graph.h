#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "../HelperClasses/Airport.h"

using namespace std;
typedef list<int> li;
typedef vector<int> vi;
typedef pair<int, int> pii;

class Graph {
public:
    struct Edge {
        int dest;
        int weight;
        set<string> airlines;
    };
    struct Node {
        list<Edge> adj;
        bool visited;
        int distance;
    };

    int n;
    vector<Node> nodes;

    Graph();
    explicit Graph(int nodes);
    void addEdge(int src, int dest, string airline, int weight = 1);

    int getOutDegree(int i);
    int getAirlinesNumber(int i);
    int getDestinationsNumber(int i);
    int getDestinationsCountries(int i, unordered_map<int, Airport> &airports);
    int getNumEdges();
    int getCompanies();
    int getDiameter();
    set<int> getDestinations(int src, int r);
    vector<Node> getNodes() const;
    vector<pii> getTopAirports(int i);
    set<int> getArticulationPoints();
    set<int> getArticulationPoints(set<string> &airlines_to_consider);

    list<li> least_flights(vector<int> sources, vector<int> destination);
    list<li> least_flights(const vector<int>& sources, const vector<int>& dest, const set<string> &airlines_to_consider);
    list<li> least_flights_with_distance(const vector<int>& src, const vector<int>& dest, const set<string>& airlines_to_consider);
    list<li> least_flights_with_distance(const vector<int>& src, const vector<int>& dest);

    void articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, bool first = false);
    set<int> articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, set<string> &airlines_to_consider, bool first = false);
};

#endif
