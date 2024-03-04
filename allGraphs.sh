#!/usr/bin/env bash
g++ -std=c++17 Program.cpp Graph.cpp Vertex.cpp ./CrossingMinimizers/Crossingminimizer.cpp ./CrossingMinimizers/Barycenter.cpp ./CrossingMinimizers/Median.cpp -o program.o
echo "Program compiled"

testGraphs="./tests/graphs"

for file in "$testGraphs"/*.gr; do
     if [ -f "$file" ]; then
        echo "$file"
        ./program.o "$file"
        echo "============================================="
    fi
done

rm *.o