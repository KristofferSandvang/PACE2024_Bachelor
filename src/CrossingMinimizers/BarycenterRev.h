#ifndef BARYCENTERREV_H
#define BARYCENTERREV_H

#include "CrossingMinimizer.h"
#include <string>

class BarycenterRev : public CrossingMinimizer {
    private:
        void handleSameBCREVVal(std::vector<std::pair<float, Vertex> >* bcValues);
        void optimizeOrderBCREV(std::vector<int>*  vertexIndices);
    public:
        BarycenterRev(Graph* graph);
        void minimizeCrossings() override;
        virtual ~BarycenterRev();
        using CrossingMinimizer::writeSolution;
        using CrossingMinimizer::getNewB;
};

#endif
