#include <bits/stdc++.h>
#include "Airport.h"
#include "Airline.h"
#include "graph.h"

using namespace std;

void read_airports();
void read_airlines();
void read_flights();
void clear() {for (int i = 0; i < 50; i++) cout << endl;}
void wait() {cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.get();}
void print_menu();
void print_menu1();
void print_menu2();
void print_menu3();
void print_menu4();
void list_shortest_paths(int, int);

unordered_map<string, int> airport_codes;
unordered_map<int, Airport> airports;
unordered_map<string, int> airline_codes;
unordered_map<int, Airline> airlines;
Graph graph;

int main() {
    read_airports();
    graph = Graph((int) airport_codes.size(), true);
    read_airlines();
    read_flights();
    print_menu();
    return 0;
}

void list_shortest_paths(int src, int dest) {
    list<li> path = graph.least_flights(src, dest);
    cout << "Trajetos mais curtos: " << airports.at(src).getName() << " -> " << airports.at(dest).getName() << endl;
    for (auto &l : path) {
        for (auto &k: l) {
            if (k == l.back())
                cout << airports.at(k).getName() << endl;
            else
                cout << airports.at(k).getName() << " -> ";
        }
        cout << endl;
    }
}

void read_airports() {
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
}
void read_airlines() {
    ifstream airlines_file("../data/airlines.csv");

    string line;
    int i = 1;
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
}
void read_flights() {
    ifstream flights_file("../data/flights.csv");
    string line;
    while (getline(flights_file, line)) {
        istringstream ss(line);
        string origin, destination, airline;
        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, airline);

        graph.addEdge(airport_codes[origin], airport_codes[destination], airline);
    }
}

void print_menu() {
    int choice;
    do {
        clear();
        cout << "------------------------------------------" << endl;
        cout << "|         Simulador de Voos 3000         |" << endl;
        cout << "| 1. Rotas sem distâncias                |" << endl;
        cout << "| 2. Rotas com distâncias                |" << endl;
        cout << "| 3. Estatísticas da rede                |" << endl;
        cout << "| 4. Estudos sobre a rede                |" << endl;
        cout << "| 0. Sair                                |" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        if (choice != 0) {
            switch (choice) {
                case 1:
                    print_menu1();
                    break;
                /*case 2:
                    menu_partial_lists(&students, &classes, &courses, &classCourses, &slots);
                    break;
                case 3:
                    menu_schedules(&students, &classes, &courses, &classCourses, &slots);
                    break;
                case 4:
                    menu_requests(&students, &classes, &courses, &classCourses, &slots, &requests);
                    break;
                case 5:
                    processAllRequests(&students, &classes, &courses, &classCourses, &requests);
                    wait();
                    break;*/
                default:
                    cout << "Opcao invalida!" << endl;
            }
        }
    } while (choice != 0);

    clear();
}

void print_menu1() {
    int choice;
    do {
        clear();
        cout << "------------------------------------------" << endl;
        cout << "|         Simulador de Voos 3000         |" << endl;
        cout << "| 1. Rotas mais curtas (aeroportos)      |" << endl;
        cout << "| 2. Rotas mais curtas (cidades)         |" << endl;
        cout << "| 3. Rotas mais curtas (locais)          |" << endl;
        cout << "| 0. Voltar                              |" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        string src, dest;
        if (choice != 0) {
            switch (choice) {
                case 1:
                    cout << "Escolha o aeroporto de origem: "; cin >> src;
                    cout << "Escolha o aeroporto de destino: "; cin >> dest; cout << endl;
                    list_shortest_paths(airport_codes[src], airport_codes[dest]);
                    wait(); break;
                case 2:
                    cout << "Escolha a cidade de origem: "; cin >> src;
                    cout << endl << "Escolha a cidade de destino: "; cin >> dest; cout << endl;
                    //TODO
                    wait();
                    break;
                case 3:
                    cout << "Escolha o local de origem: "; cin >> src;
                    cout << endl << "Escolha o local de destino: "; cin >> dest; cout << endl;
                    //TODO
                    wait(); break;
                default:
                    cout << "Opcao invalida!" << endl;
            }
        }
    } while (choice != 0);
}


