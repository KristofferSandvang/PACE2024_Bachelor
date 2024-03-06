#ifndef SPLIT_H
#define SPLIT_H

#include "CrossingMinimizer.h"
#include <string>

class Split : protected CrossingMinimizer
{
private:

public:
    Split(Graph graph, std::string solutionFileName);
    void minimizeCrossings() override;
    
    ~Split();
};

#endif
