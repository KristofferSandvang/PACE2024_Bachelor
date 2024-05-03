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
    Graph(std::istream& inputStream);
    Graph() = default;

    long double calculateGraphDensity();
    unsigned long int countCrossings();
    unsigned long int countCrossings(std::vector<Vertex> A, std::vector<Vertex> B);
    unsigned long int countCrossings(std::string B_file);
    unsigned long int countCrossingsSweep();
    unsigned long int countCrossingsSweep(std::string B_file);
    unsigned long int countCrossingsSweep(std::vector<Vertex>* A, std::vector<Vertex>* B);    
    unsigned long int findVertexIndex(int vertexID);
    static int findVertexByID(std::vector<Vertex>* vertices, int vertexID);
    void switchVertices(int v1ID, int v2ID);
    std::vector<Vertex>* getB();
    std::vector<Vertex>* getA();
    int getNumVertices();
    int getNumEdges();
    int getn0();
    int getn1();
    ~Graph();
};

#endif
