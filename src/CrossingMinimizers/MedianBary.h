#ifndef MEDIANBARY_H
#define MEDIANBARY_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>
class MedianBary : public CrossingMinimizer
{
private:
    void handleSameMedianBaryVal(std::vector<std::pair<float, Vertex> >* MedValues);
    void optimizeOrderMedianBary(std::vector<int>* vertexIndices);
public:
    MedianBary(Graph* graph);
    void minimizeCrossings() override;
    ~MedianBary();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;
};

#endif