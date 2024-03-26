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
        unordered_map<string, double> cityMaxFlowOriginalGraph;
        list<vector<string>> rawReservoirs;
        list<vector<string>> rawStations;
        list<vector<string>> rawCities;
        list<vector<string>> rawPipes;
    public:
        Dataset();
        Dataset(list<vector<string>> rawReservoirs, list<vector<string>> rawStations, list<vector<string>> rawCities, list<vector<string>> rawPipes);
        void loadReservoirs();
        void loadStations();
        void loadCities();
        void loadPipes();
        void loadSuperSource();

        double edmondsKarp(string source, string target);
        void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);
        bool findAugmentingPath(Vertex<string> *s, Vertex<string> *t);
        double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
        void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);

        bool waterNeeds(list<vector<string>> rawCities);
        void cityMaxFlowMap(list<vector<string>> rawCities);
        double maxFlow();
        bool removeR_Or_PS_Effects(string v);

        bool removePipeline_Effects(string pointA, string pointB);

        Graph<string> getNetwork() const;
};


#endif //DA_1_DATASET_H