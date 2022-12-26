#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Graph {
public:
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        vector<string> airlines;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string airline, int weight = 1);

    // Depth-First Search
    void dfs(int v);

    // Breadth-First Search
    void bfs(int v);
};

#endif
