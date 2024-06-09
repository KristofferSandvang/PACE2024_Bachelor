#ifndef PARENTMINIMIZER_H
#define PARENTMINIMIZER_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>

class ParentMinimizer : public CrossingMinimizer {
    private:
        std::vector<Vertex> A;
    public:
        ParentMinimizer(Graph* graph);
        void minimizeCrossings() override;
        virtual ~ParentMinimizer();
        using CrossingMinimizer::writeSolution;
        using CrossingMinimizer::getNewB;

};

#endif
