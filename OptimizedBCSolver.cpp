#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include <iomanip>
#include <stdexcept>

const std::string INPUT_PATH = "./tests/graphs/public/";
const std::string SOLUTION_PATH = "./tests/solutions/public/";

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
        auto start = std::chrono::system_clock::now();
        std::string inputFile = argv[1];
        std::string fileName = getFileName(inputFile);
        std::string outputFile = SOLUTION_PATH + fileName + ".sol";
        Graph graph(inputFile);
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of file reading "<< duration << std::endl;

        unsigned long int crossingsS = graph.countCrossingsSweep();
        std::cout << "Number of crossings sweep: " << crossingsS << std::endl;
        
        int numVertices = graph.getNumVertices();
        int numEdges = graph.getNumEdges();

        start = std::chrono::system_clock::now();
        OptimizedBC optimizedBC(&graph, outputFile);
        optimizedBC.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of OptimizedBC: "<< duration << std::endl;
        optimizedBC.writeSolution();
        std::cout << "Number of crossings after OptimizedBC sweep: " << graph.countCrossingsSweep(graph.getA(), optimizedBC.getNewB()) << std::endl;
        
        std::ofstream csvFile("solvers.csv", std::ios::app);

        csvFile << fileName << "," << "OptimizedBC" << "," << crossingsS << "," << duration << "," << numEdges << "," << numVertices << "," << graph.calculateGraphDensity() << "," << graph.countCrossingsSweep(graph.getA(), optimizedBC.getNewB()) << std::endl;

        csvFile.close();
        return 0;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Invalid filepath" << std::endl;
        return 1;
    }
}
