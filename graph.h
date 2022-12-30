#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "Airport.h"

using namespace std;
typedef list<int> li;
typedef vector<int> vi;
typedef pair<int, int> pii;

class Graph {
public:
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        set<string> airlines;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        int distance;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

    Graph(); // Default constructor

    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string airline, int weight = 1);

    // Depth-First Search
    void dfs(int v);

    // Breadth-First Search
    void bfs(int v);

    list<li> least_flights(int src, int dest);
    list<li> least_flights(int src, int dest, set<string> &airlines_to_consider);
    list<li> least_flights(vector<int> sources, vector<int> destination);
    list<li> least_flights(vector<int> sources, vector<int> dest, set<string> &airlines_to_consider);

    int getOutDegree(int i);
    int getAirlinesNumber(int i);
    int getDestinationsNumber(int i);

    int getDestinationsCountries(int i, unordered_map<int, Airport> &airports);

    set<int> getDestinations(int src, int r);

    vector<Node> getNodes() const;

    int getNumEdges();

    int getCompanies();

    int getDiameter();

    vector<pii> getTopAirports(int i);

    set<int> getArticulationPoints();

};

#endif
