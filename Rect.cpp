#include "Rect.h"

Rect::Rect(double lat1, double lat2, double lon1, double lon2) {
    this->lat1 = min(lat1, lat2);
    this->lat2 = max(lat1, lat2);
    if (false){//lon1 > 90 && lon2 < -90){
        this->lon1 = lon1;
        this->lon2 = lon2;
    } else if(false){//lon2 > 90 && lon1 < -90){
        this->lon1 = lon2;
        this->lon2 = lon1;
    } else {
        this->lon1 = min(lon1, lon2);
        this->lon2 = max(lon1, lon2);
    }
}

Rect Rect::trimLeft(int cd, double data) {
    if(cd == 0)
        return Rect(lat1, data, lon1, lon2);
    else
        return Rect(lat1, lat2, lon1, data);
}

Rect Rect::trimRight(int cd, double data) {
    if(cd == 0)
        return Rect(data, lat2, lon1, lon2);
    else
        return Rect(lat1, lat2, data, lon2);
}

double distance(pair<double, double> Q, Rect BB) {
    double lat = Q.first;
    double lon = Q.second;
    /*if (BB.lon1 > 90 && BB.lon2 < -90){
        if (lat <= BB.lat1 && lat <= BB.lat2 && (lon <= BB.lon1 || lon >= BB.lon2))
            return 0;
        else if (lat < BB.lat1 && lon > BB.lon1)
            return haversine(lat, lon, BB.lat1, BB.lon1);
        else if (lat < BB.lat1 && lon < BB.lon2)
            return haversine(lat, lon, BB.lat1, BB.lon2);
        else if (lat > BB.lat2 && lon > BB.lon1)
            return haversine(lat, lon, BB.lat2, BB.lon1);
        else if (lat > BB.lat2 && lon < BB.lon2)
            return haversine(lat, lon, BB.lat2, BB.lon2);
        else if (lat < BB.lat1)
            return haversine(lat, lon, BB.lat1, lon);
        else if (lat > BB.lat2)
            return haversine(lat, lon, BB.lat2, lon);
        else if (lon > BB.lon1)
            return haversine(lat, lon, lat, BB.lon1);
        else
            return haversine(lat, lon, lat, BB.lon2);*/
    // } else {
        if (lat >= BB.lat1 && lat <= BB.lat2 && lon >= BB.lon1 && lon <= BB.lon2)
            return 0;
        else if (lat < BB.lat1 && lon < BB.lon1)
            return haversine(lat, lon, BB.lat1, BB.lon1);
        else if (lat < BB.lat1 && lon > BB.lon2)
            return haversine(lat, lon, BB.lat1, BB.lon2);
        else if (lat > BB.lat2 && lon < BB.lon1)
            return haversine(lat, lon, BB.lat2, BB.lon1);
        else if (lat > BB.lat2 && lon > BB.lon2)
            return haversine(lat, lon, BB.lat2, BB.lon2);
        else if (lat < BB.lat1)
            return haversine(lat, lon, BB.lat1, lon);
        else if (lat > BB.lat2)
            return haversine(lat, lon, BB.lat2, lon);
        else if (lon < BB.lon1)
            return haversine(lat, lon, lat, BB.lon1);
        else
            return haversine(lat, lon, lat, BB.lon2);
    // }
}
