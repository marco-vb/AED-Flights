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
    string getName() const;
    string getCity() const;
    string getCountry() const;
    double getLatitude() const;
    double getLongitude() const;
    Airport(string code, string name, string city, string country, double latitude, double longitude);
};


#endif //PROJETO2_AIRPORT_H
