#ifndef OPTIMIZEDMEDIAN_H
#define OPTIMIZEDMEDIAN_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>
#include <map>

class OptimizedMedian : public CrossingMinimizer {
    private:
        void handleSameMedianVal(std::map<float, std::vector<int> >* MedMap);
        void optimizeOrder(std::vector<int>* vertexIndices);
    public:
        OptimizedMedian(Graph* graph);
        void minimizeCrossings() override;
        ~OptimizedMedian();
        using CrossingMinimizer::writeSolution;
        using CrossingMinimizer::getNewB;
};

#endif
