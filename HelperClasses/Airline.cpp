#include "Airline.h"

Airline::Airline(string code, string name, string callSign, string country) :
    code(code), name(name), callSign(callSign), country(country) {}
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
bool Airline::operator<(const Airline &rhs) const {
    return code < rhs.code;
}
