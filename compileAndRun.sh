#!/usr/bin/env bash
# Skal have en make file, som compiler alle vores cpp filer :)
g++ -std=c++17 Program.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp ./CrossingMinimizers/OptimizedBC.cpp ./CrossingMinimizers/Split.cpp -o program.o
echo "Program compiled"
./program.o ./tests/graphs/matching_4_4.gr
rm *.o
# cd visualizer
#python visualizer.py ../tests/graphs/matching_4_4.gr ../tests/solutions/matching_4_4.sol
# cd ..
pace2024verifier ./tests/graphs/matching_4_4.gr ./tests/solutions/matching_4_4.sol -c
