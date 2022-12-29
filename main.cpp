#include <bits/stdc++.h>
#include "Airport.h"
#include "Airline.h"
#include "graph.h"
#include "Coord2dTree.h"

using namespace std;

void read_airports();
void read_airlines();
void read_flights();
void clear() {for (int i = 0; i < 50; i++) cout << endl;}
void wait() {cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.get();}
void print_menu();
void print_menu1();
void print_shortest_paths_airports();
void print_menu2();
void print_menu3();
void print_menu4();
void print_menu5();
void print_airport_stats(int, Airport &);
void list_shortest_paths(int, int);


int getCitiesNumber(set<int> &set1);

int getCountriesNumber(set<int> &set1);

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
    cout << "Trajetos mais curtos de " << airports.at(src).getName() << " para " << airports.at(dest).getName() << endl;

    if (path.empty())
        cout << "Não há trajetos disponíveis para os critérios especificados." << endl;

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
void list_shortest_paths(int src, int dest, set<string> &airlines_to_consider) {
    list<li> path = graph.least_flights(src, dest, airlines_to_consider);

    cout << "Companhias aéreas consideradas: ";
    for (const auto& a : airlines_to_consider) cout << a << " ";
    cout << endl;

    cout << "Trajetos mais curtos de " << airports.at(src).getName() << " para " << airports.at(dest).getName() << endl;

    if (path.empty())
        cout << "Não há trajetos disponíveis para os critérios especificados." << endl;

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
        cout << "| 5. Informações sobre um aeroporto      |" << endl;
        cout << "| 0. Sair                                |" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        if (choice != 0) {
            switch (choice) {
                case 1:
                    print_menu1(); break;
                case 2:
                    print_menu2(); break;
                case 3:
                    print_menu3(); break;
                case 4:
                    print_menu4(); break;
                case 5:
                    print_menu5(); break;
                default:
                    break;
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
        if (choice != 0) {
            switch (choice) {
                case 1:
                    print_shortest_paths_airports();
                    wait(); break;
                /*case 2:
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
                    cout << "Opcao invalida!" << endl;*/
            }
        }
    } while (choice != 0);
}

void print_menu2() {}
void print_menu3() {}
void print_menu4() {}
void print_menu5() {
    string code;
    cout << "Escolha o código do aeroporto: ";
    cin >> code; cout << endl;

    transform(code.begin(), code.end(), code.begin(), ::toupper);

    if (airport_codes.find(code) == airport_codes.end()) {
        cout << "Código inválido!" << endl; wait(); return;
    }

    int id = airport_codes[code];
    Airport airport = airports.at(id);
    print_airport_stats(id, airport);
    wait();
}

void print_airport_stats(int id, Airport &airport) {
    cout << "Código: " << airport.getCode() << endl;
    cout << "Nome: " << airport.getName() << endl;
    cout << "Cidade: " << airport.getCity() << endl;
    cout << "País: " << airport.getCountry() << endl;
    cout << "Coordenadas: " << airport.getLatitude() << ", " << airport.getLongitude() << endl;
    cout << "Existem " << graph.getOutDegree(id) << " voos de saída." << endl;
    cout << graph.getAirlinesNumber(id) << " companhias aéreas voam a partir deste aeroporto." << endl;
    cout << "Existem voos para " << graph.getDestinationsNumber(id) << " destinos diferentes," << endl;
    cout << "que pertencem a " << graph.getDestinationsCountries(id, airports) << " países diferentes." << endl;

    //generate random number from 1 to 5
    int r = rand() % 5 + 1;
    set<int> destinations = graph.getDestinations(id, r);
    cout << "Com apenas " << r << " voos, é possível chegar a " << destinations.size() << " aeroportos diferentes," << endl;
    cout << "a " << getCitiesNumber(destinations) << " cidades diferentes ";
    cout << "e a " << getCountriesNumber(destinations) << " países diferentes." << endl;
}

int getCountriesNumber(set<int> &set1) {
    set<string> countries;
    for (int id : set1) {
        countries.insert(airports.at(id).getCountry());
    }
    return (int) countries.size();
}

int getCitiesNumber(set<int> &set1) {
    set<string> cities;
    for (int id : set1) {
        cities.insert(airports.at(id).getCity());
    }
    return (int) cities.size();
}

void print_shortest_paths_airports() {
    string src, dest;
    cout << "Escolha o aeroporto de origem: "; cin >> src;
    transform(src.begin(), src.end(), src.begin(), ::toupper);

    if (airport_codes.find(src) == airport_codes.end()) {
        cout << "Aeroporto nao encontrado!" << endl; wait();
        return;
    }

    cout << "Escolha o aeroporto de destino: "; cin >> dest;
    transform(dest.begin(), dest.end(), dest.begin(), ::toupper);

    if (airport_codes.find(dest) == airport_codes.end()) {
        cout << "Aeroporto nao encontrado!" << endl; wait();
        return;
    }

    cout << "Pretende pesquisar apenas para certas companhias aéreas? (s/n) ";
    string op; cin >> op;
    // make op lowercase
    transform(op.begin(), op.end(), op.begin(), ::toupper);

    if (op == "S") {
        set<string> airlines_to_consider;
        cout << "Liste os códigos das companhias aéreas que pretende considerar (escreva 'fim' para terminar): ";
        string airline;
        while (cin >> airline) {
            transform(airline.begin(), airline.end(), airline.begin(), ::toupper);
            if (airline == "FIM") break;
            if (airline_codes.find(airline) != airline_codes.end()) airlines_to_consider.insert(airline);
            else cout << "Companhia aérea não encontrada!" << endl;
        }
        list_shortest_paths(airport_codes[src], airport_codes[dest], airlines_to_consider);
    } else {
        list_shortest_paths(airport_codes[src], airport_codes[dest]);
    }
}

