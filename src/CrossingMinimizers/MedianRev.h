#ifndef MEDIANREV_H
#define MEDIANREV_H

#include "CrossingMinimizer.h"
#include <string>

class MedianRev : public CrossingMinimizer {
    private:
        void handleSameMEDREVVal(std::vector<std::pair<float, Vertex> >* bcValues);
        void optimizeOrderMEDREV(std::vector<int>*  vertexIndices);
    public:
        MedianRev(Graph* graph);
        void minimizeCrossings() override;
        virtual ~MedianRev();
        using CrossingMinimizer::writeSolution;
        using CrossingMinimizer::getNewB;
};

#endif
