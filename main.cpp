#include <bits/stdc++.h>
#include "Airport.h"
#include "Airline.h"
#include "graph.h"
#include "Coord2dTree.h"

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

    Coord2dTree tree;
    vector<pair<double, double>> coords;
    int n = 0;

    for (int i = 0; i < 200; i++) {
        double lat = (double) rand() / RAND_MAX * 180 - 90;
        double lon = (double) rand() / RAND_MAX * 360 - 180;
        coords.push_back({lat, lon});
        tree.insert(lat, lon);
    }
    for (int i = 0; i < 200; i++) {
        double lat = (double) rand() / RAND_MAX * -90;
        double lon = (double) rand() / RAND_MAX * 360 - 180;
        pair<double, double> best = make_pair(0, 0);
        double best_dist = 1000000000;
        for(pair<double, double> coord : coords) {
            if(haversine(lat, lon, coord.first, coord.second) < best_dist) {
                best = coord;
                best_dist = haversine(lat, lon, coord.first, coord.second);
            }
        }
        pair<double, double> found = tree.nearest(lat, lon);
        if(best.first != found.first || best.second != found.second) {
            cout << n << endl;
            cout << "Error" << endl;
            cout << "Lat: " << lat << " Lon: " << lon << endl;
            cout << "Best: " << best.first << " " << best.second << endl;
            cout << "Best Dist: " << best_dist << endl;
            cout << "Found: " << found.first << " " << found.second << endl;
            cout << "Found Dist: " << haversine(lat, lon, found.first, found.second) << endl;
            cout << "0 Dist: " << haversine(lat, lon, lat, -180) << endl;
        }
        n++;
    }
    cout << n << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
