#!/usr/bin/env bash
g++ -std=c++17 BarycenterSolver.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp -o BarycenterSolver.o
echo "BarycenterSolver compiled"
g++ -std=c++17 MedianSolver.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Median.cpp -o MedianSolver.o
echo "MedianSolver compiled"
g++ -std=c++17 OptimizedBCSolver.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/OptimizedBC.cpp -o OptimizedBCSolver.o
echo "OptimizedBCSolver compiled"
g++ -std=c++17 OptimizedBCRightSolver.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/OptimizedBCRight.cpp -o OptimizedBCRightSolver.o
echo "OptimizedBCRightSolver compiled"
g++ -std=c++17 OptimizedMedianSolver.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/OptimizedMedian.cpp -o OptimizedMedianSolver.o
echo "OptimizedMedianSolver compiled"

testGraphs="./tests/graphs/medium"
solutionsDirectory="./tests/solutions/medium"
for file in "$testGraphs"/*.gr; do
     if [ -f "$file" ]; then
        echo "$file"

        filename=$(basename -- "$file")
        filenameWithoutExtension="${filename%.*}" 
        ./BarycenterSolver.o "$file"
        solutionFile="$solutionsDirectory/$filenameWithoutExtension.sol"
        pace2024verifier -c "$file" "$solutionFile"
        echo "============================================="
        ./MedianSolver.o "$file"
        solutionFile="$solutionsDirectory/$filenameWithoutExtension.sol"
        pace2024verifier -c "$file" "$solutionFile"
        echo "============================================="
        ./OptimizedBCSolver.o "$file"
        solutionFile="$solutionsDirectory/$filenameWithoutExtension.sol"
        pace2024verifier -c "$file" "$solutionFile"
        echo "============================================="
        ./OptimizedBCRightSolver.o "$file"
        solutionFile="$solutionsDirectory/$filenameWithoutExtension.sol"
        pace2024verifier -c "$file" "$solutionFile"
        echo "============================================="
        ./OptimizedMedianSolver.o "$file"
        solutionFile="$solutionsDirectory/$filenameWithoutExtension.sol"
        pace2024verifier -c "$file" "$solutionFile"
        echo "============================================="
    fi
done

rm *.o