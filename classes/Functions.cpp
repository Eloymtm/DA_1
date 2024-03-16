//
// Created by eloy_mm2004 on 16-03-2024.
//

#include "Functions.h"


template<class T>
void Functions<T>::setNetwork(Graph<T> network){
    this->Network = network;
}

template <class T>
void Functions<T>::getMaxAmountWater(Graph<T>* graph, T source, T target) {
    Vertex<T>* s = graph->findVertex(source);
    Vertex<T>* t = graph->findVertex(target);
    double flow = INF;

    for (Vertex<T>* a : graph->getVertexSet()) {
        for (Edge<T> b: a->getAdj()) {
            b.setFlow(0);
        }
    }
    while(flow != getMinimumFlowInPath(s, t)) {
        double flowAux = getMinimumFlowInPath(s, t);
        setAugmentFlow(s, t, flowAux);
    }

}

template <class T>
double Functions<T>::getMinimumFlowInPath(Vertex<T>* source, Vertex<T>* target){
    double finalCapacity = INF;  //Maior valor possivel para depois poder substituir
    Vertex<T>* finalVertex = target;

    while(finalVertex != source){
        Edge<T> a = finalVertex->getPath();
        if(a.getDest() == target){
            if(a.getWeight()-a.getFlow() > finalCapacity){
                finalCapacity = a.getWeight()-a.getFlow();
            }
            finalVertex = a.getOrig();
        }
        else{
            if(a.getFlow() > finalCapacity){
                finalCapacity = a.getFlow();
            }
            finalVertex = a.getDest();
    }

}
    return finalCapacity;
}

template<class T>
void Functions<T>::setAugmentFlow(Vertex<T>* source, Vertex<T>* target, double flowMin){
    Vertex<T>* finalVertex = target;

    while(finalVertex != source){
        Edge<T> a = finalVertex->getPath();
        double flow = a.getFlow();
        if(a.getDest() == finalVertex){
            a.setFlow(flow + flowMin);
            finalVertex = a.getOrig();
        }
        else if(a.getOrig() == finalVertex){
            a.setFlow(flow-flowMin);
            finalVertex = a.getDest();
        }
    }
}