#!/usr/bin/env bash
if [ -z "$1" ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

g++ -std=c++17 -Ofast ./src/Hybrid.cpp ./src/Graph.cpp ./src/Vertex.cpp ./src/CrossingMinimizers/Crossingminimizer.cpp ./src/CrossingMinimizers/Barycenter.cpp ./src/CrossingMinimizers/Median.cpp ./src/CrossingMinimizers/OptimizedBC.cpp ./src/CrossingMinimizers/OptimizedMedian.cpp ./src/CrossingMinimizers/BarycenterMed.cpp ./src/CrossingMinimizers/BarycenterRev.cpp ./src/CrossingMinimizers/MedianBary.cpp ./src/CrossingMinimizers/MedianRev.cpp -o Hybrid.o

if [ $? -ne 0 ]; then
  echo "Compilation failed"
  exit 1
fi

./Hybrid.o < $1
rm Hybrid.o