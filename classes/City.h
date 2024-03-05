#ifndef DA_1_CITY_H
#define DA_1_CITY_H

#include "string"

using namespace std;

class City {
    private:
        string name;
        string id;
        string code;
        int demand;
        int population;
    public:
        City();
        City(string name, string id, string code, float demand, int population);
        string getName() const;
        string getId() const;
        string getCode() const;
        float getDemand() const;
        int getPopulation() const;
        bool operator==(const City& other) const {
            return this->code == other.code;
        }
};

#endif //DA_1_CITY_H