#!/bin/bash
g++ -std=c++17 -Ofast MTSolverData.cpp ./src/Graph.cpp ./src/Vertex.cpp ./src/CrossingMinimizers/Crossingminimizer.cpp ./src/CrossingMinimizers/Barycenter.cpp ./src/CrossingMinimizers/Median.cpp ./src/CrossingMinimizers/OptimizedBC.cpp ./src/CrossingMinimizers/OptimizedMedian.cpp ./src/CrossingMinimizers/ParentMinimizer.cpp ./src/CrossingMinimizers/OptimizedBCRight.cpp ./src/CrossingMinimizers/BogoMinimizer.cpp ./src/CrossingMinimizers/BarycenterMed.cpp ./src/CrossingMinimizers/BarycenterRev.cpp ./src/CrossingMinimizers/MedianBary.cpp ./src/CrossingMinimizers/MedianRev.cpp ./src/CrossingMinimizers/Assignment.cpp -o program.o
echo "Program compiled"

testGraphs="./tests/graphs/allGraphs"

for file in "$testGraphs"/*.gr; do
    if [ -f "$file" ]; then
        echo "$file"
        basename=$(basename "$file" .gr)
        echo "$basename" >> solvers.csv
        
        ./program.o < "$file"
        echo "============================================="
    fi
done

# Clean up
rm *.o
