#include "Dataset.h"
#include <queue>



Graph<string> Dataset::getNetwork() const {
    return this->network;
}


Dataset::Dataset() {}



Dataset::Dataset(list<vector<string>> rawReservoirs, list<vector<string>> rawStations, list<vector<string>> rawCities, list<vector<string>> rawPipes){
    loadReservoirs(rawReservoirs);
    loadStations(rawStations);
    loadCities(rawCities);
    loadPipes(rawPipes);
    loadSuperSink();
}


void Dataset::loadSuperSink(){
    Vertex<string>* superSource = new Vertex<string>("SuperSource");
    network.addVertex(superSource->getInfo());
    for(Vertex<string>* v : network.getVertexSet()){
        if(v->getInfo()[0] == 'R'){
            superSource->addEdge(v, INF);
        }
    }
}


void Dataset::loadPipes(list<vector<string>> rawPipes) {
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
    for(vector<string> reservoir : rawReservoirs){
        this->network.addVertex(reservoir[3]);
        this->reservoirs[reservoir[3]] = Reservoir(reservoir[0], reservoir[1], reservoir[2], reservoir[3], stoi(reservoir[4]));
    }
}


void Dataset::getMaxAmountWater(string source, string target) {
    Vertex<string>* s = this->network.findVertex(source);
    Vertex<string>* t = this->network.findVertex(target);
    double flow = INF;

    for (Vertex<string>* a : this->network.getVertexSet()) {
        for (Edge<string>* b: a->getAdj()) {
            b->setFlow(0);
        }
    }
    while(findAugmentingPath(s, t)) {
        double flowAux = getMinimumFlowInPath(s, t);
        cout << "flowAux";
        setAugmentFlow(s, t, flowAux);
    }

}

double Dataset::getMinimumFlowInPath(Vertex<string>* source, Vertex<string>* target){
    double finalCapacity = INF;  //Maior valor possivel para depois poder substituir
    Vertex<string>* finalVertex = target;


    while(finalVertex != source){
        Edge<string>* a = finalVertex->getPath();
        if(a->getDest() == target){
            if(a->getWeight()-a->getFlow() < finalCapacity){
                finalCapacity = a->getWeight()-a->getFlow();
            }
            finalVertex = a->getOrig();
        }
        else{
            if(a->getFlow() < finalCapacity){
                finalCapacity = a->getFlow();
            }
            finalVertex = a->getDest();
        }

    }
    return finalCapacity;
}

void Dataset::testAndVisit(queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Dataset::findAugmentingPath(Vertex<string> *s, Vertex<string> *t) {
// Mark all vertices as not visited
    for(auto v : this->network.getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    queue<Vertex<string> *> q;
    q.push(s);
// BFS to find an augmenting path
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
// Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}
void Dataset::setAugmentFlow(Vertex<string>* source, Vertex<string>* target, double flowMin){
    Vertex<string>* finalVertex = target;

    while(finalVertex != source){
        Edge<string>* a = finalVertex->getPath();
        double flow = a->getFlow();
        if(a->getDest() == finalVertex){
            a->setFlow(flow + flowMin);
            finalVertex = a->getOrig();
        }
        else if(a->getOrig() == finalVertex){
            a->setFlow(flow-flowMin);
            finalVertex = a->getDest();
        }
    }
}

