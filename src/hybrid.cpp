#include "Graph.h"
#include "CrossingMinimizers/Utils.h"
#include "CrossingMinimizers/Barycenter.h"
#include "CrossingMinimizers/Median.h"
#include "CrossingMinimizers/BarycenterMed.h"
#include "CrossingMinimizers/OptimizedBC.h"
#include "CrossingMinimizers/OptimizedMedian.h"
#include "CrossingMinimizers/OptimizedBCRight.h"
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
int timeLimit = 300;  // 5 minutes in seconds
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

bool timeRemaining(std::chrono::steady_clock::time_point start, int seconds) {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    return elapsed < seconds;
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
    if (NumofEdges < 12500) {
        solvers.emplace_back(std::make_unique<OptimizedMedian>(&graph));
        solvers.emplace_back(std::make_unique<MedianRev>(&graph));
        solvers.emplace_back(std::make_unique<BarycenterMed>(&graph));
        solvers.emplace_back(std::make_unique<Median>(&graph));
        solvers.emplace_back(std::make_unique<BarycenterRev>(&graph));
        solvers.emplace_back(std::make_unique<MedianBary>(&graph));
        solvers.emplace_back(std::make_unique<Barycenter>(&graph));

    } else {
        solvers.emplace_back(std::make_unique<MedianRev>(&graph));
        solvers.emplace_back(std::make_unique<BarycenterMed>(&graph));
        solvers.emplace_back(std::make_unique<Median>(&graph));
        solvers.emplace_back(std::make_unique<BarycenterRev>(&graph));
        solvers.emplace_back(std::make_unique<MedianBary>(&graph));
        solvers.emplace_back(std::make_unique<Barycenter>(&graph));
    }

    for (auto& solver : solvers) {
        if (flag || !timeRemaining(start, timeLimit - 20)) break;
        solver->minimizeCrossings();
        if (flag || !timeRemaining(start, timeLimit - 20)) break;

        unsigned long crossings = graph.countCrossingsSweep(graph.getA(), solver->getNewB());
        if (flag || !timeRemaining(start, timeLimit - 20)) break;

        CrossingsAndSolvers.push_back(std::make_pair(crossings, solver.get()));
        if (flag || !timeRemaining(start, timeLimit - 20)) break;
    }

    auto bestSolution = std::min_element(CrossingsAndSolvers.begin(), CrossingsAndSolvers.end(),
                                         [](const auto& a, const auto& b) {
                                             return a.first < b.first;
                                         });

    if (bestSolution != CrossingsAndSolvers.end()) {
        bestSolution->second->writeSolution();
    }

    return 0;
}
