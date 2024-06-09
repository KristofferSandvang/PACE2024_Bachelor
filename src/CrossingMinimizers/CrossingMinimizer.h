#ifndef CROSSINGMINIMIZER_H
#define CROSSINGMINIMIZER_H

#include "../Graph.h"
#include "../Vertex.h"
#include <string>

class CrossingMinimizer {
    protected:
        Graph* graph;
        std::vector<Vertex> B;

    public:
        CrossingMinimizer(Graph* graph);
        void writeSolution();
        std::vector<Vertex>* getNewB();
        virtual void minimizeCrossings() = 0;
        virtual ~CrossingMinimizer();
};

#endif
