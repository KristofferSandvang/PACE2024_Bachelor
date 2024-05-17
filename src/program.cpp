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
    OptimizedBC optimizedBC(&graph);
    optimizedBC.minimizeCrossings();
    // optimizedBC.writeSolution();
    OptimizedMedian optimizedMedian(&graph);
    optimizedMedian.minimizeCrossings();
    optimizedMedian.writeSolution();
    return 0;
}