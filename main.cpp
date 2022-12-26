#include <bits/stdc++.h>
#include "Airport.h"
#include "graph.h"

using namespace std;

int main() {
    unordered_map<string, int> codes;
    unordered_map<int, Airport> airports;
    ifstream airports_file("data/airports.csv");

    string line;
    int i = 1;
    while (getline(airports_file, line)) {
        string code = line.substr(0, 3);
        string name = line.substr(4, line.find(",") - 4);
        string city = line.substr(line.find(",") + 1, line.find(",") - 1);
        string country = line.substr(line.find(",") + 1, line.find(",") - 1);
        double latitude = stod(line.substr(line.find(",") + 1, line.find(",") - 1));
        double longitude = stod(line.substr(line.find(",") + 1, line.find(",") - 1));

        Airport airport(code, name, city, country, latitude, longitude);
        codes.insert({code, i});
        airports.insert({i, airport});
        i++;
    }
    airports_file.close();
    Graph graph((int) codes.size(), true);

    ifstream flights_file("data/flights.csv");
    while (getline(flights_file, line)) {
        string origin = line.substr(0, 3);
        string destination = line.substr(4, line.find(",") - 4);
        string airline = line.substr(line.find(",") + 1, line.find(",") - 1);

        graph.addEdge(codes[origin], codes[destination], airline);
    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
