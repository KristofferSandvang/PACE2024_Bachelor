#include "CrossingMinimizer.h"
#include <iostream>

CrossingMinimizer::CrossingMinimizer(Graph graph, std::string solutionFileName) {
    CrossingMinimizer::graph = graph;
    CrossingMinimizer::solutionFileName = solutionFileName;
}

void CrossingMinimizer::writeSolution(std::vector<Vertex> B) {
    std::ofstream solutionFile(solutionFileName);
    if (!solutionFile.is_open()) {
        std::cout << "Unable to write to " << solutionFileName << std::endl;
        return;
    }
    for (auto vertex: B) {
        solutionFile << vertex.toString() << std::endl;
    }

    solutionFile.close();
    return;
}

// Destructor 
CrossingMinimizer::~CrossingMinimizer() {
    return;
}