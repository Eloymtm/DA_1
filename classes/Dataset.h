#ifndef DA_1_DATASET_H
#define DA_1_DATASET_H

#include "Graph.h"
#include "City.h"
#include "Station.h"
#include "Reservoir.h"
#include <list>
#include <unordered_map>
#include <math.h>

/**
 * Struct to represent all the important variables of the metrics
 */
struct Metrics {
    double average;
    double variance;
    double max_difference;
};

using namespace std;
class Dataset {
    friend class Menu;
protected:
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
        void loadSuperSink();

        double edmondsKarp(Graph<string> g, string source, string target);
        void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);
        bool findAugmentingPath(Graph<string> g, Vertex<string> *s, Vertex<string> *t);
        double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
        void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);

        bool waterNeeds(Graph<string> g, list<vector<string>> rawCities);
        void cityMaxFlowMap(list<vector<string>> rawCities);
        double maxFlow();

        Metrics getMetrics(Graph<string> g);
        void balanceNetwork(Graph<string> g);

        bool removeR_Or_PS_Effects(Graph<string> g, string v);
        bool removePipeline_Effects(Graph<string> g, string pointA, string pointB);

        Graph<string> getNetwork() const;
};


#endif //DA_1_DATASET_H