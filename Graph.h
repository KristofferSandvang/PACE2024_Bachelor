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
    std::vector<std::pair<int, int> > edges;

public:
    Graph(std::string inputFilename);
    Graph() = default;

    double calculateGraphDensity();
    int countCrossings();
    int countCrossings(std::vector<Vertex> A, std::vector<Vertex> B);
    int countCrossings(std::string B_file);
    int countCrossingsSweep();
    int countCrossingsSweep(std::string B_file);
    int countCrossingsSweep(std::vector<Vertex>* A, std::vector<Vertex>* B);    
    int findVertexIndex(int vertexID);
    static int findVertexByID(std::vector<Vertex>* vertices, int vertexID);
    void switchVertices(int v1ID, int v2ID);
    std::vector<Vertex>* getB();
    std::vector<Vertex>* getA();
    int getNumVertices();
    int getNumEdges();
    ~Graph();
};

#endif
