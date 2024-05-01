#include <fstream>
#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include "CrossingMinimizers/OptimizedMedian.h"
#include "CrossingMinimizers/OptimizedBCRight.h"
#include "CrossingMinimizers/ParentMinimizer.h"
#include <algorithm>
#include <csignal>
#include <memory>
#include <iostream>

volatile sig_atomic_t flag = 0;

void signalHandler( int signum ) {
    flag = 1;
}


int main(int argc, char* argv[]) {
    /*     if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << argv[1] << argv[2] << std::endl;
        return 1;
    } */
    std::string inputPath = argv[1];
    std::string outputPath = "solution.sol";

    Graph graph(inputPath);
    std::vector<std::pair<unsigned long, CrossingMinimizer*> > CrossingsAndSolvers;
    // Solvers :
    
    std::vector<std::unique_ptr<CrossingMinimizer>> solvers;
    solvers.emplace_back(std::make_unique<Barycenter>(&graph, outputPath));
    solvers.emplace_back(std::make_unique<Median>(&graph, outputPath));
    solvers.emplace_back(std::make_unique<OptimizedBC>(&graph, outputPath));
    solvers.emplace_back(std::make_unique<OptimizedMedian>(&graph, outputPath));
    solvers.emplace_back(std::make_unique<ParentMinimizer>(&graph, outputPath));
    /* solvers.emplace_back(OptimizedBCRight(&graph, outputPath)); */
    int i = 0;
    
    while (!flag && i < solvers.size())
    {
        solvers.at(i)->minimizeCrossings();
        CrossingsAndSolvers.push_back(std::make_pair(graph.countCrossingsSweep(graph.getA(), solvers.at(i)->getNewB()), solvers[i].get())); 
        i++;
    }
    
    auto bestSolution = std::min_element(CrossingsAndSolvers.begin(), CrossingsAndSolvers.end(), 
    [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    bestSolution->second->writeSolution();

    return 0;
}