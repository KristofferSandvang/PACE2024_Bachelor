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
        
        std::ofstream csvFile("results.csv", std::ios::app);

        csvFile << fileName << "," << crossingsS << "," << duration2 << "," << crossingsN << "," << duration << "," << numEdges << "," << numVertices << std::endl;

        csvFile.close();
        
        /* start = std::chrono::system_clock::now();
        Barycenter Barycenter(&graph, outputFile);
        Barycenter.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of Barycenter: "<< duration << std::endl; 
        std::cout << "Number of crossings after Barycenter sweep: " << graph.countCrossingsSweep(outputFile) << std::endl;
        
        
        start = std::chrono::system_clock::now();
        OptimizedBC OptimizedBC(&graph, outputFile);
        OptimizedBC.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of OptimizedBC: "<< duration << std::endl;
        std::cout << "Number of crossings after OptimizedBC sweep: " << graph.countCrossingsSweep(outputFile) << std::endl;
        
        start = std::chrono::system_clock::now();
        OptimizedBCRight OptimizedBCRight(&graph, outputFile);
        OptimizedBCRight.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of OptimizedBCRight: "<< duration << std::endl;
        std::cout << "Number of crossings after OptimizedBCRight sweep: " << graph.countCrossingsSweep(outputFile) << std::endl; */

        /* //Median and OptimizedMedian
        start = std::chrono::system_clock::now();
        Median Median(&graph, outputFile);
        Median.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of Median: "<< duration << std::endl;
        std::cout << "Number of crossings after Median sweep: " << graph.countCrossingsSweep(outputFile) << std::endl;

        start = std::chrono::system_clock::now();
        OptimizedMedian OptimizedMedian(&graph, outputFile);
        OptimizedMedian.minimizeCrossings();
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of OptimizedMedian: "<< duration << std::endl;
        std::cout << "Number of crossings after OptimizedMedian sweep: " << graph.countCrossingsSweep(outputFile) << std::endl; */
        return 0;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Invalid filepath" << std::endl;
        return 1;
    }
}
