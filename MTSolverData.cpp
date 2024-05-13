#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include "src/Graph.h"
#include "src/CrossingMinimizers/Barycenter.h"
#include "src/CrossingMinimizers/Median.h"
#include "src/CrossingMinimizers/OptimizedBC.h"
#include "src/CrossingMinimizers/OptimizedMedian.h"
#include "src/CrossingMinimizers/OptimizedBCRight.h"
#include "src/CrossingMinimizers/ParentMinimizer.h"
#include "src/CrossingMinimizers/BogoMinimizer.h"
#include <iomanip>
#include <stdexcept>
#include <unordered_map>


const std::string INPUT_PATH = "./tests/graphs/public/";
const std::string SOLUTION_PATH = "./tests/solutions/public";
const int NUM_OF_MINIMIZERS = 7;
std::mutex mutex; 


void threadFunction(int ID, Graph* graph, 
                    std::unordered_map<int, unsigned long int>& crossings, 
                    std::unordered_map<int, double>& durations){
    double duration;
    unsigned long int crossingAfter;
    switch (ID) {
        case 0: 
        {
            auto start = std::chrono::system_clock::now();
            Barycenter barycenter(graph);
            barycenter.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), barycenter.getNewB());

            break;
        }
        case 1:
        {
            auto start = std::chrono::system_clock::now();
            Median median(graph);
            median.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), median.getNewB());

            break;
        }
        case 2:
        {
            auto start = std::chrono::system_clock::now();
            OptimizedBC optimizedBC(graph);
            optimizedBC.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), optimizedBC.getNewB());
        
            break;
        }
        case 3:
        {
            auto start = std::chrono::system_clock::now();
            OptimizedBCRight optimizedBCRight(graph);
            optimizedBCRight.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), optimizedBCRight.getNewB());

            break;
        }
        case 4:
        {
            auto start = std::chrono::system_clock::now();
            OptimizedMedian optimizedMedian(graph);
            optimizedMedian.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), optimizedMedian.getNewB());

            break;
        }
        case 5:
        {   
            auto start = std::chrono::system_clock::now();
            ParentMinimizer parentMinimizer(graph);
            parentMinimizer.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), parentMinimizer.getNewB());
            
            break;
        }
        case 6:
        {
            auto start = std::chrono::system_clock::now();
            BogoMinimizer bogoMinimizer(graph);
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
    std::unordered_map<int, unsigned long int> crossingsAfter;
    std::unordered_map<int, double> durations;
    auto start = std::chrono::system_clock::now();
    Graph graph(std::cin);
    std::cout << "Graph created" << std::endl;
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
        threads.push_back(std::thread(threadFunction, i, &graph, std::ref(crossingsAfter), std::ref(durations)));
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    std::ofstream csvFile("solvers.csv", std::ios::app);
    for (int i = 0; i < NUM_OF_MINIMIZERS; i++)
    {
        csvFile << "," << i << "," << crossingsBefore << "," << durations[i] << "," << numEdges << "," << graph.getn0() << graph.getn1() << "," << density << "," << crossingsAfter[i] << std::endl;
    }
    csvFile.close();
} 
