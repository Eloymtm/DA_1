#include "City.h"

City::City(){
    this->name = "";
    this->id = "";
    this->code = "";
    this->demand = 0;
    this->population = 0;
}

City::City(string name, string id, string code, float demand, int population){
    this->name = name;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

string City::getName() const{
    return this->name;
}

string City::getId() const{
    return this->id;
}

string City::getCode() const{
    return this->code;
}

float City::getDemand() const{
    return this->demand;
}

int City::getPopulation() const{
    return this->population;
}