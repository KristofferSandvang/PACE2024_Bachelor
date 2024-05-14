#!/usr/bin/env bash
g++ -std=c++17 -O3 MTSolverData.cpp ./src/Graph.cpp ./src/Vertex.cpp ./src/CrossingMinimizers/Crossingminimizer.cpp ./src/CrossingMinimizers/Barycenter.cpp ./src/CrossingMinimizers/Median.cpp ./src/CrossingMinimizers/OptimizedBC.cpp ./src/CrossingMinimizers/OptimizedMedian.cpp ./src/CrossingMinimizers/ParentMinimizer.cpp ./src/CrossingMinimizers/OptimizedBCRight.cpp ./src/CrossingMinimizers/BogoMinimizer.cpp ./src/CrossingMinimizers/BarycenterMed.cpp ./src/CrossingMinimizers/BarycenterRev.cpp ./src/CrossingMinimizers/MedianBary.cpp ./src/CrossingMinimizers/MedianRev.cpp -o program.o
echo "program compiled"

testGraphs="./tests/graphs/public"
for file in "$testGraphs"/*.gr; do
     if [ -f "$file" ]; then
        echo "$file"
        ./program.o < "$file"
        echo "============================================="
    fi
done

rm *.o