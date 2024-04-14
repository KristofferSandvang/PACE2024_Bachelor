#ifndef PARENTMINIMIZER_H
#define PARENTMINIMIZER_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>

class ParentMinimizer : protected CrossingMinimizer
{
private:
    std::vector<Vertex> A;
public:
    ParentMinimizer(Graph* graph, std::string solutionFileName);
    void minimizeCrossings() override;
    ~ParentMinimizer();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;

};

#endif