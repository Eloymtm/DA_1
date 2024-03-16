//
// Created by eloy_mm2004 on 16-03-2024.
//

#ifndef G03_1_FUNCTIONS_H
#define G03_1_FUNCTIONS_H

#include "Dataset.h"


template<class T>
class Functions{
    void getMaxAmountWater(Graph<T>* graph, T source, T target);
    double getMinimumFlowInPath(Vertex<T>* source, Vertex<T>* target);
    void setAugmentFlow(Vertex<T>* source, Vertex<T>* target, double flow);
    void setNetwork(Graph<T> network);
private:
    Graph<T> Network;
};

#endif //G03_1_FUNCTIONS_H
