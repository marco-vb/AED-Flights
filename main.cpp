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
void print_menu2();
void print_menu3();
void print_menu4();
void list_shortest_paths(int, int);
struct pair_hash{
    size_t operator () (const std::pair<double, double> &pair) const;
};

unordered_map<string, int> airport_codes;
unordered_map<int, Airport> airports;
unordered_map<string, int> airline_codes;
unordered_map<int, Airline> airlines;
unordered_map<pair<double, double>, int, pair_hash> airport_coords;
unordered_map<string, vector<int>> airport_cities;
Graph graph;
Coord2dTree tree;

int main() {
    read_airports();
    graph = Graph((int) airport_codes.size(), true);
    read_airlines();
    read_flights();
    print_menu();
    return 0;
}


size_t pair_hash::operator () (const std::pair<double, double> &pair) const {
    return std::hash<double>()(pair.first) ^ std::hash<double>()(pair.second);
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

void list_shortest_paths(vector<int> src, vector<int> dest) {
    list<li> path = graph.least_flights(src, dest);
    cout << "Trajetos mais curtos de " << airports.at(src.front()).getName() << " para " << airports.at(dest.front()).getCity() << endl;

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

void list_shortest_paths(vector<int> src, vector<int> dest, set<string> &airlines_to_consider) {
    list<li> path = graph.least_flights(src, dest, airlines_to_consider);

    cout << "Companhias aéreas consideradas: ";
    for (const auto& a : airlines_to_consider) cout << a << " ";
    cout << endl;

    cout << "Trajetos mais curtos de " << airports.at(src.front()).getCity() << " para " << airports.at(dest.front()).getCity() << endl;

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

pair<double, double> string_to_coords(string s) {
    int i = 0;
    while (s[i] != 'N' && s[i] != 'S'){
        i++;
        if(i == s.size()) return make_pair(100, 200);
    }
    if(i+3 >= s.size() || (s[s.size()-1] != 'E' && s[s.size()-1] != 'W')) return make_pair(100, 200);

    double lat = stod(s.substr(0, i));
    if (s[i] == 'S') lat *= -1;
    double lon = stod(s.substr(i + 2, s.size() - i - 3));
    if (s[s.size() - 1] == 'W') lon *= -1;

    if(lat < -90 || lat > 90 || lon < -180 || lon > 180) return make_pair(100, 200);
    return make_pair(lat, lon);
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
        airport_coords.insert({{lat, lon}, i});
        tree.insert(lat, lon);
        if(airport_cities.find(city) == airport_cities.end()) {
            vector<int> v; v.push_back(i);
            airport_cities.insert({city, v});
        } else {
            airport_cities.at(city).push_back(i);
        }
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
                case 1: {
                    cout << "Escolha o aeroporto de origem: ";
                    cin >> src;
                    if (airport_codes.find(src) == airport_codes.end()) {
                        cout << "Aeroporto nao encontrado!" << endl;
                        wait();
                        break;
                    }

                    cout << "Escolha o aeroporto de destino: ";
                    cin >> dest;
                    if (airport_codes.find(dest) == airport_codes.end()) {
                        cout << "Aeroporto nao encontrado!" << endl;
                        wait();
                        break;
                    }

                    cout << "Pretende pesquisar apenas para certas companhias aéreas? (s/n) ";
                    string op;
                    cin >> op;

                    if (op == "s" || op == "S") {
                        set<string> airlines_to_consider;
                        cout
                                << "Liste os códigos das companhias aéreas que pretende considerar (escreva 'fim' para terminar): ";
                        string airline;
                        while (cin >> airline && airline != "fim" && airline != "FIM") {
                            if (airline_codes.find(airline) != airline_codes.end()) {
                                airlines_to_consider.insert(airline);
                            } else {
                                cout << "Companhia aérea não encontrada!" << endl;
                            }
                        }
                        list_shortest_paths(airport_codes[src], airport_codes[dest], airlines_to_consider);
                    } else {
                        list_shortest_paths(airport_codes[src], airport_codes[dest]);
                    }
                    wait();
                    break;
                }
                case 2:{
                    cout << "Escolha a cidade de origem: ";
                    getline(cin >> ws, src);
                    if (airport_cities.find(src) == airport_cities.end()) {
                        cout << "Cidade nao encontrada!" << endl;
                        wait();
                        break;
                    }

                    cout << "Escolha a cidade de destino: ";
                    getline(cin >> ws, dest);
                    if (airport_cities.find(dest) == airport_cities.end()) {
                        cout << "Cidade nao encontrada!" << endl;
                        wait();
                        break;
                    }

                    cout << "Pretende pesquisar apenas para certas companhias aéreas? (s/n) ";
                    string op;
                    cin >> op;

                    if (op == "s" || op == "S") {
                        set<string> airlines_to_consider;
                        cout << "Liste os códigos das companhias aéreas que pretende considerar (escreva 'fim' para terminar): ";
                        string airline;
                        while (cin >> airline && airline != "fim" && airline != "FIM") {
                            if (airline_codes.find(airline) != airline_codes.end()) {
                                airlines_to_consider.insert(airline);
                            } else {
                                cout << "Companhia aérea não encontrada!" << endl;
                            }
                        }
                        list_shortest_paths(airport_cities[src], airport_cities[dest], airlines_to_consider);
                    } else {
                        list_shortest_paths(airport_cities[src], airport_cities[dest]);
                    }
                    wait();
                    break;
                }

                case 3: {
                    cout << "Escolha as coordenadas de origem (e.g. '16.23N 64.1W'): ";
                    getline(cin >> ws, src);
                    pair <double, double> src_coords = string_to_coords(src);
                    if (src_coords.first == 100 &&
                        src_coords.second == 200) {
                        cout << "Erro ao introduzir as coordenadas!" << endl;
                        wait();
                        break;
                    }

                    cout << endl << "Escolha as coordenadas de destino (e.g. '16.23N 64.1W'): ";
                    getline(cin >> ws, dest);
                    pair <double, double> dest_coords = string_to_coords(dest);
                    if (dest_coords.first == 100 &&
                        dest_coords.second == 200) {
                        cout << "Erro ao introduzir as coordenadas!" << endl;
                        wait();
                        break;
                    }

                    cout << "Pretende pesquisar apenas para certas companhias aéreas? (s/n) ";
                    string op;
                    cin >> op;

                    if (op == "s" || op == "S") {
                        set<string> airlines_to_consider;
                        cout << "Liste os códigos das companhias aéreas que pretende considerar (escreva 'fim' para terminar): ";
                        string airline;
                        while (cin >> airline && airline != "fim" && airline != "FIM") {
                            if (airline_codes.find(airline) != airline_codes.end()) {
                                airlines_to_consider.insert(airline);
                            } else {
                                cout << "Companhia aérea não encontrada!" << endl;
                            }
                        }
                        list_shortest_paths(airport_coords[tree.nearest(src_coords)],
                                            airport_coords[tree.nearest(dest_coords)],
                                            airlines_to_consider);
                    } else {
                        list_shortest_paths(airport_coords[tree.nearest(src_coords)],
                                            airport_coords[tree.nearest(dest_coords)]);
                    }
                    wait();
                    break;
                }
                default:
                    cout << "Opcao invalida!" << endl;
            }
        }
    } while (choice != 0);
}

