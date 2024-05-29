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
#include "src/CrossingMinimizers/ParentMinimizer.h"
#include "src/CrossingMinimizers/BogoMinimizer.h"
#include "src/CrossingMinimizers/MedianBary.h"
#include "src/CrossingMinimizers/MedianRev.h"
#include "src/CrossingMinimizers/BarycenterMed.h"
#include "src/CrossingMinimizers/BarycenterRev.h"
#include "src/CrossingMinimizers/Assignment.h"
#include <iomanip>
#include <stdexcept>
#include <unordered_map>


const std::string INPUT_PATH = "./tests/graphs/Ass/";
const std::string SOLUTION_PATH = "./tests/solutions/Ass/";
const int NUM_OF_MINIMIZERS = 11;
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
            OptimizedMedian optimizedMedian(graph);
            optimizedMedian.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), optimizedMedian.getNewB());

            break;
        }
        case 4:
        {   
            auto start = std::chrono::system_clock::now();
            ParentMinimizer parentMinimizer(graph);
            parentMinimizer.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), parentMinimizer.getNewB());
            
            break;
        }
        case 5:
        {
            auto start = std::chrono::system_clock::now();
            BogoMinimizer bogoMinimizer(graph);
            bogoMinimizer.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), bogoMinimizer.getNewB());
            
            break;
        }
        case 6:
        {
            auto start = std::chrono::system_clock::now();
            MedianBary medianBary(graph);
            medianBary.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), medianBary.getNewB());
            
            break;
        }
        case 7:
        {
            auto start = std::chrono::system_clock::now();
            MedianRev medianRev(graph);
            medianRev.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), medianRev.getNewB());
            
            break;
        }
        case 8:
        {
            auto start = std::chrono::system_clock::now();
            BarycenterMed barycenterMed(graph);
            barycenterMed.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), barycenterMed.getNewB());
            
            break;
        }
        case 9:
        {
            auto start = std::chrono::system_clock::now();
            BarycenterRev barycenterRev(graph);
            barycenterRev.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), barycenterRev.getNewB());
            break;
        }
        case 10:
        {
            auto start = std::chrono::system_clock::now();
            Assignment assignment(graph);
            assignment.minimizeCrossings();
            auto end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            crossingAfter = graph->countCrossingsSweep(graph->getA(), assignment.getNewB());
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
    std::string filename = argv[1];
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

    std::ofstream csvFile("Temp.csv", std::ios::app);
    if (!csvFile.is_open()) {
        std::cout << "Error :()" << std::endl;
    }

    for (int i = 0; i < NUM_OF_MINIMIZERS; i++)
    {
        csvFile << filename << "," << i << "," << crossingsBefore << "," << durations[i] << "," << numEdges << "," << graph.getn0() << "," <<graph.getn1() << "," << density << "," << crossingsAfter[i] << std::endl;
    }
    csvFile.close();
} 
