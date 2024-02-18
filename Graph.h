#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <vector>
#include <string>
#include "Vertex.h"

const std::string SOLUTION_PATH = "./tests/solutions/";
const std::string GRAPH_PATH = "./tests/graphs/";

class Graph
{
private:
    std::vector<Vertex> A, B;
    int n0, n1, numberOfEdges;
    std::string solutionFileName;

public:
    Graph(std::ifstream& inputFile, std::string solutionFileName);

    void writeSolution();
    int countCrossings();
    void minimizeNumberOfCrossings();
    int findVertexIndex(int vertexID);
    void switchVertices(int v1ID, int v2ID);
    ~Graph();
};

#endif