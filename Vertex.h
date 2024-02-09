#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>

class Vertex
{
private:
    int vertexNumber;
    std::vector<int> edgeTo;
public:
    Vertex(int vertexNumber);
    ~Vertex();
    void addEdge(int vertex);
    std::vector<int> getEdges();
    std::string toString();
};

#endif