#include "Vertex.h"
#include <algorithm> 

Vertex::Vertex(int vertexID) {
    Vertex::id = vertexID;
}

Vertex::~Vertex()
{
}

void Vertex::addEdge(Vertex vertex) {
    edges.push_back(vertex);
    std::sort(edges.begin(), edges.end());
}

std::vector<Vertex> Vertex::getEdges() {
    return edges;
}

std::string Vertex::toString() {
    return std::to_string(id);
}

int Vertex::getVertexID() {
    return id;
}

