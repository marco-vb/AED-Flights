#ifndef PROJETO2_AIRPORT_H
#define PROJETO2_AIRPORT_H

#include <string>
using namespace std;

class Airport {
private:
    string Code;
    string Name;
    string City;
    string Country;
    double Latitude;
    double Longitude;

public:
    string getCode() const;
    void setCode(string code);
    string getName() const;
    void setName(string name);
    string getCity() const;
    void setCity(string city);
    string getCountry() const;
    void setCountry(string country);
    double getLatitude() const;
    void setLatitude(double latitude);
    double getLongitude() const;
    void setLongitude(double longitude);
    Airport(string code, string name, string city, string country, double latitude, double longitude);
};


#endif //PROJETO2_AIRPORT_H
