#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include "CrossingMinimizers/Split.h"
#include "CrossingMinimizers/OptimizedMedian.h"
#include "CrossingMinimizers/OptimizedBCRight.h"
#include <iomanip>
#include <stdexcept>

const std::string INPUT_PATH = "./tests/graphs/";
const std::string SOLUTION_PATH = "./tests/solutions/";

std::string getFileName(std::string filePath) {
    size_t prefixPath = filePath.find(INPUT_PATH);

    if (prefixPath != std::string::npos) {
        return filePath.substr(INPUT_PATH.size(), filePath.length() - INPUT_PATH.size() - 3);
    }
    throw std::invalid_argument("The path does not contain the input File");
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Too many arguments given. " << std::endl;
        exit(1);
    }
    try
    {   

        std::string inputFile = argv[1];
        std::string fileName = getFileName(inputFile);
        std::string outputFile = SOLUTION_PATH + fileName + ".sol";

        Graph graph(inputFile);

        auto start = std::chrono::system_clock::now();
        std::cout << "Number of crossings naive: " << graph.countCrossings() << std::endl;
        auto end = std::chrono::system_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of naive count: "<< duration << std::endl;

        start = std::chrono::system_clock::now();
        std::cout << "Number of crossings sweep: " << graph.countCrossingsSweep() << std::endl;
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of sweep: "<< duration << std::endl;

        std::cout << "Graph Density = " << std::setprecision(2) << graph.calculateGraphDensity() << std::endl;
        
        
        /* start = std::chrono::system_clock::now();
        Median median(graph, outputFile);
        median.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of median: "<< duration << std::endl;
        std::cout << "Number of crossings after median: " << graph.countCrossingsSweep(outputFile) << std::endl;
        std::cout << "Number of crossings after median: " << graph.countCrossings(outputFile) << std::endl;

        start = std::chrono::system_clock::now();
        OptimizedMedian optimizedMedian(graph, outputFile);
        optimizedMedian.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of optimizedMedian: "<< duration << std::endl;
        std::cout << "Number of crossings after optimizedMedian: " << graph.countCrossingsSweep(outputFile) << std::endl;
        
        start = std::chrono::system_clock::now();
        Barycenter barycenter(graph, outputFile); 
        barycenter.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of barycenter: "<< duration << std::endl;
        std::cout << "Number of crossings after barycenter: " << graph.countCrossingsSweep(outputFile) << std::endl; */

        start = std::chrono::system_clock::now();
        OptimizedBC optimizedBC(graph, outputFile);
        optimizedBC.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of optimizedBC: "<< duration << std::endl;
        std::cout << "Number of crossings after optimizedBC: " << graph.countCrossingsSweep(outputFile) << std::endl;
        std::cout << "Number of crossings after optimizedBC: " << graph.countCrossings(outputFile) << std::endl;

        start = std::chrono::system_clock::now();
        OptimizedBCRight optimizedBCRight(graph, outputFile);
        optimizedBCRight.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of optimizedBCRight: "<< duration << std::endl;
        std::cout << "Number of crossings after optimizedBCRight: " << graph.countCrossingsSweep(outputFile) << std::endl;
        std::cout << "Number of crossings after optimizedBCRight: " << graph.countCrossings(outputFile) << std::endl;
        return 0;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Invalid filepath" << std::endl;
        return 1;
    }
}
