#ifndef PROJETO2_FLIGHT_H
#define PROJETO2_FLIGHT_H

#include "Airport.h"

class Flight {
private:
    Airport& source;
    Airport& target;
    string airline;

public:
    Flight(Airport& source, Airport& target, string airline);
    Airport& getSource() const;
    Airport& getTarget() const;
    string getAirline() const;
};


#endif //PROJETO2_FLIGHT_H
