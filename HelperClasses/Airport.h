#ifndef PROJETO2_AIRPORT_H
#define PROJETO2_AIRPORT_H

#include <string>
using namespace std;

/**
 * @brief Classe que representa um aeroporto
 *
 * Esta classe representa um aeroporto, com o seu nome, codigo, cidade, pais, latitude e longitude
 */
class Airport {
private:
    /// Codigo do aeroporto
    string Code;
    /// Nome do aeroporto
    string Name;
    /// Cidade do aeroporto
    string City;
    /// Pais do aeroporto
    string Country;
    /// Latitude do aeroporto
    double Latitude;
    /// Longitude do aeroporto
    double Longitude;

public:
    /**
     * @brief Retorna o codigo do aeroporto
     *
     * @return O codigo do aeroporto
     */
    string getCode() const;

    /**
     * @brief Retorna o nome do aeroporto
     *
     * @return O nome do aeroporto
     */
    string getName() const;

    /**
     * @brief Retorna a cidade em que se encontra  aeroporto
     *
     * @return A cidade em que se encontra  aeroporto
     */
    string getCity() const;

    /**
     * @brief Retorna o pais em que se encontra aeroporto
     *
     * @return O pais em que se encontra aeroporto
     */
    string getCountry() const;

    /**
     * @brief Retorna a latitude do aeroporto
     *
     * @return A latitude do aeroporto
     */
    double getLatitude() const;

    /**
     * @brief Retorna a longitude do aeroporto
     *
     * @return A longitude do aeroporto
     */
    double getLongitude() const;

    /**
     * @brief Construtor da classe Airport
     *
     * @param code Codigo do aeroporto
     * @param name Nome do aeroporto
     * @param city Cidade do aeroporto
     * @param country Pais do aeroporto
     * @param latitude Latitude do aeroporto
     * @param longitude Longitude do aeroporto
     */
    Airport(string code, string name, string city, string country, double latitude, double longitude);
};


#endif //PROJETO2_AIRPORT_H
