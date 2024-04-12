#!/usr/bin/env bash
g++ -std=c++17 Program.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/OptimizedBC.cpp ./CrossingMinimizers/OptimizedBCRight.cpp ./CrossingMinimizers/Median.cpp ./CrossingMinimizers/OptimizedMedian.cpp -o program.o
echo "Program compiled"

testGraphs="./tests/graphs/medium"
solutionsDirectory="./tests/solutions/medium"
for file in "$testGraphs"/*.gr; do
     if [ -f "$file" ]; then
        echo "$file"

        filename=$(basename -- "$file")
        filenameWithoutExtension="${filename%.*}" 

        ./program.o "$file"

        solutionFile="$solutionsDirectory/$filenameWithoutExtension.sol"
        pace2024verifier -c "$file" "$solutionFile"

        echo "============================================="
    fi
done

rm *.o