#include "Dataset.h"
#include "map"

Graph<string> Dataset::getNetwork() const {
    return this->network;
}

Dataset::Dataset() {}

Dataset::Dataset(list<vector<string>> rawReservoirs, list<vector<string>> rawStations, list<vector<string>> rawCities, list<vector<string>> rawPipes){
    this->rawCities = rawCities;
    this->rawPipes = rawPipes;
    this->rawReservoirs = rawReservoirs;
    this->rawStations = rawStations;
    loadReservoirs();
    loadStations();
    loadCities();
    loadPipes();
    loadSuperSource();
    loadSuperSink();
    cityMaxFlowMap(rawCities);
}

void Dataset::loadPipes() {
    for(vector<string> pipe : rawPipes){
        Vertex<string>* src = network.findVertex(pipe[0]);
        Vertex<string>* dest = network.findVertex(pipe[1]);
        if(stoi(pipe[3]) == 1){
            src->addEdge(dest, stod(pipe[2]));
        }
        else{
            src->addEdge(dest, stod(pipe[2]));
            dest->addEdge(src, stod(pipe[2]));
        }
    }
}

void Dataset::loadCities() {
    for(vector<string> city : rawCities){
        this->network.addVertex(city[2]);
        this->cities[city[2]] = City(city[0], city[1], city[2], stof(city[3]), stoi(city[4]));
    }
}

void Dataset::loadStations() {
    for(vector<string> station : rawStations){
        this->network.addVertex(station[1]);
        this->stations[station[1]] = Station(station[0], station[1]);
    }
}

void Dataset::loadReservoirs() {
    for(vector<string> reservoir : rawReservoirs){
        this->network.addVertex(reservoir[3]);
        this->reservoirs[reservoir[3]] = Reservoir(reservoir[0], reservoir[1], reservoir[2], reservoir[3], stoi(reservoir[4]));
    }
}

void Dataset::loadSuperSource(){

    network.addVertex("SuperSource");
    Vertex<string>* superSource = network.findVertex("SuperSource");
    for(Vertex<string>* v : network.getVertexSet()){
        if(v->getInfo().substr(0,1) == "R"){
            superSource->addEdge(v, reservoirs[v->getInfo()].getMaxDelivery());
        }
    }
}

void Dataset::loadSuperSink(){
    network.addVertex("SuperSink");
    Vertex<string>* superSink = network.findVertex("SuperSink");
    for(Vertex<string>* v: network.getVertexSet()){
        if(v->getInfo().substr(0,1) == "C"){

            v->addEdge(superSink,cities[v->getInfo()].getDemand());
        }
    }
}

void Dataset::testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Dataset::findAugmentingPath(Graph<string> g, Vertex<string> *s, Vertex<string> *t) {
    for(auto v : g.getVertexSet()) {
        v->setVisited(false);
    }

    s->setVisited(true);
    std::queue<Vertex<string> *> q;
    q.push(s);

    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();

        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }

        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }

    return t->isVisited();
}

double Dataset::findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t) {
    double f = INF;

    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }

    return f;
}

void Dataset::augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

double Dataset::edmondsKarp(Graph<string> g,string source, string target) {
    Vertex<string>* s = g.findVertex(source);
    Vertex<string>* t = g.findVertex(target);

    double maxFlow = 0;

    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    for (auto v : g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        maxFlow += f;
        augmentFlowAlongPath(s, t, f);
    }

    return maxFlow;
}

bool Dataset::waterNeeds(Graph<string> g,list<vector<string>> rawCities){
    map<string, double> waterSupply;
    int r = 0;

    edmondsKarp(g, "SuperSource", "SuperSink");

    for(vector<string> city : rawCities){
        double maxFlow = 0;
        for(Vertex<string>* v : g.getVertexSet()){
            for(auto e : v->getAdj()){
                if(e->getDest()->getInfo() == city[2]){
                    maxFlow += e->getFlow();
                }
            }
        }
        waterSupply.insert(make_pair(city[2], maxFlow));
    }

    auto it = waterSupply.begin();
    while(it != waterSupply.end()){
        auto city = cities.find(it->first);
        if(it->second < city->second.getDemand()){
            cout << it->first << " " << city->second.getDemand() - it->second << "\n";
            r++;
        }
        it++;
    }

    if(r > 0){
        return false;
    }

    return true;
}

void Dataset::cityMaxFlowMap(list<vector<string>> rawCities){
    edmondsKarp(network,"SuperSource", "SuperSink");

    for(vector<string> city : rawCities){
        double maxFlow = 0;
        for(Vertex<string>* v : network.getVertexSet()){
            for(auto e : v->getAdj()){
                if(e->getDest()->getInfo() == city[2]){
                    maxFlow += e->getFlow();
                }
            }
        }
        cityMaxFlowOriginalGraph.insert(make_pair(city[2], maxFlow));
    }
}

double Dataset::maxFlow(){
    double r = 0;

    auto it = cityMaxFlowOriginalGraph.begin();
    while(it != cityMaxFlowOriginalGraph.end()){
        r += it->second;
        it++;
    }

    return r;
}

bool Dataset::removeR_Or_PS_Effects(Graph<string> g,string v){
    g.removeVertex(v);

    unordered_map<string, double> waterSupply;
    int r = 0;

    edmondsKarp(g,"SuperSource", "SuperSink");

    for(vector<string> city : rawCities){
        double maxFlow = 0;
        for(Vertex<string>* x : g.getVertexSet()){
            for(auto e : x->getAdj()){
                if(e->getDest()->getInfo() == city[2]){
                    maxFlow += e->getFlow();
                }
            }
        }
        waterSupply.insert(make_pair(city[2], maxFlow));
    }

    cout << "Total deficit according to the Demand:\n";
    auto it = waterSupply.begin();
    while(it != waterSupply.end()){
        auto city = cities.find(it->first);
        if(it->second < city->second.getDemand()){
            cout << it->first << " --> " << city->second.getDemand() - it->second << "\n";
        }
        it++;
    }

    cout << "\nDeficit relative to the initial max flow of each city:\n";
    auto it2 = waterSupply.begin();
    while(it2 != waterSupply.end()){
        auto city = cityMaxFlowOriginalGraph.find(it2->first);
        if(it2->second < city->second){
            cout << it2->first << " --> " << city->second - it2->second << "\n";
            r++;
        }
        it2++;
    }

    if(r > 0){
        return false;
    }

    return true;
}

bool Dataset::removePipeline_Effects(Graph<string> g, string pointA, string pointB){
    for(auto v : this->network.getVertexSet()){
        for(auto e : v->getAdj()){
            if(e->getOrig()->getInfo() == pointA && e->getDest()->getInfo() == pointB){
                e->setWeight(0);
            }
        }
    }

    unordered_map<string, double> waterSupply;
    int r = 0;

    edmondsKarp(g,"SuperSource", "SuperSink");

    for(vector<string> city : rawCities){
        double maxFlow = 0;
        for(Vertex<string>* x : g.getVertexSet()){
            for(auto e : x->getAdj()){
                if(e->getDest()->getInfo() == city[2]){
                    maxFlow += e->getFlow();
                }
            }
        }
        waterSupply.insert(make_pair(city[2], maxFlow));
    }

    cout << "Total deficit according to the Demand:\n";
    auto it = waterSupply.begin();
    while(it != waterSupply.end()){
        auto city = cities.find(it->first);
        if(it->second < city->second.getDemand()){
            cout << it->first << " --> " << city->second.getDemand() - it->second << "\n";
        }
        it++;
    }

    cout << "\nDeficit relative to the initial max flow of each city:\n";
    auto it2 = waterSupply.begin();
    while(it2 != waterSupply.end()){
        auto city = cityMaxFlowOriginalGraph.find(it2->first);
        if(it2->second < city->second){
            cout << it2->first << " --> " << city->second - it2->second << "\n";
            r++;
        }
        it2++;
    }

    if(r > 0){
        return false;
    }

    return true;
}

Metrics Dataset::getMetrics(Graph<string> g){
    Metrics res;

    double total_difference = 0;
    double average = 0;
    vector<double> differences;
    double max_dif = 0;

    for(auto v : g.getVertexSet()){
        for(auto e : v->getAdj()){
            if(e->getOrig()->getInfo() == "SuperSource" || e->getOrig()->getInfo().substr(0,1) == "C"){
                e->setProcessed(true);
            }
            else{
                e->setProcessed(false);
            }
        }
    }

    for(auto v : g.getVertexSet()){
        for(auto e : v->getAdj()){
            if(!e->isProcessed()){
                double diff = abs(e->getWeight() - e->getFlow());
                differences.push_back(diff);
                total_difference += diff;
                if(diff > max_dif){
                    max_dif = diff;
                }

                e->setProcessed(true);
            }
        }
    }

    average = total_difference / ((double) differences.size());
    double sumSquaredDifference = 0.0;
    for(double difference : differences){
        sumSquaredDifference += pow(difference- average, 2);
    }
    double variance = sumSquaredDifference / ((double) differences.size());

    res.average = average;
    res.variance = variance;
    res.max_difference = max_dif;
    return res;
}

void Dataset::balanceNetwork(Graph<string> g){ //void but could be changed to return Metrics if it eases the menu stuff
    edmondsKarp(g, "SuperSource", "SuperSink"); //get paths
    unordered_map<string , double> overloadedCitiesFlow;//map of overflowing cities -> amount of overflow

    Metrics oldMetrics = getMetrics(g);
    cout << "Actual average = " << oldMetrics.average << " Actual maximum difference = " << oldMetrics.max_difference << " Actual variance = " << oldMetrics.variance << "\n";

    auto it = cityMaxFlowOriginalGraph.begin();
    while(it != cityMaxFlowOriginalGraph.end()){
        auto city = cities.find(it->first);
        if(it->second > city->second.getDemand()){
            overloadedCitiesFlow.insert(make_pair(it->first,it->second - city->second.getDemand()));
        }
        it++;
    }

    for(auto p: overloadedCitiesFlow){ //loop through the overloaded cities
        Vertex<string> *city = g.findVertex(p.first);

        for(auto e : city->getIncoming()){
            if(p.second > 0){
                city->addEdge(e->getOrig(),min(e->getWeight(), p.second));
                p.second -= min(e->getWeight(), p.second);
            }
        }

        edmondsKarp(g, p.first, "SuperSink");
    }
    Metrics newMetrics = getMetrics(g); //get metrics after balancing is done to afterwards compare

    cout << "New average = " << newMetrics.average << " New maximum difference = " << newMetrics.max_difference << " New variance = " << newMetrics.variance;
}

