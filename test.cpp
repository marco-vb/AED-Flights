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

    vector<pair<double, double>> coords;
    Coord2dTree tree;

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

        coords.push_back({lat, lon});
        tree.insert({lat, lon});
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

    // Coord2dTree tree;
    // vector<pair<double, double>> coords;
    int n = 0;

//    for (int i = 0; i < 20000; i++) {
//        double lat = (double) rand() / RAND_MAX * 180 - 90;
//        double lon = (double) rand() / RAND_MAX * 360 - 180;
//        coords.push_back({lat, lon});
//        tree.insert(lat, lon);
//    }
    cout << "Testing nearest neighbor search: KdTree" << endl;
    cout << "Loaded " << coords.size() << " airports." << endl;

    for (int i = 0; i < 4200; i++) {
        double lat = (double) rand() / RAND_MAX * 180 - 90;
        double lon = (double) rand() / RAND_MAX * 360 - 180;
        double r = (double) rand() / RAND_MAX * 20000;
        // lat = 59.2264; lon = 101.753; r = 4956.21;
        vector<pair<double, double>> best = findInRadius(coords, {lat, lon}, r);
        vector<pair<double, double>> found = tree.in_radius(lat, lon, r);
        //vector<pair<double, double>> found = best;

//        pair<double, double> best = findClosest(coords, {lat, lon});
        //pair<double, double> found = tree.nearest(lat, lon);
        n++;

        set<pair<double, double>> sbest;
        for (auto &p : best) {
            sbest.insert(p);
        }
        set<pair<double, double>> sfound;
        for (auto &p : found) {
            sfound.insert(p);
        }
        if (sbest != sfound) {
            cout << "Searching for " << lat << ", " << lon << " within " << r << " km" << endl;

            cout << endl;
            cout << "Test " << n << " failed!" << endl;
            cout << "Best: " << endl;
            for (auto &p : best) {
                if(sfound.find(p) == sfound.end()) {
                    cout << p.first << " " << p.second << endl;
                    cout << "Distance: " << haversine(lat, lon, p.first, p.second) << endl;
                }}
            cout << "Found: " << endl;
            for (auto &p : found) {
                if(sbest.find(p) == sbest.end()) {
                    cout << p.first << " " << p.second << endl;
                    cout << "Distance: " << haversine(lat, lon, p.first, p.second) << endl;
                }
            }
            cout << "Lat: " << lat << " Lon: " << lon << endl;
            return 0;
        }

//        if(best.first != found.first || best.second != found.second) {
//            cout << n << endl;
//            cout << "Error" << endl;
//            cout << "Lat: " << lat << " Lon: " << lon << endl;
//            cout << "Best: " << best.first << " " << best.second << endl;
//            cout << "Best Dist: " << haversine(lat, lon, best.first, best.second) << endl;
//            cout << "Found: " << found.first << " " << found.second << endl;
//            cout << "Found Dist: " << haversine(lat, lon, found.first, found.second) << endl;
//            cout << "0 Dist: " << haversine(lat, lon, lat, -180) << endl;
//        }
    }
    cout << "Tested with " << n << " random points." << endl;
//
//    set<string> airline_set = {"TAP"};
//    set<int> ap = graph.getArticulationPoints(airline_set);
//    if(ap.empty()) cout << "No articulation points" << endl;
//    else {
//        cout << "Articulation points: " << endl;
//        for(auto &a : ap) {
//            cout << airports.at(a).getCode() << '-' << airports.at(a).getName() << '-' << a << endl;
//        }
//        cout << airports.at(523).getName() << ' ' << 523 << endl;
//    }


    return 0;
}
