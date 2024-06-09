#ifndef OPTIMIZEDBC_H
#define OPTIMIZEDBC_H

#include "CrossingMinimizer.h"
#include <string>
#include <vector>
#include <map>

class OptimizedBC : public CrossingMinimizer
{
    private:
        void handleSameBCVal(std::map<float, std::vector<int> >* BCmap);
        void optimizeOrder(std::vector<int>*  vertexIndices);
    public:
        OptimizedBC(Graph* graph);
        void minimizeCrossings() override;
        virtual ~OptimizedBC();
        using CrossingMinimizer::writeSolution;
        using CrossingMinimizer::getNewB;
};

#endif
