#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "CrossingMinimizer.h"
#include <vector>
#include <algorithm>
#include <unordered_map>

class Assignment : public CrossingMinimizer
{
private:
    std::vector<std::vector<int> > adjacencyMatrix;
    std::vector<std::vector<int>> crossingMatrix;
    int calculateCost(int i, int j, int n, int m);
    void createCrossingMatrix(Graph* graph);

public:
    Assignment(Graph* graph);
    void minimizeCrossings() override;
    ~Assignment();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;
};

#endif