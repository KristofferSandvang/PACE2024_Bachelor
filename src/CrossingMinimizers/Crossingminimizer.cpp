#include "CrossingMinimizer.h"
#include <iostream>

CrossingMinimizer::CrossingMinimizer(Graph* graph) {
    CrossingMinimizer::graph = graph;
    CrossingMinimizer::B = *graph->getB();
}

void CrossingMinimizer::writeSolution() {
    for (Vertex vertex : B) {
        std::cout << vertex.toString() << std::endl;
    }

    return;
}

std::vector<Vertex>* CrossingMinimizer::getNewB() {
    return &B;
}

// Destructor 
CrossingMinimizer::~CrossingMinimizer() {}