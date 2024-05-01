#ifndef CROSSINGMINIMIZER_H
#define CROSSINGMINIMIZER_H

#include "../Graph.h"
#include "../Vertex.h"
#include <string>

class CrossingMinimizer
{
    protected:
    Graph* graph;
    std::string solutionFileName;
    std::vector<Vertex> B;

    public:
    CrossingMinimizer(Graph* graph, std::string solutionFile);
    void writeSolution();
    std::vector<Vertex>* getNewB();
    virtual void minimizeCrossings() = 0;

    ~CrossingMinimizer();
};

#endif
