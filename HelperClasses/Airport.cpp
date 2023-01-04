#include "Airport.h"

string Airport::getCode() const {
    return Code;
}
string Airport::getName() const {
    return Name;
}
string Airport::getCity() const {
    return City;
}
string Airport::getCountry() const {
    return Country;
}
double Airport::getLatitude() const {
    return Latitude;
}
double Airport::getLongitude() const {
    return Longitude;
}
Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) :
    Code(code), Name(name), City(city), Country(country), Latitude(latitude), Longitude(longitude) {}
