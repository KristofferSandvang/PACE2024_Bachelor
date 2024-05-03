#include "ParentMinimizer.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

ParentMinimizer::ParentMinimizer (Graph* graph) : CrossingMinimizer(graph) {
    A = *graph->getA();
}

void ParentMinimizer::minimizeCrossings() {
    std::unordered_map<int, bool> status;
    std::vector<Vertex> newB;
    for (int i = 0; i < A.size(); i++) {
        Vertex currentVertex = A.at(i);
        std::vector<Vertex*> edges = currentVertex.getEdges();
        std::sort(edges.begin(), edges.end(), 
            [](Vertex* a, Vertex* b) {
                return a->getVertexDegree() < b->getVertexDegree();
            });
        for (int j = 0; j < edges.size(); j++)
        {
            Vertex* child = edges.at(j);
            if (status[child->getVertexID()]) {
                continue;
            }
            status[child->getVertexID()] = true;
            newB.push_back(*edges.at(j));
        }
        
    }
    B = newB;
}


ParentMinimizer::~ParentMinimizer() {}