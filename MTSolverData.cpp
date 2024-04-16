#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include "CrossingMinimizers/OptimizedMedian.h"
#include "CrossingMinimizers/OptimizedBCRight.h"
#include "CrossingMinimizers/ParentMinimizer.h"
#include "CrossingMinimizers/BogoMinimizer.h"
#include <iomanip>
#include <stdexcept>


const std::string INPUT_PATH = "./tests/graphs/";
const std::string SOLUTION_PATH = "./tests/solutions/";
const int NUM_OF_MINIMIZERS = 7;
std::mutex mutex; 

std::string getFileName(std::string filePath) {
    size_t prefixPath = filePath.find(INPUT_PATH);

    if (prefixPath != std::string::npos) {
        return filePath.substr(INPUT_PATH.size(), filePath.length() - INPUT_PATH.size() - 3);
    }
    throw std::invalid_argument("The path does not contain the input File");
}


void threadFunction(int ID, Graph* graph, std::string outputFile, 
                    std::unordered_map<int, unsigned long int>& crossings, 
                    std::unordered_map<int, double>& durations){
    double duration;
    unsigned long int crossingAfter;
    switch (ID) {
        case 0: 
        {
            auto start = std::chrono::system_clock::now();
            Barycenter barycenter(graph, outputFile);
            barycenter.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), barycenter.getNewB());

            break;
        }
        case 1:
        {
            auto start = std::chrono::system_clock::now();
            Median median(graph, outputFile);
            median.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), median.getNewB());

            break;
        }
        case 2:
        {
            auto start = std::chrono::system_clock::now();
            OptimizedBC optimizedBC(graph, outputFile);
            optimizedBC.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), optimizedBC.getNewB());
        
            break;
        }
        case 3:
        {
           auto start = std::chrono::system_clock::now();
            OptimizedBCRight optimizedBCRight(graph, outputFile);
            optimizedBCRight.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), optimizedBCRight.getNewB());

            break;
        }
        case 4:
        {
            auto start = std::chrono::system_clock::now();
            OptimizedMedian optimizedMedian(graph, outputFile);
            optimizedMedian.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), optimizedMedian.getNewB());

            break;
        }
        case 5:
        {
            auto start = std::chrono::system_clock::now();
            ParentMinimizer parentMinimizer(graph, outputFile);
            parentMinimizer.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), parentMinimizer.getNewB());
            
            break;
        }
        case 6:
        {
            auto start = std::chrono::system_clock::now();
            BogoMinimizer bogoMinimizer(graph, outputFile);
            bogoMinimizer.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), bogoMinimizer.getNewB());
            
            break;
        }
        default:
            return;
    }
    mutex.lock();

    crossings[ID] = crossingAfter;
    durations[ID] = duration;

    mutex.unlock();
}


int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Too many arguments given. " << std::endl;
        exit(1);
    }
    try {   
        std::unordered_map<int, unsigned long int> crossingsAfter;
        std::unordered_map<int, double> durations;
        auto start = std::chrono::system_clock::now();
        std::string inputFile = argv[1];
        std::string fileName = getFileName(inputFile);
        std::string outputFile = SOLUTION_PATH + fileName + ".sol";
        Graph graph(inputFile);
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        std::cout << "Duration of file reading "<< duration << std::endl;

        int numVertices = graph.getNumVertices();
        int numEdges = graph.getNumEdges();
        long double density = graph.calculateGraphDensity();
        long unsigned int crossingsBefore = graph.countCrossingsSweep();
        std::cout << "Number of crossings before: " << crossingsBefore << std::endl;

        std::vector<std::thread> threads;

        for (int i = 0; i < NUM_OF_MINIMIZERS; i++)
        {
            threads.push_back(std::thread(threadFunction, i, &graph, outputFile, std::ref(crossingsAfter), std::ref(durations)));
        }
        

        for (auto& thread : threads) {
            thread.join();
        }


        std::ofstream csvFile("solvers.csv", std::ios::app);


        for (int i = 0; i < NUM_OF_MINIMIZERS; i++)
        {
            csvFile << fileName << "," << i << "," << crossingsBefore << "," << durations[i] << "," << numEdges << "," << numVertices << "," << density << "," << crossingsAfter[i] << std::endl;
        }
        csvFile.close();

    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid filepath" << std::endl;
        return 1;
    }
}