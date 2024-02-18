#include "Vertex.h"


Vertex::Vertex(int vertexID) {
    Vertex::id = vertexID;
}

Vertex::~Vertex()
{
}

void Vertex::addEdge(Vertex vertex) {
    edgeTo.push_back(vertex);
}

std::vector<Vertex> Vertex::getEdges() {
    return edgeTo;
}

std::string Vertex::toString() {
    return std::to_string(id);
}

int Vertex::getVertexID() {
    return id;
}