#ifndef AED2223_P12_COORD2DTREE_H
#define AED2223_P12_COORD2DTREE_H

#include <utility>
#include <list>
#include <set>
#include <iostream>
#include "../HelperClasses/Rect.h"
#include "../HelperClasses/Haversine.h"
using namespace std;

/**
 * @brief Struct que representa um nó da árvore apresentada a seguir
 *
 * Cada nó da árvore contem um par de coordenadas (latitude, longitude) e dois apontadores para os seus filhos(esquerdo e direito).
 */
struct Node {
    pair<double, double> data;
    Node *left;
    Node *right;
};

/**
 * @brief Classe que representa uma árvore de coordenadas 2D
 *
 * Esta classe representa uma árvore de coordenadas 2D, que permite:
 *  - a inserção das coordenadas de um ponto
 *  - procurar o ponto mais próximo de outro dadas as suas coordenadas
 *  - procurar todos os pontos dentro de um raio dado
 *  - procurar os N pontos mais próximos de um dado ponto
 *
 *  Esta implementação tem como base a implementação dos slides do professor Carl Kingsford, professor da Universidade Carnegie Mellon (https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf).
 *  A implementação original usa um array para represar as coordenadas e apenas foi desenhada para funcionar no plano.
 *  A nossa implementação usa um par de double para representar as coordenadas e foi ajustada para funcionar numa superficie esferica como a superficie da Terra.
 *  Nesta classe foi utilizada a função Haversine para calcular a distância entre dois pontos e a classe Rect para representar um retângulo.
 *
 * Cada nível tem uma dimensão associada (neste caso longitude e latitude)
 * Ao percorrer árvore devemos ir alternando as dimensões.
 * Cada nó tem umas coordenadas associadas (lat, lon)
 *
 */
class Coord2dTree {
private:
    /// Apontador para a raiz da árvore
    Node* root;

    /// Número de nós da árvore
    int size;
    
    /**
     * @brief Método auxiliar para inserir um ponto na árvore
     *

     * Método auxiliar para inserir um ponto na árvore.
     * Esta método é recursivo e é chamada pela método publico insert().
     * Se pretendermos inserir o ponto x precisamos de encontrar o nó onde este estaria
     * Para o encontrar, apenas precisamos comparar as coordenadas da dimensão associada ao nó atual, e dependendo disso procuramos na respetiva sub-árvore.
     * Se encontrarmos um ponto com coordenadas iguais a x, este ponto não é inserido.
     * Se chegarmos a um nullptr, inserimos aí um nó folha com as coordenadas de x.
     *
     * Complexidade Temporal: 
     *  - Em média: O(log n)
     *  - No pior caso: O(n)
     * 
     * @param x Par de coordenadas do ponto a inserir
     * @param t Apontador para o nó atual
     * @param cd Coordenada a utilizar para comparar o ponto a inserir com o nó atual
     * @return Apontador para o nó atual atualizado
     */
    Node* insert(pair<double, double> x, Node* t, int cd);
    
    /**
     * @brief Método auxiliar para procurar o ponto mais próximo de outro dado as suas coordenadas
     *
     * Método auxiliar para procurar o ponto mais próximo de outro dadas as suas coordenadas.
     * Este método é recursivo e é chamada pela método publico nearest().
     * Cada ponto tem um retangulo associado a si, onde todos os filhos desse ponto se encontram.
     * Dado que x é o ponto passado por argumento, b o ponto até agora, mais perto, t o nó atual, e BB o retangulo correspondente ao nó atual,
     * se a distancia(x, b) < distancia(x, BB), significa que nenhum ponto dentro do retangulo BB poderá estar mais proximo de x do que b, ou seja,
     * nenhum filho de t poderá estar mais proximo de x do que o b, logo é desnecessario procurar nesta sub-árvore.
     * Caso isto não aconteça, o codigo prossegue.
     * Se o ponto associado a t for mais próximo de x do que b, atualiza o ponto mais próximo.
     * Recursivamente procura o ponto da árvore mais proximo de x, primeiro na sub-árvore que conteria se o tivessemos a inserir, a seguir na outra sub-árvore,
     * porque o ponto ainda pode estar na outra sub-árvore.
     *
     * Complexidade Temporal: 
     *  - Em média: O(log n)
     *  - No pior caso: O(n)
     * 
     * @param Q Par de coordenadas do ponto a procurar
     * @param t Apontador para o nó atual
     * @param cd Coordenada a utilizar para comparar o ponto a procurar com o nó atual
     * @param BB Retangulo associado ao nó atual
     * @param best Referencia para as coordenadas do ponto mais proximo de x encontrado até ao momento
     * @param best_dist Referencia para a distancia entre x e o ponto mais proximo de x encontrado até ao momento
     */
    void nearest(pair<double, double> Q, Node* t, int cd, Rect BB, pair<double, double> &best, double &best_dist);

    /**
     * @brief Método auxiliar para procurar todos os pontos dentro de um raio dado
     *
     * Método auxiliar para procurar todos os pontos cuja distancia a outro é menor que um certo raio, dadas as suas coordenadas.
     * Este método é recursivo e é chamada pela método publico in_radius().
     * Cada ponto tem um retangulo associado a si, onde todos os filhos desse ponto se encontram.
     * Dado que x é o ponto passado por argumento, t o nó atual, e BB o retangulo correspondente ao nó atual,
     * se a raio de pesquisa < distancia(x, BB), significa que nenhum ponto dentro do retangulo BB poderá estar ter uma distancia a x menor que o raio, ou seja,
     * nenhum filho de t poderá estar dentro do raio que pretendemos, logo é desnecessario procurar nesta sub-árvore.
     * Caso isto não aconteça, o codigo prossegue.
     * Se o ponto associado a t estiver a uma distancia menor do que o raio de pesquisa, adiciona o ponto a lista de pontos encontrados.
     * Recursivamente procura-se tanto na sub-árvore da direta como na sub-árvore da esquerda os pontos que estejam dentro do raio de pesquisa.
     *
     * Complexidade Temporal:
     *  - Em média: O(log n)
     *  - No pior caso e se o raio > 1500km: O(n)
     *
     * @param x Par de coordenadas do ponto a procurar
     * @param t Apontador para o nó atual
     * @param cd Coordenada a utilizar para comparar o ponto a procurar com o nó atual
     * @param BB Retangulo associado ao nó atual
     * @param best Referencia para o vetor de pontos dentro do raio
     * @param radius Raio de procura
     */
    void in_radius(pair<double, double> Q, Node* t, int cd, Rect BB, vector<pair<double, double>> &best, double radius);

    /**
     * @brief Método auxiliar para procurar os N pontos mais próximos de outro dado as suas coordenadas
     *
     * Método auxiliar para procurar os N pontos mais próximos de outro dadas as suas coordenadas.
     * Este método é recursivo e é chamado pela método publico nearestN().
     * Cada ponto tem um retangulo associado a si, onde todos os filhos desse ponto se encontram.
     * Neste método é passada por argumento uma fila de prioridade, onde são guardados os N pontos mais próximos de x, ordenados por distancia ao ponto passado por argumento.
     * Dado que x é o ponto passado por argumento, h a fila de prioridade, mais perto, t o nó atual, e BB o retangulo correspondente ao nó atual,
     * se h tem menos de N elementos, o ponto associado a t e a sua distancia a x é adicionado a h.
     * Caso contrario e se a distancia(x, maximo de h) < distancia(x, BB), significa que nenhum ponto dentro do retangulo BB poderá estar mais proximo de x do que os pontos em h, ou seja,
     * nenhum filho de t poderá estar mais proximo de x do que os pontos em h, logo é desnecessario procurar nesta sub-árvore.
     * Caso isto não aconteça, o codigo prossegue.
     * Se o ponto associado a t for mais próximo de x do que o maximo de h, esse ponto e a distancia a ele são inseridos na fila de prioridade e o maximo de h é removido.
     * Recursivamente procura o ponto da árvore mais proximo de x, primeiro na sub-árvore que conteria se o tivessemos a inserir, a seguir na outra sub-árvore,
     * porque o ponto ainda pode estar na outra sub-árvore.
     *
     * Complexidade Temporal:
     *  - Em média: O((log n + N) * log N)
     *  - No pior caso: O(n * log N)
     *
     *  Onde N é o numero de pontos a procurar e n é o numero total de pontos na árvore
     *
     * @param x Par de coordenadas do ponto a procurar
     * @param t Apontador para o nó atual
     * @param cd Coordenada a utilizar para comparar o ponto a procurar com o nó atual
     * @param BB Retangulo associado ao nó atual
     * @param bestN Referencia para a fila de prioridade com os N pontos mais proximos de x até ao momento
     * @param n Número de pontos a procurar
     */
    void nearestN(pair<double, double> Q, Node* t, int cd, Rect BB, priority_queue<pair<double, pair<double, double>>>& bestN, int n);
public:
    /**
     * @brief Construtor da classe
     *
     * Construtor da classe.
     * Inicializa a árvore vazia, com root = nullptr.
     */
    Coord2dTree();

    /**
     * @brief Insere um ponto na árvore
     *
     * Insere um ponto na árvore através do método privado insert() e retorna true se o ponto foi inserido com sucesso, false caso contrário.
     *
     * Complexidade Temporal:
     *  - Em média: O(log n)
     *  - No pior caso: O(n)
     *
     * @param lat Latitude do ponto a inserir
     * @param lon Longitude do ponto a inserir
     * @return true se o ponto foi inserido com sucesso, false caso contrário
     */
    bool insert(double lat, double lon);

    /**
     * @brief Procura o ponto mais próximo de outro dado as suas coordenadas
     *
     * Procura o ponto mais próximo de outro dado as suas coordenadas.
     * Caso a árvore esteja vazia, retorna um par de coordenadas (-1, -1).
     * Para isso, chama o método privado nearest().
     * Caso a distancia entre o ponto mais proximo e o ponto p seja inferior à distancia entre p e o meridiano de 180º,
     * volta a correr o método nearest(), mas com a longitude equivalente à do ponto p mas como se estivesse no outro lado do meridiano,
     * por exemplo, se o ponto p tem longitude -173º, o ponto p' tem longitude 187º.
     *
     * Complexidade Temporal:
     *  - Em média: O(log n)
     *  - No pior caso: O(n)
     *
     * @param p Par de coordenadas do ponto a procurar
     * @return Par de coordenadas do ponto mais proximo de (lat, lon)
     */
    pair<double, double> nearest(pair<double, double> p);

    /**
     * @brief Procura os pontos dentro de um raio dado as suas coordenadas
     *
     * Procura os pontos dentro de um raio dado as suas coordenadas.
     * Caso a árvore esteja vazia, retorna um vetor vazio.
     * Para isso, chama o método privado in_radius().
     * Caso o raio seja inferior à distancia entre p e o meridiano de 180º, volta a correr o método in_radius(),
     * mas com a longitude equivalente à do ponto p mas como se estivesse no outro lado do meridiano,
     * por exemplo, se o ponto p tem longitude -173º, o ponto p' tem longitude 187º.
     *
     * Complexidade Temporal:
     *  - Em média: O(log n)
     *  - No pior caso e se o raio > 1500km: O(n)
     *
     * @param p Par de coordenadas do ponto a procurar
     * @param radius Raio de procura
     * @return Vetor de pontos dentro do raio
     */
    vector<pair<double, double>> in_radius(pair<double, double> p, double radius);

    /**
     * @brief Procura os N pontos mais próximos de um certo ponto de um dado as suas coordenadas
     *
     * Procura os N pontos mais próximos de um dado as suas coordenadas.
     * Caso a árvore esteja vazia ou o numero de pontos pedidos for 0, retorna um vetor vazio.
     * Para isso, chama o método privado nearestN().
     * Caso a distancia entre o maximo da fila de prioridade e o ponto p seja inferior à distancia entre p e o meridiano de 180º,
     * volta a correr o método nearestN(), mas com a longitude equivalente à do ponto p, mas como se estivesse no outro lado do meridiano,
     * por exemplo, se o ponto p tem longitude -173º, o ponto p' tem longitude 187º. Depois junta as duas filas de prioridade e mantem apenas
     * os N pontos mais proximos.
     *
     * Complexidade Temporal:
     *  - Em média: O((log n + N) * log N)
     *  - No pior caso: O(n * log N)
     *
     *  Onde N é o numero de pontos a procurar e n é o numero total de pontos na árvore
     *
     * @param p Par de coordenadas do ponto a procurar
     * @param n Número de pontos a procurar
     * @return Vetor de pontos mais próximos de p ordenados por ordem crescente de distância
     */
    vector<pair<double, double>> nearestN(pair<double, double> p, int n);
};

#endif
