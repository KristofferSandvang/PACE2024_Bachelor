#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include <iomanip>


const std::string SOLUTION_PATH = "./tests/solutions/";


int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Too many arguments given. " << std::endl;
        exit(1);
    }
    std::string inputFile = argv[1];
    std::string outputFile = SOLUTION_PATH + "test.sol";

    
    auto start = std::chrono::system_clock::now();
    Graph graph(inputFile);
    std::cout << "Number of crossings before: " << graph.countCrossings() << std::endl;

    std::cout << "Graph Density = " << std::setprecision(2) << graph.calculateGraphDensity() << std::endl;
    Barycenter barycenter(graph, outputFile); 
    barycenter.minimizeCrossings();

    std::cout << "Number of crossings after barycenter: " << graph.countCrossings(outputFile) << std::endl;

    Median median(graph, outputFile);
    median.minimizeCrossings();

    std::cout << "Number of crossings after median: " << graph.countCrossings(outputFile) << std::endl;

    OptimizedBC optimizedBC(graph, outputFile);
    optimizedBC.minimizeCrossings();

    std::cout << "Number of crossings after optimizedBC: " << graph.countCrossings(outputFile) << std::endl;

    auto end = std::chrono::system_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    std::cout << "Duration = "<< duration << std::endl;
    return 0;
}