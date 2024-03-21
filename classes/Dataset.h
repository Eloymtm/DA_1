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
        Graph<string> network;
        unordered_map<string, City> cities;
        unordered_map<string, Station> stations;
        unordered_map<string, Reservoir> reservoirs;
    public:
        Dataset();
        Dataset(list<vector<string>> rawReservoirs, list<vector<string>> rawStations, list<vector<string>> rawCities, list<vector<string>> rawPipes);
        void loadReservoirs(list<vector<string>> rawReservoirs);
        void loadStations(list<vector<string>> rawStations);
        void loadCities(list<vector<string>> rawCities);
        void loadPipes(list<vector<string>> rawPipes);
        void loadSuperSource();

        double edmondsKarp(Graph<string> g,string source, string target);
        void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);
        bool findAugmentingPath(Graph<string> g, Vertex<string> *s, Vertex<string> *t);
        double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
        void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);

        Graph<string> getNetwork() const;
};


#endif //DA_1_DATASET_H