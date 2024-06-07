#ifndef BOGOMINIMIZER_H
#define BOGOMINIMIZER_H

#include "CrossingMinimizer.h"
#include <string>

class BogoMinimizer : public CrossingMinimizer {
    private:
    
    public:
        BogoMinimizer(Graph* graph);
        void minimizeCrossings() override;
        ~BogoMinimizer();
        using CrossingMinimizer::writeSolution;
        using CrossingMinimizer::getNewB;
};

#endif
