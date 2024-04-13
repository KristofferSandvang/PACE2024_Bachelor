#ifndef BOGOMINIMIZER_H
#define BOGOMINIMIZER_H

#include "CrossingMinimizer.h"
#include <string>

class BogoMinimizer : CrossingMinimizer
{
private:
  
public:
    BogoMinimizer(Graph* graph, std::string solutionFileName);
    void minimizeCrossings() override;
    ~BogoMinimizer();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;
};


#endif