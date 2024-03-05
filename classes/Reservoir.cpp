#include "Reservoir.h"

Reservoir::Reservoir(){
    this->name = "";
    this->municipality = "";
    this->id = "";
    this->code = "";
    this->MaxDelivery = 0;
}

Reservoir::Reservoir(string name, string municipality, string id, string code, int MaxDelivery){
    this->name = name;
    this->municipality = municipality;
    this->id = id;
    this->code = code;
    this->MaxDelivery = MaxDelivery;
}

string Reservoir::getName() const{
    return this.name;
}

string Reservoir::getMunicipality() const{
    return this->municipality;
}

string Reservoir::getId() const{
    return this->id;
}

string Reservoir::getCode() const{
    return this->code;
}

int Reservoir::getMaxDelivery() const{
    return this->MaxDelivery;
}