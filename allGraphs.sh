#!/usr/bin/env bash
g++ -std=c++17 Program.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp ./CrossingMinimizers/OptimizedBC.cpp ./CrossingMinimizers/Split.cpp ./CrossingMinimizers/OptimizedMedian.cpp ./CrossingMinimizers/ParentMinimizer.cpp ./CrossingMinimizers/OptimizedBCRight.cpp ./CrossingMinimizers/BogoMinimizer.cpp -o program.o
echo "Program compiled"

testGraphs="./tests/graphs"
solutionsDirectory="./tests/solutions"

for file in "$testGraphs"/*.gr; do
     if [ -f "$file" ]; then
        echo "$file"
        ./program.o "$file"
        filename=$(basename -- "$file")
        filenameWithoutExtension="${filename%.*}" 
        solutionFile="$solutionsDirectory/$filenameWithoutExtension.sol"
        pace2024verifier -c "$file" "$solutionFile"
        echo "============================================="
    fi
done

rm *.o