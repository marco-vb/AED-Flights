#include "Flight.h"

Flight::Flight(Airport& source, Airport& target, string airline) :
    source(source), target(target), airline(airline) {}

Airport& Flight::getSource() const {
    return source;
}

Airport& Flight::getTarget() const {
    return target;
}

string Flight::getAirline() const {
    return airline;
}
