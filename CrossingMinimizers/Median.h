#ifndef MEDIAN_H
#define MEDIAN_H

#include "CrossingMinimizer.h"
#include <string>

class Median : protected CrossingMinimizer
{
private:
  
public:
    Median(Graph* graph, std::string solutionFileName);
    void minimizeCrossings() override;
    ~Median();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;

};

#endif