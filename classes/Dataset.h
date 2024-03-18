#ifndef DA_1_DATASET_H
#define DA_1_DATASET_H

#include "Graph.h"
#include "City.h"
#include "Station.h"
#include "Reservoir.h"
#include <list>
#include <unordered_map>

using namespace std;

template<class T>
class Dataset {
    private:
        Graph<T> network;
        unordered_map<T, City> cities;
        unordered_map<T, Station> stations;
        unordered_map<T, Reservoir> reservoirs;
    public:
        Dataset();
        Dataset(list<vector<T>> rawReservoirs, list<vector<T>> rawStations, list<vector<T>> rawCities, list<vector<T>> rawPipes);
        void loadReservoirs(list<vector<T>> rawReservoirs);
        void loadStations(list<vector<T>> rawStations);
        void loadCities(list<vector<T>> rawCities);
        void loadPipes(list<vector<T>> rawPipes);
        void loadSuperSink();

        Graph<T> getNetwork() const;
};


#endif //DA_1_DATASET_H