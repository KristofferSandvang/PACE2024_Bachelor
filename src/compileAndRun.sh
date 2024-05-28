#!/usr/bin/env bash
# Skal have en make file, som compiler alle vores cpp filer :)
g++ -std=c++17 program.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Assignment.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp ./CrossingMinimizers/OptimizedBC.cpp ./CrossingMinimizers/OptimizedMedian.cpp ./CrossingMinimizers/ParentMinimizer.cpp ./CrossingMinimizers/OptimizedBCRight.cpp ./CrossingMinimizers/BogoMinimizer.cpp -o program.o
echo "Program compiled"
./program.o < ../tests/graphs/test.gr #> ../tests/solutions/test.sol
# rm *.o
# cd ../visualizer
# python visualizer.py ../tests/graphs/test.gr ../tests/solutions/test.sol
# cd ..
# pace2024verifier ../tests/graphs/test.gr ../tests/solutions/test.sol
# cd ./src