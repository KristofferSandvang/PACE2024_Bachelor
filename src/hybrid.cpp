#include "Graph.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
#include "CrossingMinimizers/BarycenterMed.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include "CrossingMinimizers/OptimizedMedian.h"
#include "CrossingMinimizers/ParentMinimizer.h"
#include "CrossingMinimizers/MedianBary.h"
#include "CrossingMinimizers/BarycenterRev.h"
#include "CrossingMinimizers/MedianRev.h"
#include <algorithm>
#include <csignal>
#include <memory>
#include <iostream>
#include <chrono>

volatile sig_atomic_t flag = 0;
std::chrono::steady_clock::time_point start;
int timeLimit = 300;
int minRemaingTime = 20;
std::vector<std::pair<unsigned long, CrossingMinimizer*>>* globalSolutions = nullptr;

void signalHandler(int signum) {
    flag = 1;
    if (globalSolutions != nullptr) {
        auto bestSolution = std::min_element(globalSolutions->begin(), globalSolutions->end(),
                                             [](const auto& a, const auto& b) {
                                                 return a.first < b.first;
                                             });
        if (bestSolution != globalSolutions->end()) {
            bestSolution->second->writeSolution();
        }
        exit(0);
    }
}

bool timeRemaining(std::chrono::steady_clock::time_point start) {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    return  minRemaingTime < (timeLimit - elapsed);
}

int main() {
    start = std::chrono::steady_clock::now();
    signal(SIGTERM, signalHandler);
    std::vector<std::pair<unsigned long, CrossingMinimizer*>> CrossingsAndSolvers;
    globalSolutions = &CrossingsAndSolvers;
    Graph graph(std::cin);

    int NumofVertices = graph.getNumVertices();
    long double NumofEdges = graph.getNumEdges();
    long double n0 = graph.getn0();
    long double n1 = graph.getn1();
    long double density = NumofEdges / (n0 * n1);

    std::vector<std::unique_ptr<CrossingMinimizer>> solvers;
    if (NumofEdges < 13000 && NumofVertices < 13500) {
        solvers.emplace_back(std::make_unique<OptimizedMedian>(&graph));
        solvers.emplace_back(std::make_unique<OptimizedBC>(&graph));
    }
    solvers.emplace_back(std::make_unique<MedianBary>(&graph));
    solvers.emplace_back(std::make_unique<Barycenter>(&graph));
    solvers.emplace_back(std::make_unique<BarycenterMed>(&graph));
    solvers.emplace_back(std::make_unique<Median>(&graph));
    solvers.emplace_back(std::make_unique<BarycenterRev>(&graph));
    solvers.emplace_back(std::make_unique<MedianRev>(&graph));
    // focus on barycenter first
    if (0.003 < density &&  density < 0.005) {
        std::swap(solvers[0], solvers[1]);
    }

    for (auto& solver : solvers) {
        if (flag || !timeRemaining(start)) break;
        solver->minimizeCrossings();
        if (flag || !timeRemaining(start)) break;
        unsigned long crossings = graph.countCrossingsSweep(graph.getA(), solver->getNewB());
        CrossingsAndSolvers.push_back(std::make_pair(crossings, solver.get()));
        if (crossings == 0){
            solver->writeSolution();
            return 0;
        }
    }

    if (flag) {
        return 0;
    }
    auto bestSolution = std::min_element(CrossingsAndSolvers.begin(), CrossingsAndSolvers.end(),
                                         [](const auto& a, const auto& b) {
                                             return a.first < b.first;
                                         });
    if (bestSolution != CrossingsAndSolvers.end() && !flag) {
        bestSolution->second->writeSolution();
    }

    return 0;
}
