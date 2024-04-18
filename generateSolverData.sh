#!/usr/bin/env bash
g++ -std=c++17 -O3 MTSolverData.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp ./CrossingMinimizers/OptimizedBC.cpp ./CrossingMinimizers/Split.cpp ./CrossingMinimizers/OptimizedMedian.cpp ./CrossingMinimizers/ParentMinimizer.cpp ./CrossingMinimizers/OptimizedBCRight.cpp ./CrossingMinimizers/BogoMinimizer.cpp -o program.o
echo "program compiled"

testGraphs="./tests/graphs/public"
for file in "$testGraphs"/*.gr; do
     if [ -f "$file" ]; then
        echo "$file"
        ./program.o "$file"
        echo "============================================="
    fi
done

rm *.o