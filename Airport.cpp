#include "Airport.h"

string Airport::getCode() const {
    return Code;
}

void Airport::setCode(string code) {
    Code = code;
}

string Airport::getName() const {
    return Name;
}

void Airport::setName(string name) {
    Name = name;
}

string Airport::getCity() const {
    return City;
}

void Airport::setCity(string city) {
    City = city;
}

string Airport::getCountry() const {
    return Country;
}

void Airport::setCountry(string country) {
    Country = country;
}

double Airport::getLatitude() const {
    return Latitude;
}

void Airport::setLatitude(double latitude) {
    Latitude = latitude;
}

double Airport::getLongitude() const {
    return Longitude;
}

void Airport::setLongitude(double longitude) {
    Longitude = longitude;
}

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) :
    Code(code), Name(name), City(city), Country(country), Latitude(latitude), Longitude(longitude) {}
