#include "Airline.h"

Airline::Airline(string code, string name, string callsign, string country) :
    code(code), name(name), callSign(callsign), country(country) {}

string Airline::getCode() const {
    return code;
}

string Airline::getName() const {
    return name;
}

string Airline::getCallSign() const {
    return callSign;
}

string Airline::getCountry() const {
    return country;
}