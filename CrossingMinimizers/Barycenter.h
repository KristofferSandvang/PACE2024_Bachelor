#ifndef BARYCENTER_H
#define BARYCENTER_H

#include "CrossingMinimizer.h"
#include <string>

class Barycenter : CrossingMinimizer
{
private:
  
public:
    Barycenter(Graph* graph, std::string solutionFileName);
    void minimizeCrossings() override;
    ~Barycenter();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;
};


#endif