#ifndef FLIGHTS_RECT_H
#define FLIGHTS_RECT_H

#include <utility>
#include <queue>
#include <functional>
#include "Haversine.h"
using namespace std;

/**
 * @brief Classe que representa um retangulo entre duas latitudes e duas longitudes
 *
 */
class Rect {
public:
    /// Latitude inferior
    double lat1;
    /// Latitude superior
    double lat2;
    /// Longitude inferior
    double lon1;
    /// Longitude superior
    double lon2;

    /**
     * @brief Construtor da classe
     *
     * @param lat1 Latitude inferior
     * @param lat2 Latitude superior
     * @param lon1 Longitude inferior
     * @param lon2 Longitude superior
     */
    Rect(double lat1, double lat2, double lon1, double lon2);

    /**
     * @brief Retorna o retangulo resultante de cortar o retangulo atual pela esquerda
     *
     * Retorna o retangulo resultante de cortar o retangulo atual pela esquerda, no eixo cd, no ponto data
     *
     * @param cd Coordenada a cortar (0 - latitude, 1 - longitude)
     * @param data Valor da coordenada a cortar
     * @return O retangulo resultante de cortar o retangulo atual pela esquerda
     */
    Rect trimLeft(int cd, double data) const;

    /**
     * @brief Retorna o retangulo resultante de cortar o retangulo atual pela direita
     *
     * Retorna o retangulo resultante de cortar o retangulo atual pela direita, no eixo cd, no ponto data
     *
     * @param cd Coordenada a cortar (0 - latitude, 1 - longitude)
     * @param data Valor da coordenada a cortar
     * @return O retangulo resultante de cortar o retangulo atual pela direita
     */
    Rect trimRight(int cd, double data) const;
};


/**
 * @brief Função que retorna dois retangulos a distancia do ponto Q do retangulo BB
 *
 * @param Q Ponto a ser considerado
 * @param BB Retangulo a ser considerado
 * @return Distancia entre o ponto Q e o ponto do retangulo BB mais proximo de Q
 */
double distance(pair<double, double> Q, Rect BB);

#endif //FLIGHTS_RECT_H
