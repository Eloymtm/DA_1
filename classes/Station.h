#ifndef DA_1_STATION_H
#define DA_1_STATION_H

#include "string"

using namespace std;

class Station {
    private:
        string id;
        string code;
    public:
        Station();
        Station(string id, string code);
        string getId() const;
        string getCode() const;
};

#endif DA_1_STATION_H