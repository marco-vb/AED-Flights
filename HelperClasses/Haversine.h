#ifndef FLIGHTS_HAVERSINE_H
#define FLIGHTS_HAVERSINE_H

#include <cmath>
using namespace std;

/**
 * @brief Função que retorna uma distancia entre dois pontos
 *
 * Esta função retorna uma distancia entre dois pontos, calculada com a formula de Haversine, dadas as suas coordenadas
 *
 * @param lat1 Latitude do primeiro ponto
 * @param lon1 Longitude do primeiro ponto
 * @param lat2 Latitude do segundo ponto
 * @param lon2 Longitude do segundo ponto
 * @return A distancia entre os dois pontos
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

/**
 * @brief Função que retorna uma distancia entre dois pontos
 *
 * Esta função retorna uma distancia entre dois pontos, calculada com a formula de Haversine, dadas as suas coordenadas
 *
 * @param p1 Par de coordenadas do primeiro ponto
 * @param p2 Par de coordenadas do segundo ponto
 * @return A distancia entre os dois pontos
 */
double haversine(pair<double, double> p1, pair<double, double> p2);

#endif //FLIGHTS_HAVERSINE_H
