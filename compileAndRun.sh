#!/usr/bin/env bash
# Skal have en make file, som compiler alle vores cpp filer :)
g++ Program.cpp Graph.cpp Vertex.cpp -o program.o
./program.o
rm *.o
cd visualizer
python visualizer.py ../tests/graphs/test.gr ../tests/solutions/test.sol
cd ..