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
#include "CrossingMinimizers/ParentMinimizer.h"
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

        /* std::ofstream csvFile("results.csv", std::ios::app);

        csvFile << fileName << "," << crossingsS << "," << duration2 << "," << crossingsN << "," << duration << "," << numEdges << "," << numVertices << std::endl;

        csvFile.close(); */
        
        // Barycenter and optimizations:
        start = std::chrono::system_clock::now();
        Barycenter barycenter(&graph, outputFile);
        barycenter.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of barycenter: "<< duration << std::endl; 
        std::cout << "Number of crossings after barycenter: " << graph.countCrossingsSweep(graph.getA(), barycenter.getNewB()) << std::endl;
        
        start = std::chrono::system_clock::now();
        OptimizedBC optimizedBC(&graph, outputFile);
        optimizedBC.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of OptimizedBC: "<< duration << std::endl;
        std::cout << "Number of crossings after OptimizedBC: " << graph.countCrossingsSweep(graph.getA(), optimizedBC.getNewB()) << std::endl;
        
        start = std::chrono::system_clock::now();
        OptimizedBCRight optimizedBCRight(&graph, outputFile);
        optimizedBCRight.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of optimizedBCRight: "<< duration << std::endl;
        optimizedBCRight.writeSolution();
        std::cout << "Number of crossings after optimizedBCRight: " << graph.countCrossingsSweep(graph.getA(), optimizedBCRight.getNewB()) << std::endl;

        //Median and OptimizedMedian
        start = std::chrono::system_clock::now();
        Median Median(&graph, outputFile);
        Median.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of Median: "<< duration << std::endl;
        std::cout << "Number of crossings after Median: " << graph.countCrossingsSweep(graph.getA(), Median.getNewB()) << std::endl;
        
        start = std::chrono::system_clock::now();
        OptimizedMedian optimizedMedian(&graph, outputFile);
        optimizedMedian.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of OptimizedMedian: "<< duration << std::endl;
        std::cout << "Number of crossings after OptimizedMedian: " << graph.countCrossingsSweep(graph.getA(), optimizedMedian.getNewB()) << std::endl;

        // ParentMinimizer
        start = std::chrono::system_clock::now();
        ParentMinimizer parentMinimizer(&graph, outputFile);
        parentMinimizer.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of ParentMinimizer: "<< duration << std::endl;
        std::cout << "Number of crossings after ParentMinimizer: " << graph.countCrossingsSweep(graph.getA(), parentMinimizer.getNewB()) << std::endl;
        parentMinimizer.writeSolution();

        return 0;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Invalid filepath" << std::endl;
        return 1;
    }
}
