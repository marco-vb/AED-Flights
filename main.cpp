#include <bits/stdc++.h>
#include "Airport.h"
#include "Airline.h"
#include "graph.h"
#include "Coord2dTree.h"

using namespace std;

typedef pair<int, int> pii;

void read_airports();
void read_airlines();
void read_flights();
void clear() {for (int i = 0; i < 50; i++) cout << endl;}
void wait() {cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.get();}
void print_menu();
void print_menu1();
void print_shortest_paths(const vector<int>& src, const vector<int>& dest);
int get_airport(bool is_origin);
vector<int> get_city(bool is_origin);
int get_coordinates(bool is_origin);
vector<int> get_coordinates_km(bool is_origin);
void print_menu2();
void print_menu3();
void print_global_stats();
void print_menu4();
void print_menu5();
void print_airport_stats(int, Airport &);
void list_shortest_paths(int, int);
void print_articulation_points();
struct pair_hash{
    size_t operator () (const std::pair<double, double> &pair) const;
};


int getCitiesNumber(set<int> &set1);

int getCountriesNumber(set<int> &set1);

void print_country_stats();

void print_airline_stats();

void print_shortest_paths_distance(vector<int> vector1, vector<int> vector2);

void list_shortest_paths_with_distance(vector<int> src, vector<int> dest, const set<string>& airlines_to_consider);

void list_shortest_paths_with_distance(vector<int> src, vector<int> dest);

unordered_map<string, int> airport_codes;
unordered_map<int, Airport> airports;
unordered_map<string, int> airline_codes;
unordered_map<int, Airline> airlines;
unordered_map<pair<double, double>, int, pair_hash> airport_coords;
unordered_map<string, vector<int>> airport_cities;
unordered_map<string, vector<int>> airport_countries;
unordered_map<string, vector<int>> airport_airlines;
unordered_map<string, unordered_set<string>> cities_country;
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

std::string set_to_string(const std::set<std::string>& set) {
    std::stringstream result;
    bool first = true;
    for (const std::string& s : set) {
        if (!first) {
            result << ", ";
        }
        result << s;
        first = false;
    }

    std::string str = result.str();
    std::size_t last_comma = str.find_last_of(',');
    if (last_comma != std::string::npos) {
        str.replace(last_comma, 2, " & ");
    }
    return str;
}
void list_shortest_paths(vector<int> src, vector<int> dest) {
    list<li> path = graph.least_flights(src, dest);
    set<string> o; set<string> d; string src_string; string dst_string;
    if(src.size() == 1)
        src_string = airports.at(src[0]).getName();
    else {
        for (auto &s: src)
            o.insert(airports.at(s).getCity());
        src_string = set_to_string(o);
    }
    if(dest.size() == 1)
        dst_string = airports.at(dest[0]).getName();
    else {
        for (auto &s: dest)
            d.insert(airports.at(s).getCity());
        dst_string = set_to_string(d);
    }

    cout << endl << "Trajetos mais curtos de " << src_string << " para " << dst_string << endl << endl;

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

    cout << endl << "Trajetos mais curtos de " << airports.at(src.front()).getCity() << " para " << airports.at(dest.front()).getCity() << endl;

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
    double lat; double lon;
    int i = 0;
    while (s[i] != 'N' && s[i] != 'S' && s[i] != ','){
        i++;
        if(i == s.size()) return make_pair(100, 200);
    }

    if(s[i] == ','){
        lat = stod(s.substr(0, i));
        lon = stod(s.substr(i+1, s.size()-i-1));
    }
    else {
        if(i+3 >= s.size() || (s[s.size()-1] != 'E' && s[s.size()-1] != 'W')) return make_pair(100, 200);

        lat = stod(s.substr(0, i));
        if (s[i] == 'S') lat *= -1;
        lon = stod(s.substr(i + 2, s.size() - i - 3));
        if (s[s.size() - 1] == 'W') lon *= -1;
    }
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

        transform(country.begin(), country.end(), country.begin(), ::toupper);
        transform(city.begin(), city.end(), city.begin(), ::toupper);
        if(airport_cities.find(city) == airport_cities.end()) {
            vector<int> v; v.push_back(i);
            airport_cities.insert({city, v});
        } else {
            airport_cities.at(city).push_back(i);
        }

        if(cities_country.find(city) == cities_country.end()) {
            unordered_set<string> countries = {country};
            cities_country.insert({city, countries});
        } else if(cities_country.find(city) -> second.find(country) == cities_country.find(city) -> second.end()){
            cities_country.at(city).insert(country);
        }

        if (airport_countries.find(country) == airport_countries.end()) {
            vector<int> v; v.push_back(i);
            //transform(country.begin(), country.end(), country.begin(), ::toupper);
            airport_countries.insert({country, v});
        } else {
            //transform(country.begin(), country.end(), country.begin(), ::toupper);
            airport_countries.at(country).push_back(i);
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
    getline(flights_file, line);
    while (getline(flights_file, line)) {
        istringstream ss(line);
        string origin, destination, airline;
        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, airline);

        graph.addEdge(airport_codes[origin], airport_codes[destination], airline);

        if (airport_airlines.find(airline) == airport_airlines.end()) {
            vector<int> v; v.push_back(airport_codes[origin]);
            airport_airlines.insert({airline, v});
        } else {
            airport_airlines.at(airline).push_back(airport_codes[origin]);
        }
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
        cout << "| 6. Pontos de Ariculacao (Nao sabia onde colocar isto, por isso pus aqui, mas é temporario, depois na reuniao colocamos num dos submenus, :))      |" << endl;
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
                case 6:
                    print_articulation_points(); break;
                default:
                    break;
            }
        }
    } while (choice != 0);

    clear();
}

void print_menu1() {
    bool opcao_invalida = false;
    int choice;
    vector<int> src, dest;
    do {
        clear();
        cout << "--------------------------------------------" << endl;
        cout << "|         Simulador de Voos 3000           |" << endl;
        cout << "|            Rotas mais curtas             |" << endl;
        cout << "| Selecione a origem do voo:               |" << endl;
        cout << "| 1. Aeroporto                             |" << endl;
        cout << "| 2. Cidade                                |" << endl;
        cout << "| 3. Ponto mais proximo das Coordenadas    |" << endl;
        cout << "| 4. Todos os pontos a Xkm das Coordenadas |" << endl;
        cout << "| 0. Voltar                                |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        if (choice != 0) {
            switch (choice) {
                case 1: {
                    int src_i = get_airport(true);
                    if(src_i == -1) opcao_invalida = true;
                    else src.push_back(src_i);
                    wait();
                    break;
                }
                case 2: {
                    src = get_city(true);
                    wait();
                    break;
                }

                case 3: {
                    int src_i = get_coordinates(true);
                    if(src_i == -1) opcao_invalida = true;
                    else src.push_back(src_i);
                    wait();
                    break;
                }

                case 4: {
                    src = get_coordinates_km(true);
                    wait();
                    break;
                }

                default:
                    opcao_invalida = true;
                    cout << "Opcao invalida!" << endl;
            }
        }

        if(opcao_invalida) break;

        clear();
        cout << "--------------------------------------------" << endl;
        cout << "|         Simulador de Voos 3000           |" << endl;
        cout << "|            Rotas mais curtas             |" << endl;
        cout << "| Selecione o destino do voo:              |" << endl;
        cout << "| 1. Aeroporto                             |" << endl;
        cout << "| 2. Cidade                                |" << endl;
        cout << "| 3. Ponto mais proximo das Coordenadas    |" << endl;
        cout << "| 4. Todos os pontos a Xkm das Coordenadas |" << endl;
        cout << "| 0. Voltar                                |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        if (choice != 0) {
            switch (choice) {
                case 1: {
                    int dest_i = get_airport(false);
                    if(dest_i == -1) opcao_invalida = true;
                    else dest.push_back(dest_i);
                    wait();
                    break;
                }
                case 2: {
                    dest = get_city(false);
                    wait();
                    break;
                }

                case 3: {
                    int dest_i = get_coordinates(false);
                    if(dest_i == -1) opcao_invalida = true;
                    else dest.push_back(dest_i);
                    wait();
                    break;
                }

                case 4: {
                    dest = get_coordinates_km(false);
                    wait();
                    break;
                }

                default:
                    opcao_invalida = true;
                    cout << "Opcao invalida!" << endl;
            }

            if(!opcao_invalida) {
                print_shortest_paths(src, dest);
                wait();
                break;
            }
        }
    } while (choice != 0 && !opcao_invalida);
}

void print_menu2() {
    bool opcao_invalida = false;
    int choice;
    vector<int> src, dest;
    do {
        clear();
        cout << "--------------------------------------------" << endl;
        cout << "|         Simulador de Voos 3000           |" << endl;
        cout << "|            Rotas mais curtas             |" << endl;
        cout << "| Selecione a origem do voo:               |" << endl;
        cout << "| 1. Aeroporto                             |" << endl;
        cout << "| 2. Cidade                                |" << endl;
        cout << "| 3. Ponto mais proximo das Coordenadas    |" << endl;
        cout << "| 4. Todos os pontos a Xkm das Coordenadas |" << endl;
        cout << "| 0. Voltar                                |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        if (choice == 0) return;
        if (choice != 0) {
            switch (choice) {
                case 1: {
                    int src_i = get_airport(true);
                    if(src_i == -1) opcao_invalida = true;
                    else src.push_back(src_i);
                    wait();
                    break;
                }
                case 2: {
                    src = get_city(true);
                    wait();
                    break;
                }

                case 3: {
                    int src_i = get_coordinates(true);
                    if(src_i == -1) opcao_invalida = true;
                    else src.push_back(src_i);
                    wait();
                    break;
                }

                case 4: {
                    src = get_coordinates_km(true);
                    wait();
                    break;
                }

                default:
                    opcao_invalida = true;
                    cout << "Opcao invalida!" << endl;
            }
        }

        if(opcao_invalida) break;

        clear();
        cout << "--------------------------------------------" << endl;
        cout << "|         Simulador de Voos 3000           |" << endl;
        cout << "|            Rotas mais curtas             |" << endl;
        cout << "| Selecione o destino do voo:              |" << endl;
        cout << "| 1. Aeroporto                             |" << endl;
        cout << "| 2. Cidade                                |" << endl;
        cout << "| 3. Ponto mais proximo das Coordenadas    |" << endl;
        cout << "| 4. Todos os pontos a Xkm das Coordenadas |" << endl;
        cout << "| 0. Voltar                                |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        if (choice == 0) return;
        if (choice != 0) {
            switch (choice) {
                case 1: {
                    int dest_i = get_airport(false);
                    if(dest_i == -1) opcao_invalida = true;
                    else dest.push_back(dest_i);
                    wait();
                    break;
                }
                case 2: {
                    dest = get_city(false);
                    wait();
                    break;
                }

                case 3: {
                    int dest_i = get_coordinates(false);
                    if(dest_i == -1) opcao_invalida = true;
                    else dest.push_back(dest_i);
                    wait();
                    break;
                }

                case 4: {
                    dest = get_coordinates_km(false);
                    wait();
                    break;
                }

                default:
                    opcao_invalida = true;
                    cout << "Opcao invalida!" << endl;
            }

            if(!opcao_invalida) {
                print_shortest_paths_distance(src, dest);
                wait();
                break;
            }
        }
    } while (choice != 0 && !opcao_invalida);
}

void print_shortest_paths_distance(vector<int> src, vector<int> dest) {
    if(src.size() == 0) {
        cout << "Nao existem aeroportos de origem!" << endl;
        return;
    }
    if(dest.size() == 0) {
        cout << "Nao existem aeroportos de destino!" << endl;
        return;
    }

    if(src.size() == 1) {
        cout << "Aeroporto de origem: " << airports.at(src[0]).getName() << endl;
    } else {
        cout << "Aeroportos de origem: " << endl;
        for(int & i : src) {
            cout << "  - " << airports.at(i).getName() << endl;
        }
    }
    cout << endl;
    if(dest.size() == 1) {
        cout << "Aeroporto de destino: " << airports.at(dest[0]).getName() << endl;
    } else {
        cout << "Aeroportos de destino: " << endl;
        for(int & i : dest) {
            cout << "  - " << airports.at(i).getName() << endl;
        }
    }

    cout << endl << "Pretende pesquisar apenas para certas companhias aéreas? (s/n) ";
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
        list_shortest_paths_with_distance(src, dest, airlines_to_consider);
    } else {
        list_shortest_paths_with_distance(src, dest);
    }
}

void list_shortest_paths_with_distance(vector<int> src, vector<int> dest) {
    list<li> path = graph.least_flights_with_distance(src, dest);
    set<string> o; set<string> d; string src_string; string dst_string;
    if(src.size() == 1)
        src_string = airports.at(src[0]).getName();
    else {
        for (auto &s: src)
            o.insert(airports.at(s).getCity());
        src_string = set_to_string(o);
    }
    if(dest.size() == 1)
        dst_string = airports.at(dest[0]).getName();
    else {
        for (auto &s: dest)
            d.insert(airports.at(s).getCity());
        dst_string = set_to_string(d);
    }

    cout << endl << "Trajetos mais curtos de " << src_string << " para " << dst_string << endl << endl;

    if (path.empty())
        cout << "Não há trajetos disponíveis para os critérios especificados." << endl;

    for (auto &l : path) {
        for (auto &k: l) {
            if (k == l.front())
                cout << "(" <<k << " Km) ";
            else if (k == l.back())
                cout << airports.at(k).getName() << endl;
            else
                cout << airports.at(k).getName() << " -> ";
        }
        cout << endl;
    }
}

void list_shortest_paths_with_distance(vector<int> src, vector<int> dest, const set<string>& airlines_to_consider) {
    list<li> path = graph.least_flights_with_distance(src, dest, airlines_to_consider);

    cout << "Companhias aéreas consideradas: ";
    for (const auto& a : airlines_to_consider) cout << a << " ";
    cout << endl;

    cout << endl << "Trajetos mais curtos de " << airports.at(src.front()).getCity() << " para " << airports.at(dest.front()).getCity() << endl;

    if (path.empty())
        cout << "Não há trajetos disponíveis para os critérios especificados." << endl;

    for (auto &l : path) {
        for (auto &k: l) {
            if (k == l.front())
                cout << "(" <<k << " Km) ";
            else if (k == l.back())
                cout << airports.at(k).getName() << endl;
            else
                cout << airports.at(k).getName() << " -> ";
        }
        cout << endl;
    }
}

void print_articulation_points() {
    cout << endl << "Pretende pesquisar apenas para certas companhias aéreas? (s/n) ";
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
        set<int> ap = graph.getArticulationPoints(airlines_to_consider);
        if(ap.empty()) cout << "Sem pontos de articulacao" << endl;
        else {
            cout << "Pontos de Articulacao: " << endl;
            for(auto &a : ap) {
                cout << airports.at(a).getCode() << '-' << airports.at(a).getName() << endl;
            }
        }
    } else {
        set<int> ap = graph.getArticulationPoints();
        if(ap.empty()) cout << "Sem pontos de articulacao" << endl;
        else {
            cout << "Pontos de Articulacao: " << endl;
            for(auto &a : ap) {
                cout << airports.at(a).getCode() << '-' << airports.at(a).getName() << '-' << a << endl;
            }
        }
    }
    wait();
}

void print_shortest_paths(const vector<int>& src, const vector<int>& dest) {
    if(src.size() == 0) {
        cout << "Nao existem aeroportos de origem!" << endl;
        return;
    }
    if(dest.size() == 0) {
        cout << "Nao existem aeroportos de destino!" << endl;
        return;
    }

    if(src.size() == 1) {
        cout << "Aeroporto de origem: " << airports.at(src[0]).getName() << endl;
    } else {
        cout << "Aeroportos de origem: " << endl;
        for(int i = 0; i < src.size(); i++) {
            cout << "  - " << airports.at(src[i]).getName() << endl;
        }
    }
    cout << endl;
    if(dest.size() == 1) {
        cout << "Aeroporto de destino: " << airports.at(dest[0]).getName() << endl;
    } else {
        cout << "Aeroportos de destino: " << endl;
        for(int i = 0; i < dest.size(); i++) {
            cout << "  - " << airports.at(dest[i]).getName() << endl;
        }
    }

    cout << endl << "Pretende pesquisar apenas para certas companhias aéreas? (s/n) ";
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
        list_shortest_paths(src, dest, airlines_to_consider);
    } else {
        list_shortest_paths(src, dest);
    }
}

int get_airport(bool is_origin) {
    string src;
    string s;
    if(is_origin) s = "origem";
    else s = "destino";
    cout << "Escolha o aeroporto de " << s << ": "; cin >> src;
    transform(src.begin(), src.end(), src.begin(), ::toupper);

    if (airport_codes.find(src) == airport_codes.end()) {
        cout << "Aeroporto nao encontrado!" << endl; wait();
        return -1;
    }
    return airport_codes[src];
}

vector<int> get_city(bool is_origin) {
    string src;
    string s;
    if(is_origin) s = "origem";
    else s = "destino";
    cout << "Escolha a cidade de " << s << ": ";
    getline(cin >> ws, src);
    transform(src.begin(), src.end(), src.begin(), ::toupper);
    if (airport_cities.find(src) == airport_cities.end()) {
        cout << "Cidade nao encontrada!" << endl;
        return {};
    }

    vector<int> airport_list = airport_cities[src];

    if(cities_country.find(src) -> second.size() > 1) {
        cout << "Escolha o pais: ";
        string country;
        getline(cin >> ws, country);
        transform(country.begin(), country.end(), country.begin(), ::toupper);
        for(auto it = airport_list.begin(); it != airport_list.end(); it++) {
            string c = airports.at(*it).getCountry();
            transform(c.begin(), c.end(), c.begin(), ::toupper);
            if(c != country) {
                airport_list.erase(it);
                it--;
            }
        }
    }

    return airport_list;
}

int get_coordinates(bool is_origin) {
    string src;
    string s;
    if(is_origin) s = "origem";
    else s = "destino";
    cout << "Escolha as coordenadas de " << s << " (e.g. '16.23N 42.13W' or '16.23,-42.13'): ";
    getline(cin >> ws, src);
    pair <double, double> coords = string_to_coords(src);
    pair <double, double> src_coords = tree.nearest(coords);

    if (src_coords.first == 100 &&
        src_coords.second == 200) {
        cout << "Erro ao introduzir as coordenadas!" << endl;
        return {};
    }
    return airport_coords[src_coords];
}

vector<int> get_coordinates_km(bool is_origin) {
    string src;
    string s;
    if(is_origin) s = "origem";
    else s = "destino";
    cout << "Escolha as coordenadas de " << s << " (e.g. '16.23N 42.13W' or '16.23,-42.13'): ";
    getline(cin >> ws, src);
    pair <double, double> coords = string_to_coords(src);
    if (coords.first == 100 &&
        coords.second == 200) {
        cout << "Erro ao introduzir as coordenadas!" << endl;
        return {};
    }
    cout << endl << "Escolha o raio de pesquisa (em km): ";
    double radius_src;
    cin >> radius_src;

    vector <pair<double, double>> src_pairs = tree.in_radius(coords, radius_src);
    if(src_pairs.empty()) {
        cout << "Nao foram encontrados aeroportos na zona de " << s << "!" << endl;
        return {};
    }

    vector <int> airports_in_radius_src;for(int i = 0; i < src_pairs.size(); i++) {
        airports_in_radius_src.push_back(airport_coords[src_pairs[i]]);
    }

    return airports_in_radius_src;
}

void print_menu3() {
    int choice;
    do {
        clear();
        cout << "--------------------------------------------" << endl;
        cout << "|         Simulador de Voos 3000           |" << endl;
        cout << "|          Estatísticas da Rede            |" << endl;
        cout << "| Selecione o modo:                        |" << endl;
        cout << "| 1. Estatísticas da rede global           |" << endl;
        cout << "| 2. Estatísticas de um país               |" << endl;
        cout << "| 3. Estatísticas de uma companhia         |" << endl;
        cout << "| 0. Voltar                                |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Escolha: ";
        cin >> choice;
        switch(choice) {
            case 1:
                print_global_stats();
                break;
            case 2:
                print_country_stats();
                break;
            case 3:
                print_airline_stats();
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
                wait();
        }
    } while(choice != 0);
}

void print_airline_stats() {
    string airline;
    cout << "Escolha a companhia aérea: ";
    getline(cin >> ws, airline);
    transform(airline.begin(), airline.end(), airline.begin(), ::toupper);

    if (airline_codes.find(airline) == airline_codes.end()) {
        cout << "Companhia aérea não encontrada!" << endl;
        wait();
        return;
    }

    vector<int> airports_nodes = airport_airlines[airline];
    Graph g = Graph((int) airports.size() + 1, true);

    for (int &node : airports_nodes) {
        for (auto const &edge : graph.nodes[node].adj) {
            if (edge.airlines.find(airline) != edge.airlines.end()) {
                g.addEdge(node, edge.dest, airline);
            }
        }
    }

    int num_airports = (int) airports_nodes.size();
    int num_flights = g.getNumEdges();
    int num_companies = g.getCompanies();
    int diameter = g.getDiameter();
    // random number between 3 and 5
    int n = rand() % 3 + 3;
    vector<pii> top_airports = g.getTopAirports(n);

    cout << "A rede de " << airline << " tem um total de " << num_airports << " aeroportos," << endl;
    cout << "com um total de " << num_flights << " voos." << endl;

    cout << "O diâmetro da rede é " << diameter << "." << endl;
    cout << "Os " << n << " aeroportos com mais voos são:" << endl;
    for (const auto & top_airport : top_airports) {
        cout << "  - " << airports.at(top_airport.first).getName() << ", " << airports.at(top_airport.first).getCountry() << " (" << top_airport.second << " voos)" << endl;
    }
    wait();
}

void print_country_stats() {
    string country;
    cout << "Escolha o país: ";
    getline(cin >> ws, country);
    transform(country.begin(), country.end(), country.begin(), ::toupper);

    if (airport_countries.find(country) == airport_countries.end()) {
        cout << "Pais nao encontrado!" << endl;
        wait();
        return;
    }
    vector <int> airports_nodes = airport_countries[country];
    Graph country_graph = Graph((int) airports.size() + 1, true);

    for (int &node : airports_nodes) {
        for (auto const &edge : graph.nodes[node].adj) {
            int w = edge.dest;
            string new_country = airports.at(w).getCountry();
            transform(new_country.begin(), new_country.end(), new_country.begin(), ::toupper);
            if (new_country == country) {
                for (const string& airline : edge.airlines) {
                    country_graph.addEdge(node, w, airline);
                }
            }
        }
    }


    int num_airports = (int) airports_nodes.size();
    int num_flights = country_graph.getNumEdges();
    int num_companies = country_graph.getCompanies();
    int diameter = country_graph.getDiameter();
    // random number between 3 and 5
    int n = rand() % 3 + 3;
    vector<pii> top_airports = country_graph.getTopAirports(n);

    cout << "A rede de " << country << " tem um total de " << num_airports << " aeroportos," << endl;
    cout << "com um total de " << num_flights << " voos," << endl;
    cout << "e " << num_companies << " companhias aéreas." << endl;

    cout << "O diâmetro da rede é " << diameter << "." << endl;
    cout << "Os " << n << " aeroportos com mais voos são:" << endl;
    for (const auto & top_airport : top_airports) {
        cout << "  - " << airports.at(top_airport.first).getName() << ", " << airports.at(top_airport.first).getCountry() << " (" << top_airport.second << " voos)" << endl;
    }
    wait();
}

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


void print_global_stats() {
    int num_airports = (int) graph.getNodes().size();
    int num_flights = graph.getNumEdges();
    int num_companies = graph.getCompanies();
    int diameter = graph.getDiameter();
    // random number between 3 and 5
    int n = rand() % 3 + 3;
    vector<pii> top_airports = graph.getTopAirports(n);

    cout << "A rede global tem um total de " << num_airports << " aeroportos," << endl;
    cout << "com um total de " << num_flights << " voos," << endl;
    cout << "e " << num_companies << " companhias aéreas." << endl;

    cout << "O diâmetro da rede é " << diameter << "." << endl;
    cout << "Os " << n << " aeroportos com mais voos são:" << endl;
    for (const auto & top_airport : top_airports) {
        cout << "  - " << airports.at(top_airport.first).getName() << ", " << airports.at(top_airport.first).getCountry() << " (" << top_airport.second << " voos)" << endl;
    }
    wait();
}
