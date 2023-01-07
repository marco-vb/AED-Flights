#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "../HelperClasses/Airport.h"

using namespace std;
typedef list<int> li;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<int, string> pis;
typedef list<pis> lp;

/**
 * @brief Classe usada para representar um grafo dirigido.
 *
 * Esta classe representa um grafo dirigido (que, neste projeto, representa aeroportos e os voos entre eles)
 * a partir de um vetor de nós (de tamanho n+1, pois o indíce 0 não pertence ao grafo), onde cada nó possui uma lista de adjacências.
 * Os métodos implementados permitem saber várias informações sobre o grafo, como por exemplo o grau de um nó,
 * os menores caminhos entre dois nós (com ou sem distâncias), pontos de articulalção, etc.
 */
class Graph {
public:
    /**
     * @brief Struct que representa uma aresta.
     * Contém o vértice de destino, o peso da aresta e um conjunto de airlines que realizam o voo.
     */
    struct Edge {
        int dest;
        int weight;
        set<string> airlines;
    };

    /**
     * @brief Struct que representa um nó.
     * Contém uma lista de arestas, que são as arestas que saem do nó,
     * um booleano que indica se o nó já foi visitado numa pesquisa
     * e um inteiro que indica a distância do nó à origem da pesquisa.
     */
    struct Node {
        list<Edge> adj;
        bool visited;
        int distance;
    };

    /// Número de nós do grafo.
    int n;

    /// Vetor de nós do grafo.
    vector<Node> nodes;

    /**
     * @brief Construtor default classe Graph.
     * Cria um grafo com 0 nós.
     */
    Graph();

    /**
     * @brief Construtor classe Graph.
     * Cria um grafo com n nós.
     * @param n Número de nós do grafo.
     */
    explicit Graph(int nodes);

    /**
     * @brief Adiciona uma aresta ao grafo.
     * @param src Nó de origem da aresta.
     * @param dest Nó de destino da aresta.
     * @param weight Peso da aresta.
     * @param airline Airline que realiza o voo.
     */
    void addEdge(int src, int dest, string airline, int weight = 1);

    /**
     * @brief Retorna o grau de um nó.
     * Complexidade temporal: O(1)
     * @param i Nó do qual se quer saber o grau.
     * @return Grau do nó.
     */
    int getOutDegree(int i);

    /**
     * @brief Retorna o número de companhias aéreas diferentes que voam a partir de um nó.
     * Sendo E o número de arestas que saem do nó e Airlines o tamanho do set de airlines dessa aresta, temos:
     * Complexidade temporal: O(|E|*|Airlines|)
     * @param i Nó do qual se quer saber o número de companhias aéreas.
     * @return Número de companhias aéreas.
     */
    int getAirlinesNumber(int i);

    /**
     * @brief Retorna o número de destinos diferentes alcançáveis a partir de um nó.
     * Sendo E o número de arestas que saem do nó e Airlines o tamanho do set de airlines dessa aresta, temos:
     * Complexidade temporal: O(|E|*|Airlines|)
     * @param i Nó de destino.
     * @return Número de destinos diferentes.
     */
    int getDestinationsNumber(int i);

    /**
     * @brief Retorna o número de destinos em países diferentes alcançáveis a partir de um nó.
     * Sendo E o número de arestas que saem do nó e Airlines o tamanho do set de airlines dessa aresta, temos:
     * Complexidade temporal: O(|E|*|Airlines|)
     * @param i Nó de destino.
     * @return Número de destinos com países diferentes.
     */
    int getDestinationsCountries(int i, unordered_map<int, Airport> &airports);

    /**
     * @brief Retorna o número de arestas do grafo.
     * Complexidade temporal: O(|V|)
     * @return Número de arestas do grafo.
     */
    int getNumEdges();

    /**
     * @brief Retorna o número de companhias aéreas.
     * Complexidade temporal: O(|V|+|E|*|Airlines|)
     * @return Número de companhias aéreas.
     */
    int getCompanies();

    /**
     * @brief Retorna o diâmetro do grafo.
     * Para obter o diametro do grafo, é necessário calcular o menor caminho entre todos os pares de nós.
     * Para isso é necesário um BFS para cada nó.
     * É o método mais custoso da classe, com complexidade O(|V|*(|V|+|E|)).
     */
    int getDiameter();

    /**
     * @brief Retorna os destinos alcançáveis a partir de um nó com r voos ou menos.
     * É utilizado um simples BFS, adicionando à fila todos os nós com distância <= r.
     * Complexidade temporal: O(|V|+|E|)
     * @param src
     * @param r
     * @return set<int> com os destinos alcançáveis.
     */
    set<int> getDestinations(int src, int r);

    /**
     * @brief Retorna o vetor de nós do grafo.
     * @return vector<Node> com os nós do grafo.
     */
    vector<Node> getNodes() const;

    /**
     * @brief Função usada para determinar os i aeroportos com mais voos de uma rede.
     *
     * Esta função percorre cada nó (aeroporto) da rede e determina o número de voos que saem desse aeroporto,
     * com auxílio da função getDestinationNumber(). Guarda todos os resultados num vetor e
     * ordena por ordem decrescente de voos e retorna apenas os i primeiros.
     *
     * A complexidade temporal é portanto: O(|V|*|E|*|Airlines|), considerando que |E|*|Airlines| > log|V|, devido à ordenação.
     *
     * @param i Número de aeroportos a retornar.
     * @return Vetor de tamanho i com os pares aeroporto-voos que têm maior número de voos.
     */
    vector<pii> getTopAirports(int i);

    /**
     * @brief Função usada para obter os pontos de articulação da rede (é apenas um wrapper).
     *
     * Esta função utiliza apenas um DFS para determinar os pontos de articulação da rede.
     * Complexidade temporal: O(|V|+|E|)
     * @return set<int> com os pontos de articulação.
     */
    set<int> getArticulationPoints();

    /**
     * @brief Função usada para obter os pontos de articulação da rede (é apenas um wrapper), considerando apenas algumas companhias aéreas.
     *
     * Esta função utiliza apenas um DFS para determinar os pontos de articulação da rede.
     * Mas para cada chamada do DFS também é feita uma interseção com o set de companhias aéreas da aresta.
     * Logo a complexidade temporal é: O(|V|+|E|*|Airlines|)
     * @param airlines_to_consider Companhias aéreas a considerar.
     * @return set<int> com os pontos de articulação.
     */
    set<int> getArticulationPoints(set<string> &airlines_to_consider);

    /**
     * @brief Retorna os caminhos mais curtos em numero de voos entre os aeroportos de origem e os de destino.
     *
     * Esta função utiliza um BFS para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     *
     * Complexidade temporal: O(|V|+|E|)
     *
     * @param sources
     * @param destination
     * @return list<list<int>> com os caminhos mais curtos (em número de voos).
     */
    list<lp> least_flights(vector<int> sources, vector<int> destination);

    /**
     * @brief Retorna os caminhos mais curtos em numero de voos, considerando apenas algumas companhias aéreas.
     *
     * Esta função utiliza um BFS para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino, considerando apenas
     * as companhias aéreas passadas.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     *
     * Complexidade temporal: O(|V|+|E|*|Airlines|)
     *
     * @param sources
     * @param destination
     * @param airlines_to_consider
     * @return list<list<int>> com os caminhos mais curtos (em número de voos), considerando apenas as companhias aéreas passadas.
     */
    list<lp> least_flights(const vector<int>& sources, const vector<int>& dest, const set<string> &airlines_to_consider);

    /**
     * @brief Retorna os caminhos mais curtos em distância física entre os aeroportos de origem e os de destino.
     *
     * Esta função utiliza o algoritmo de Dijkstra (sem priority queue) para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     *
     * Complexidade temporal: O(|V|+|E|), o mesmo que o BFS.
     *
     * @param sources
     * @param destination
     * @return list<list<int>> com os caminhos mais curtos (em distância).
     */
    list<lp> least_flights_with_distance(const vector<int>& src, const vector<int>& dest);

    /**
     * @brief Retorna os caminhos mais curtos em distância física entre os aeroportos de origem e os de destino, considerando apenas algumas companhias aéreas.
     *
     * Esta função utiliza o algoritmo de Dijkstra (sem priority queue) para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     * São considerados apenas voos feitos pelas companhias aéreas passadas.
     *
     * Complexidade temporal: O(|V|+|E|*|Airlines|)
     *
     * @param sources
     * @param destination
     * @param airlines_to_consider
     * @return list<list<int>> com os caminhos mais curtos (em distância), considerando apenas as companhias aéreas passadas.
     */
    list<lp> least_flights_with_distance(const vector<int>& src, const vector<int>& dest, const set<string>& airlines_to_consider);

    /**
     * @brief Função usada para determinar os pontos de articulação da rede.
     *
     * Esta função utiliza apenas um DFS para determinar os pontos de articulação da rede.
     * Os pontos são guardados num set passado por referência.
     * Complexidade temporal: O(|V|+|E|)
     *
     * @param v
     * @param index
     * @param num
     * @param low
     * @param s
     * @param ap
     * @param first
     */
    void articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, bool first = false);

    /**
     * @brief Função usada para determinar os pontos de articulação da rede de um conjunto de companhias aéreas.
     *
     * Esta função utiliza apenas um DFS para determinar os pontos de articulação da rede de um conjunto de companhias aéreas.
     * Os pontos são guardados num set.
     * Complexidade temporal: O(|V|+|E|*|Airlines|)
     *
     * @param v
     * @param index
     * @param num
     * @param low
     * @param s
     * @param ap
     * @param airlines_to_consider
     * @param first
     *
     * @return set<int> com os pontos de articulação da rede de um conjunto de companhias aéreas.
     */
    set<int> articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, set<string> &airlines_to_consider, bool first = false);
};

#endif
