#include "Vertex.h"
#include <algorithm> 
#include "Graph.h"

Vertex::Vertex(int vertexID) {
    Vertex::id = vertexID;
    Vertex::degree = 0;
}

Vertex::~Vertex() {}

void Vertex::addEdge(Vertex* vertex) {
    edges.push_back(vertex);
    std::sort(edges.begin(), edges.end());
    Vertex::degree++;
}

void Vertex::updateEdgeOrder(std::vector<Vertex>* newBOrder) {
    // Sort the edges based on their position in the new border.
    std::vector<std::pair < Vertex*, int> > indices;
    int numOfEdges = edges.size();
    for (Vertex* edge : edges) {
        int newIndex = Graph::findVertexByID(newBOrder, edge->getVertexID());
        indices.push_back(std::make_pair(edge, newIndex));
    }
    
    auto comparator = [](const std::pair<Vertex*, int>& pair1, const std::pair<Vertex*, int>& pair2) {
            return pair1.second < pair2.second;
    };

    std::sort(indices.begin(), indices.end(), comparator);
    for (int i = 0; i < indices.size(); i++) {
        edges.at(i) = indices.at(i).first;
    }

}

std::vector<Vertex*> Vertex::getEdges() {
    return edges;
}

std::string Vertex::toString() {
    return std::to_string(id);
}

int Vertex::getVertexID() {
    return id;
}

int Vertex::getVertexDegree() {
    return degree;
}
