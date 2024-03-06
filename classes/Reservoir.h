#ifndef DA_1_RESERVOIR_H
#define DA_1_RESERVOIR_H

#include "string"

using namespace std;

class Reservoir {
    private:
        string name;
        string municipality;
        string id;
        string code;
        int MaxDelivery;
    public:
        Reservoir();
        Reservoir(string name, string municipality, string id, string code, int MaxDelivery);
        string getName() const;
        string getMunicipality() const;
        string getId() const;
        string getCode() const;
        int getMaxDelivery() const;
        bool operator==(const Reservoir& other) const {
            return this->code == other.code;
        }
};

#endif //DA_1_RESERVOIR_H