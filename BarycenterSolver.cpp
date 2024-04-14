#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include <iomanip>
#include <stdexcept>

const std::string INPUT_PATH = "./tests/graphs/medium/";
const std::string SOLUTION_PATH = "./tests/solutions/medium/";

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

        start = std::chrono::system_clock::now();
        int crossingsN = graph.countCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of naive: "<< duration << std::endl;
        std::cout << "Number of crossings naive: " << crossingsN << std::endl;

        start = std::chrono::system_clock::now();
        int crossingsS = graph.countCrossingsSweep();
        end = std::chrono::system_clock::now();
        double duration2 = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of sweep: "<< duration2 << std::endl;
        std::cout << "Number of crossings sweep: " << crossingsS << std::endl;
        
        int numVertices = graph.getNumVertices();
        int numEdges = graph.getNumEdges();

        start = std::chrono::system_clock::now();
        Barycenter barycenter(&graph, outputFile);
        barycenter.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of barycenter: "<< duration << std::endl; 
        barycenter.writeSolution();
        std::cout << "Number of crossings after barycenter sweep adresser: " << graph.countCrossingsSweep(graph.getA(), barycenter.getNewB()) << std::endl;

        std::ofstream csvFile("solvers.csv", std::ios::app);

        csvFile << fileName << "," << "Barycenter" << "," << crossingsS << "," << duration2 << "," << crossingsN << "," << duration << "," << numEdges << "," << numVertices << "," << graph.countCrossingsSweep(graph.getA(), barycenter.getNewB()) << std::endl;

        csvFile.close();
        return 0;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Invalid filepath" << std::endl;
        return 1;
    }
}
