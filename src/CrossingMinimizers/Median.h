#ifndef MEDIAN_H
#define MEDIAN_H

#include "CrossingMinimizer.h"
#include <string>

class Median : public CrossingMinimizer
{
private:
  
public:
    Median(Graph* graph);
    void minimizeCrossings() override;
    ~Median();
    using CrossingMinimizer::writeSolution;
    using CrossingMinimizer::getNewB;

};

#endif