#include "Dataset.h"

Graph Dataset::getNetwork() const {
    return this->network;
}

Dataset::Dataset() {}

Dataset::Dataset(list<vector<string>> rawReservoirs, list<vector<string>> rawStations, list<vector<string>> rawCities, list<vector<string>> rawPipes){
    loadReservoirs(rawReservoirs);
    loadStations(rawStations);
    loadCities(rawCities);
    loadPipes(rawPipes);
}

void Dataset::loadPipes(list<vector<string>> rawPipes) {
    for(vector<string> pipe : rawPipes){
        Vertex* src = network.findVertex(pipe[0]);
        Vertex* dest = network.findVertex(pipe[1]);
        if(stoi(pipe[3]) == 1){
            src.addEdge(dest, stod(pipe[2]));
        }
        else{
            src.addEdge(dest, stod(pipe[2]));
            dest.addEdge(src, stod(pipe[2]));
        }
    }
}

void Dataset::loadCities(list<vector<string>> rawCities) {
    for(vector<string> city : rawCities){
        this->network.addVertex(city[2]);
        this->cities[city[2]] = City(city[0], city[1], city[2], stof(city[3]), stoi(city[4]));
    }
}

void Dataset::loadStations(list<vector<string>> rawStations) {
    for(vector<string> station : rawStations){
        this->network.addVertex(station[1]);
        this->stations[station[1]] = Station(station[0], station[1]);
    }
}

void Dataset::loadReservoirs(list<vector<string>> rawReservoirs) {
    for(vector<string> reservoir : rawCities){
        this->network.addVertex(reservoir[3]);
        this->reservoirs[reservoir[3]] = Reservoir(reservoir[0], reservoir[1], reservoir[2], reservoir[3], stoi(reservoir[4]));
    }
}

