#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <vector>
#include <string>
#include "Vertex.h"


class Graph
{
private:
    std::vector<Vertex> A, B;
    int n0, n1, numberOfEdges;
    std::string solutionFileName;

public:
    Graph(std::string inputFilename);
    Graph() = default;

    double calculateGraphDensity();
    int countCrossings();
    int countCrossings(std::vector<Vertex> A, std::vector<Vertex> B);
    int countCrossings(std::string B_order);    
    int findVertexIndex(int vertexID);
    void switchVertices(int v1ID, int v2ID);
    std::vector<Vertex> getB();
    ~Graph();
};

#endif
