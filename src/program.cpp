#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
#include "CrossingMinimizers/BarycenterMed.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include "CrossingMinimizers/OptimizedMedian.h"
#include "CrossingMinimizers/OptimizedBCRight.h"
#include "CrossingMinimizers/ParentMinimizer.h"
#include "CrossingMinimizers/MedianBary.h"
#include "CrossingMinimizers/Assignment.h"
#include <algorithm>
#include <memory>
#include <iostream>

int main() {
    Graph graph(std::cin);
    Assignment assignment(&graph);
    assignment.minimizeCrossings();
    assignment.writeSolution();
    
    return 0;
}