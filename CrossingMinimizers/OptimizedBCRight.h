#ifndef OPTIMIZEDBCRIGHT_H
#define OPTIMIZEDBCRIGHT_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>
class OptimizedBCRight : protected CrossingMinimizer
{
private:
    std::vector<Vertex> B;
    void handleSameBCVal(std::vector<std::pair<float, Vertex> >* bcValues);
    void optimizeOrder(std::vector<int>*  vertexIndices);
public:
    OptimizedBCRight(Graph* grap, std::string solutionFileName);
    void minimizeCrossings() override;
    ~OptimizedBCRight();
};


#endif