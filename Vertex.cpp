#include "Vertex.h"


Vertex::Vertex(int vertexNumber) {
    Vertex::vertexNumber = vertexNumber;
}

Vertex::~Vertex()
{
}

void Vertex::addEdge(int vertex) {
    edgeTo.push_back(vertex);
}

std::vector<int> Vertex::getEdges() {
    return edgeTo;
}

std::string Vertex::toString() {
    return std::to_string(vertexNumber);
}