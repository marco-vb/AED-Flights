#ifndef FLIGHTS_AIRLINE_H
#define FLIGHTS_AIRLINE_H

#include <bits/stdc++.h>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callSign;
    string country;

public:
    Airline(string code, string name, string callsign, string country);

    string getCode() const;

    string getName() const;

    string getCallSign() const;

    string getCountry() const;
};


#endif //FLIGHTS_AIRLINE_H
