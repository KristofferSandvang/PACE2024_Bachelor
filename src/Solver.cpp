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


int main() {
    signal(SIGTERM, signalHandler);
    std::vector<std::pair<unsigned long, CrossingMinimizer*> > CrossingsAndSolvers;
    Graph graph(std::cin);

    // Solvers :
    std::vector<std::unique_ptr<CrossingMinimizer>> solvers;
    solvers.emplace_back(std::make_unique<Barycenter>(&graph));
    solvers.emplace_back(std::make_unique<Median>(&graph));
    solvers.emplace_back(std::make_unique<OptimizedBC>(&graph));
    solvers.emplace_back(std::make_unique<OptimizedMedian>(&graph));
    solvers.emplace_back(std::make_unique<ParentMinimizer>(&graph));
    /* solvers.emplace_back(OptimizedBCRight(&graph, outputPath)); */
    
    for (int i = 0; i < solvers.size(); i++)
    {
        solvers.at(i)->minimizeCrossings();
        if (flag) {
            break;
        }
        unsigned long int crossings = graph.countCrossingsSweep(graph.getA(), solvers.at(i)->getNewB());
        CrossingsAndSolvers.push_back(std::make_pair(crossings, solvers[i].get())); 
        if (flag) {
            break;
        }
        if (crossings == 0) {
            break;
        }
    }

    auto bestSolution = std::min_element(CrossingsAndSolvers.begin(), CrossingsAndSolvers.end(), 
    [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    bestSolution->second->writeSolution();

    return 0;
}