# Compile the program
g++ -std=c++17 -Ofast MTSolverData.cpp ./src/Graph.cpp ./src/Vertex.cpp ./src/CrossingMinimizers/Crossingminimizer.cpp ./src/CrossingMinimizers/Barycenter.cpp ./src/CrossingMinimizers/Median.cpp ./src/CrossingMinimizers/OptimizedBC.cpp ./src/CrossingMinimizers/OptimizedMedian.cpp ./src/CrossingMinimizers/ParentMinimizer.cpp ./src/CrossingMinimizers/OptimizedBCRight.cpp ./src/CrossingMinimizers/BogoMinimizer.cpp ./src/CrossingMinimizers/BarycenterMed.cpp ./src/CrossingMinimizers/BarycenterRev.cpp ./src/CrossingMinimizers/MedianBary.cpp ./src/CrossingMinimizers/MedianRev.cpp ./src/CrossingMinimizers/Assignment.cpp -o program.o
echo "Program compiled"

# Path to test graphs
testGraphs="./tests/graphs/public"

# Iterate through each graph file
for file in "$testGraphs"/*.gr; do
    if [ -f "$file" ]; then
        echo "$file"
        
        # Run the program with a timeout of 5 minutes
        timeout 300 ./program.o < "$file"
        
        # Check the exit status of the timeout command
        if [ $? -eq 124 ]; then
            echo "Timeout reached for $file, terminating program"
            echo "0, 10, crossingsBefore, duration, numEdges, n0, n1, density, crossingsAfter" >> solvers.csv
            # Add actions to take if the timeout is reached
        fi
        
        echo "============================================="
    fi
done

# Clean up
rm *.o