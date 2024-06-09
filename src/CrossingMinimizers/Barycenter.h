#ifndef BARYCENTER_H
#define BARYCENTER_H

#include "CrossingMinimizer.h"
#include <string>

class Barycenter : public CrossingMinimizer {
    private:
    
    public:
        Barycenter(Graph* graph);
        void minimizeCrossings() override;
        virtual ~Barycenter();
        using CrossingMinimizer::writeSolution;
        using CrossingMinimizer::getNewB;
};

#endif
