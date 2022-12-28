#include <bits/stdc++.h>
#include "Airport.h"
#include "Airline.h"
#include "graph.h"

using namespace std;

int main() {
    unordered_map<string, int> airport_codes;
    unordered_map<int, Airport> airports;
    ifstream airports_file("../data/airports.csv");

    string line;
    int i = 1;
    while (getline(airports_file, line)) {
        istringstream ss(line);
        string code, name, city, country;
        double lat, lon;
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        ss >> lat;
        ss.ignore();
        ss >> lon;

        Airport airport(code, name, city, country, lat, lon);
        airport_codes.insert({code, i});
        airports.insert({i, airport});
        i++;
    }
    airports_file.close();
    Graph graph((int) airport_codes.size(), true);

    unordered_map<string, int> airline_codes;
    unordered_map<int, Airline> airlines;

    ifstream airlines_file("../data/airlines.csv");

    i = 1;
    while (getline(airlines_file, line)) {
        istringstream ss(line);
        string code, name, callSign, country;
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callSign, ',');
        getline(ss, country);
        Airline airline(code, name, callSign, country);
        airline_codes.insert({code, i});
        airlines.insert({i, airline});
        i++;
    }

    ifstream flights_file("../data/flights.csv");
    while (getline(flights_file, line)) {
        istringstream ss(line);
        string origin, destination, airline;
        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, airline);

        graph.addEdge(airport_codes[origin], airport_codes[destination], airline);
    }

    /*for (int v = 1; v <= 4; v++) {
        for (auto &e : graph.nodes.at(v).adj) {
            cout << airports.at(v).getName() << " -> " << airports.at(e.dest).getName() << " " << endl;
        }
    }*/

    // find the shortest path between two airports
    int src = airport_codes["SJZ"];
    int dest = airport_codes["YKS"];
    list<li> path = graph.least_flights(src, dest);
    cout << "Least flights from: " << airports.at(src).getName() << " to " << airports.at(dest).getName() << endl;
    for (auto &l : path) {
        for (auto &k: l) {
            if (k == l.back())
                cout << airports.at(k).getName() << endl;
            else
                cout << airports.at(k).getName() << " -> ";
        }
        cout << endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
