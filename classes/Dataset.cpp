#include "Dataset.h"



template<class T>
Graph<T> Dataset<T>::getNetwork() const {
    return this->network;
}

template<class T>
Dataset<T>::Dataset() {}


template<class T>
Dataset<T>::Dataset(list<vector<T>> rawReservoirs, list<vector<T>> rawStations, list<vector<T>> rawCities, list<vector<T>> rawPipes){
    loadReservoirs(rawReservoirs);
    loadStations(rawStations);
    loadCities(rawCities);
    loadPipes(rawPipes);
}

template<class T>
void Dataset<T>::loadSuperSink(){
    Vertex<T>* superSink;
    superSink->setInfo("SuperSink");
    network.addVertex("SuperSink");
    for(Vertex<T>* v : network.getVertexSet()){
        if(v->getInfo()[0] == 'r'){
            superSink->addEdge(v, INF);
        }
    }
}

template<class T>
void Dataset<T>::loadPipes(list<vector<T>> rawPipes) {
    for(vector<T> pipe : rawPipes){
        Vertex<T>* src = network.findVertex(pipe[0]);
        Vertex<T>* dest = network.findVertex(pipe[1]);
        if(stoi(pipe[3]) == 1){
            src->addEdge(dest, stod(pipe[2]));
        }
        else{
            src->addEdge(dest, stod(pipe[2]));
            dest->addEdge(src, stod(pipe[2]));
        }
    }
}

template<class T>
void Dataset<T>::loadCities(list<vector<T>> rawCities) {
    for(vector<T> city : rawCities){
        this->network.addVertex(city[2]);
        this->cities[city[2]] = City(city[0], city[1], city[2], stof(city[3]), stoi(city[4]));
    }
}

template<class T>
void Dataset<T>::loadStations(list<vector<T>> rawStations) {
    for(vector<T> station : rawStations){
        this->network.addVertex(station[1]);
        this->stations[station[1]] = Station(station[0], station[1]);
    }
}

template<class T>
void Dataset<T>::loadReservoirs(list<vector<T>> rawReservoirs) {
    for(vector<T> reservoir : rawReservoirs){
        this->network.addVertex(reservoir[3]);
        this->reservoirs[reservoir[3]] = Reservoir(reservoir[0], reservoir[1], reservoir[2], reservoir[3], stoi(reservoir[4]));
    }
}

