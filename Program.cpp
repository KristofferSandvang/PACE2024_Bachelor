#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
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

        auto end = std::chrono::system_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration = "<< duration << std::endl;
        return 0;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Invalid filepath" << std::endl;
        return 1;
    }
    
    
}