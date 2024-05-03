#ifndef OPTIMIZEDBCRIGHT_H
#define OPTIMIZEDBCRIGHT_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>
class OptimizedBCRight : public CrossingMinimizer
{
private:
    void handleSameBCVal(std::vector<std::pair<float, Vertex> >* bcValues);
    void optimizeOrder(std::vector<int>*  vertexIndices);
public:
    OptimizedBCRight(Graph* grap);
    void minimizeCrossings() override;
    ~OptimizedBCRight();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;
};


#endif