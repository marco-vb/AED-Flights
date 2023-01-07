#include <bits/stdc++.h>
#include "Graph.h"

Graph::Graph() {
    n = 0;
}
Graph::Graph(int num) : n(num), nodes(num+1) {}

void Graph::addEdge(int src, int dest, string airline, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    for (Edge &e : nodes[src].adj)
        if (e.dest == dest) {
            e.airlines.insert(airline);
            return;
        }
    nodes[src].adj.push_back({dest, weight, {airline}});
}

int Graph::getOutDegree(int i) {
    return (int) nodes[i].adj.size();
}

int Graph::getAirlinesNumber(int i) {
    set<string> airlines;
    for (const auto& e : nodes[i].adj)
        for (const auto& a : e.airlines)
            airlines.insert(a);

    return (int) airlines.size();
}
int Graph::getDestinationsNumber(int i) {
    set<int> destinations;
    for (const auto& e : nodes[i].adj)
        destinations.insert(e.dest);

    return (int) destinations.size();
}
int Graph::getDestinationsCountries(int i, unordered_map<int, Airport> &airports) {
    set<string> countries;
    for (const auto& e : nodes[i].adj)
        countries.insert(airports.at(e.dest).getCountry());

    return (int) countries.size();
}
int Graph::getNumEdges() {
    int num_edges = 0;
    for (int i = 1; i <= n; ++i)
        num_edges += (int) nodes[i].adj.size();

    return num_edges;
}
int Graph::getCompanies() {
    set<string> companies;
    for (int i = 1; i <= n; ++i)
        for (const auto& e : nodes[i].adj)
            for (const auto& c : e.airlines)
                companies.insert(c);

    return (int) companies.size();
}
int Graph::getDiameter() {
    int diameter = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
        queue<int> q;
        q.push(i);
        nodes[i].visited = true;
        nodes[i].distance = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const auto& e : nodes[u].adj) {
                int w = e.dest;
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].distance = nodes[u].distance + 1;
                    diameter = max(diameter, nodes[w].distance);
                }
            }
        }
    }

    return diameter;
}
set<int> Graph::getDestinations(int src, int r) {
    set<int> destinations;
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    queue<int> q;
    q.push(src);
    nodes[src].visited = true;
    nodes[src].distance = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                if (nodes[w].distance <= r) {
                    q.push(w);
                    destinations.insert(w);
                }
            }
        }
    }

    return destinations;
}
vector<Graph::Node> Graph::getNodes() const {
    return nodes;
}
vector<pii> Graph::getTopAirports(int i) {
    vector<pii> airports(n);
    for (int v = 1; v <= n; v++) {
        airports[v-1] = make_pair(v, getDestinationsNumber(v));
    }
    sort(airports.begin(), airports.end(), [](const pii& a, const pii& b) {return a.second > b.second;});

    return vector<pii>(airports.begin(), airports.begin() + i);
}
set<int> Graph::getArticulationPoints() {
    set<int> articulationPoints;
    vector<int> low(n+1);
    vector<int> num(n+1);
    unordered_set<int> s;
    for(int i = 1; i <= n; i++)
        nodes[i].visited = false;
    for(int i = 1; i <= n; i++)
        if(!nodes[i].visited){
            articulationPointsDFS(i, 0, num, low, s, articulationPoints, true);
        }
    return articulationPoints;
}
set<int> Graph::getArticulationPoints(set<string> &airlines_to_consider) {
    set<int> articulationPoints;
    vector<int> low(n+1);
    vector<int> num(n+1);
    unordered_set<int> s;
    for(int i = 1; i <= n; i++)
        nodes[i].visited = false;
    for(int i = 1; i <= n; i++)
        if(!nodes[i].visited){
            articulationPointsDFS(i, 0, num, low, s, articulationPoints, airlines_to_consider, true);
        }
    return articulationPoints;
}

void Graph::articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, bool first){
    nodes[v].visited = true;
    num[v] = index;
    low[v] = index;
    index++;
    bool is_ap = false;
    s.insert(v);
    int n_adj = 0;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) {
            n_adj++;
            articulationPointsDFS(w, index, num, low, s, ap);
            low[v] = min(low[v], low[w]);
            if(low[w] >= num[v]) {
                is_ap = true;
                ap.insert(v);
            }
        }
        else if (s.find(w) != s.end())
            low[v] = min(low[v], num[w]);
    }
    if(is_ap && first && n_adj <= 1)
        ap.erase(v);
    s.erase(v);
}
set<int> Graph::articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, set<string> &airlines_to_consider, bool first){
    nodes[v].visited = true;
    num[v] = index;
    low[v] = index;
    index++;
    bool is_ap = false;
    s.insert(v);
    int n_adj = 0;
    for (auto e : nodes[v].adj) {
        set<string> intersection;
        set_intersection(e.airlines.begin(), e.airlines.end(), airlines_to_consider.begin(), airlines_to_consider.end(), inserter(intersection, intersection.begin()));
        if (intersection.empty()) continue;

        int w = e.dest;
        if (!nodes[w].visited) {
            n_adj++;
            set<int> temp = articulationPointsDFS(w, index, num, low, s, ap, airlines_to_consider);
            for(int t : temp) ap.insert(t);
            low[v] = min(low[v], low[w]);
            if(low[w] >= num[v] && !first) {
                is_ap = true;
                ap.insert(v);
            }
        }
        if(is_ap && first && n_adj <= 1)
            ap.erase(v);
        else if (s.find(w) != s.end())
            low[v] = min(low[v], num[w]);
    }
    s.erase(v);
    return ap;
}

list<lp> Graph::least_flights(vector<int> sources, vector<int> destination) {
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    vector<vector<pis>> previous(n+1, vector<pis>());

    queue<int> q;
    for(const auto& s : sources) {
        q.push(s);
        nodes[s].visited = true;
        nodes[s].distance = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                previous[w].push_back({u, *e.airlines.begin()});
            } else if (nodes[w].distance == nodes[u].distance + 1) {
                previous[w].push_back({u, *e.airlines.begin()});
            }
        }
    }

    lp all_min;
    int min_dist = INT_MAX;
    for(int d : destination) {
        if(nodes[d].distance != -1 && nodes[d].distance < min_dist) {
            min_dist = nodes[d].distance;
        }
    }
    for(int d : destination) {
        if(nodes[d].distance == min_dist) {
            all_min.push_back({d, ""});
        }
    }

    list<lp> paths;
    if(min_dist == INT_MAX) return paths;
    for(auto d : all_min) {
        lp path;
        path.push_back(d);
        paths.push_back(path);
    }
    for (int i = 0; i < min_dist; ++i) {
        list<lp> new_paths;
        for (const auto& p : paths) {
            for (const auto& node : previous[p.front().first]) {
                lp new_path = p;
                new_path.push_front(node);
                new_paths.push_back(new_path);
            }
        }
        paths = new_paths;
    }
    return paths;
}
list<lp> Graph::least_flights(const vector<int>& sources, const vector<int>& dest, const set<string> &airlines_to_consider) {
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    vector<vector<pis>> previous(n+1, vector<pis>());

    queue<int> q;
    for(const auto& s : sources) {
        q.push(s);
        nodes[s].visited = true;
        nodes[s].distance = 0;
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            set<string> intersection;
            set_intersection(e.airlines.begin(), e.airlines.end(), airlines_to_consider.begin(), airlines_to_consider.end(), inserter(intersection, intersection.begin()));
            if (intersection.empty()) continue;
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                previous[w].push_back({u, *intersection.begin()});
            } else if (nodes[w].distance == nodes[u].distance + 1) {
                previous[w].push_back({u, *intersection.begin()});
            }
        }
    }

    lp all_min;
    int min_dist = INT_MAX;
    for(int d : dest) {
        if(nodes[d].distance != -1 && nodes[d].distance < min_dist) {
            min_dist = nodes[d].distance;
        }
    }
    for(int d : dest) {
        if(nodes[d].distance == min_dist) {
            all_min.push_back({d, ""});
        }
    }

    list<lp> paths;
    if(min_dist == INT_MAX) return paths;
    for(auto& d : all_min) {
        lp path;
        path.push_back(d);
        paths.push_back(path);
    }
    for (int i = 0; i < min_dist; ++i) {
        list<lp> new_paths;
        for (const auto& p : paths) {
            for (const auto& node : previous[p.front().first]) {
                lp new_path = p;
                new_path.push_front(node);
                new_paths.push_back(new_path);
            }
        }
        paths = new_paths;
    }
    return paths;
}
list<lp> Graph::least_flights_with_distance(const vector<int>& src, const vector<int>& dest, const set<string>& airlines_to_consider) {
    for (int i = 1; i <= n; i++) {
        nodes[i].distance = INT_MAX;
        nodes[i].visited = false;
    }

    queue<int> q;
    vector<pis> prev(n+1, {0, ""});

    for (const int & i : src) {
        nodes[i].distance = 0;
        q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (nodes[v].visited) continue;
        nodes[v].visited = true;
        for (const auto& e : nodes[v].adj) {
            set<string> intersection;
            set_intersection(e.airlines.begin(), e.airlines.end(), airlines_to_consider.begin(), airlines_to_consider.end(), inserter(intersection, intersection.begin()));
            if (intersection.empty()) continue;
            int w = e.dest;
            if (nodes[w].distance > nodes[v].distance + e.weight) {
                nodes[w].distance = nodes[v].distance + e.weight;
                prev[w] = {v, *intersection.begin()};
                q.push(w);
            }
        }
    }

    list<lp> paths;
    for (const int & i : dest) {
        if (nodes[i].distance == INT_MAX) continue;
        lp path;
        pis v = {i, ""};
        while (v.first != 0) {
            path.push_front(v);
            v = prev[v.first];
        }
        paths.push_back(path);
    }

    for (auto& p : paths) {
        p.push_front({nodes[p.back().first].distance, ""});
    }

    return paths;
}

list<lp> Graph::least_flights_with_distance(const vector<int>& src, const vector<int>& dest) {
    for (int i = 1; i <= n; i++) {
        nodes[i].distance = INT_MAX;
        nodes[i].visited = false;
    }

    queue<int> q;
    vector<pis> prev(n + 1, {0, ""});

    for (const int &i: src) {
        nodes[i].distance = 0;
        q.push(i);
    }

    //Dijkstra's algorithm
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (nodes[v].visited) continue;
        nodes[v].visited = true;
        for (const auto &e: nodes[v].adj) {
            int w = e.dest;
            if (nodes[w].distance > nodes[v].distance + e.weight) {
                nodes[w].distance = nodes[v].distance + e.weight;
                prev[w] = {v, *e.airlines.begin()};
                q.push(w);
            }
        }
    }

    //Find the shortest path between src and dest
    list<lp> paths;
    for (const int &i: dest) {
        if (nodes[i].distance == INT_MAX) continue;
        lp path;
        pis v = {i, ""};
        while (v.first != 0) {
            path.push_front(v);
            v = prev[v.first];
        }
        paths.push_back(path);
    }

    for (auto &p: paths) {
        p.push_front({nodes[p.back().first].distance, ""});
    }

    return paths;
}