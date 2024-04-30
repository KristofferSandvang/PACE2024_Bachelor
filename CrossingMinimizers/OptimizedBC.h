#ifndef OPTIMIZEDBC_H
#define OPTIMIZEDBC_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>
class OptimizedBC : public CrossingMinimizer
{
private:
    void handleSameBCVal(std::vector<std::pair<float, Vertex> >* bcValues);
    void optimizeOrder(std::vector<int>*  vertexIndices);
public:
    OptimizedBC(Graph* graph, std::string solutionFileName);
    void minimizeCrossings() override;
    ~OptimizedBC();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;
};


#endif