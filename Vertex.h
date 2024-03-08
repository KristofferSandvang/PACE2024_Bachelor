#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>

class Vertex
{
private:
    int id;
    std::vector<Vertex> edgeTo;
public:
    Vertex(int vertexID);
    ~Vertex();
    void addEdge(Vertex vertex);
    std::vector<Vertex> getEdges();
    std::string toString();
    int getVertexID();
    void switchVertices(Vertex v1, Vertex v2);
    bool operator < (const Vertex& other) const {
        return this->id < other.id;
    }
};

#endif