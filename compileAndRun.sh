#!/usr/bin/env bash
# Skal have en make file, som compiler alle vores cpp filer :)
g++ -std=c++17 Program.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp -o program.o
echo "Program compiled"
./program.o ./tests/graphs/ladder_4_4_sorted.gr
rm *.o
cd visualizer
python visualizer.py ../tests/graphs/ladder_4_4_sorted.gr ../tests/solutions/ladder_4_4_sorted.gr.sol
cd ..
pace2024verifier ./tests/graphs/ladder_4_4_sorted.gr ./tests/solutions/ladder_4_4_sorted.sol -c
