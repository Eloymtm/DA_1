#include "Station.h"

Station::Station(){
    this->id = "";
    this->code = "";
}

Station::Station(string id, string code){
    this->id = id;
    this->code = code;
}

string Station::getId() const{
    return this->id;
}

string Station::getCode() const{
    return this->code;
}