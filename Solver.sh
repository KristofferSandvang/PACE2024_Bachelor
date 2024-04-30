#!/usr/bin/env bash
g++ -std=c++17 -O3 solver.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp ./CrossingMinimizers/OptimizedBC.cpp ./CrossingMinimizers/OptimizedMedian.cpp ./CrossingMinimizers/ParentMinimizer.cpp ./CrossingMinimizers/OptimizedBCRight.cpp -o solver.o
pace2024tester --no-tiny --test ./tests/medium_test_set solver.o
rm *.o