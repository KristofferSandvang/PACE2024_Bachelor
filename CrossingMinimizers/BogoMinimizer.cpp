#include "BogoMinimizer.h"
#include <stdlib.h>
#include <iostream>
BogoMinimizer::BogoMinimizer(Graph* graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName) {
}

void BogoMinimizer::minimizeCrossings() {
    for (int i = 0; i < B.size(); i++)
    {
        std::swap(B.at(i), B.at(rand() % B.size()));
    }
}

BogoMinimizer::~BogoMinimizer() {}