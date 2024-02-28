#ifndef CROSSINGMINIMIZER_H
#define CROSSINGMINIMIZER_H

#include "../Graph.h"
#include "../Vertex.h"
#include <string>

class CrossingMinimizer
{
    protected:
    Graph graph;
    std::string solutionFileName;
    void writeSolution(std::vector<Vertex> B);

    public:
    CrossingMinimizer(Graph graph, std::string solutionFile);
    
    virtual void minimizeCrossings() = 0;

    ~CrossingMinimizer();
};

#endif
