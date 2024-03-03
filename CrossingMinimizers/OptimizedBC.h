#ifndef OPTIMIZEDBC_H
#define OPTIMIZEDBC_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>
class OptimizedBC : protected CrossingMinimizer
{
private:
    std::vector<Vertex> B;
    void handleSameBCVal(std::vector<std::pair<float, Vertex> > bcValues);
    void optimizeOrder(std::vector<Vertex> vertices);
public:
    OptimizedBC(Graph graph, std::string solutionFileName);
    void minimizeCrossings() override;
    ~OptimizedBC();
};


#endif