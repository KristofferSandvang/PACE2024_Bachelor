#include <iostream>
#include <fstream>
#include "Graph.h"
int main() {
    std::ifstream inputFile("tests/graphs/test.gr");
    Graph graph(inputFile, "test");
    inputFile.close();
    graph.countCrossings();
    graph.writeSolution();
    return 0;
}