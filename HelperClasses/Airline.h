#ifndef FLIGHTS_AIRLINE_H
#define FLIGHTS_AIRLINE_H

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Classe que representa uma companhia aerea
 *
 * Esta classe representa uma companhia aerea, com o seu nome, codigo, call sign e o seu pais de origem
 */
class Airline {
private:

    /// Nome da companhia aerea
    string code;

    /// Codigo da companhia aerea
    string name;

    /// Call sign da companhia aerea
    string callSign;

    /// Pais de origem da companhia aerea
    string country;

public:

    /**
     * @brief Construtor da classe Airline
     *
     * @param code Codigo da companhia aerea
     * @param name Nome da companhia aerea
     * @param callSign Call sign da companhia aerea
     * @param country Pais de origem da companhia aerea
     */
    Airline(string code, string name, string callSign, string country);

    /**
     * @brief Retorna o codigo da companhia aerea
     *
     * @return O codigo da companhia aerea
     */
    string getCode() const;

    /**
     * @brief Retorna o nome da companhia aerea
     *
     * @return O nome da companhia aerea
     */
    string getName() const;

    /**
     * @brief Retorna o call sign da companhia aerea
     *
     * @return O call sign da companhia aerea
     */
    string getCallSign() const;

    /**
     * @brief Retorna o pais de origem da companhia aerea
     *
     * @return O pais de origem da companhia aerea
     */
    string getCountry() const;

    /**
     * @brief Operador de menor
     *
     * @param rhs Companhia aerea a comparar
     * @return True se as companhias aereas se codigo for menor que o codigo da companhia aerea rhs
     */
    bool operator<(const Airline &rhs) const;
};


#endif //FLIGHTS_AIRLINE_H
