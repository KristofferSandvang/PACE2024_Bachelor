#ifndef BARYCENTERMED_H
#define BARYCENTERMED_H

#include "CrossingMinimizer.h"
#include <string>

class BarycenterMed : public CrossingMinimizer
{
private:
    void handleSameBCMEDVal(std::vector<std::pair<float, Vertex> >* bcValues);
    void optimizeOrderBCMED(std::vector<int>*  vertexIndices);
public:
    BarycenterMed(Graph* graph);
    void minimizeCrossings() override;
    ~BarycenterMed();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;
};


#endif