#ifndef DA_1_DATASET_H
#define DA_1_DATASET_H

#include "Graph.h"
#include "City.h"
#include "Station.h"
#include "Reservoir.h"
#include <list>
#include <unordered_map>

using namespace std;

class Dataset {
    private:
        Graph network;
        unordered_map<string, City> cities;
        unordered_map<string, Station> stations;
        unordered_map<string, Reservoir> reservoirs;
    public:
        Dataset();
        Dataset(list<vector<string>> rawReservoirs, list<vector<string>> rawStations, list<vector<string>> rawCities);
        void loadReservoirs(list<vector<string>> rawReservoirs);
        void loadStations(list<vector<string>> rawStations);
        void loadCities(list<vector<string>> rawCities);
        void loadPipes(list<vector<string>> rawPipes);

        Graph getNetwork() const;
};


#endif //DA_1_DATASET_H