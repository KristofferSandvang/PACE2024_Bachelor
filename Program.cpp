#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"
int main() {
    auto start = std::chrono::system_clock::now();
    std::ifstream inputFile("tests/graphs/test.gr");
    Graph graph(inputFile, "test");

    graph.minimizeNumberOfCrossings();
    //graph.calculateCrossingNumberMatrix();
    graph.writeSolution();
    std::cout << graph.countCrossings() << std::endl;
    inputFile.close();
    auto end = std::chrono::system_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    std::cout << duration << std::endl;
    return 0;
}