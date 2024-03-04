#!/usr/bin/env bash
# Skal have en make file, som compiler alle vores cpp filer :)
g++ -O3 -std=c++17 Program.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp ./CrossingMinimizers/OptimizedBC.cpp -o program.o
echo "Program compiled"
./program.o ./tests/graphs/test.gr
rm *.o
cd visualizer
python visualizer.py ../tests/graphs/test.gr ../tests/solutions/test.sol
cd ..
pace2024verifier ./tests/graphs/test.gr ./tests/solutions/test.sol -c
