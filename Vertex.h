#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>

class Vertex
{
private:
    int id;
    std::vector<Vertex*> edges;
public:
    Vertex(int vertexID);
    ~Vertex();
    void addEdge(Vertex* vertex);
    std::vector<Vertex*> getEdges();
    std::string toString();
    void updateEdgeOrder(std::vector<Vertex>* newBorder);
    int getVertexID();
    bool operator < (const Vertex& other) const {
        return this->id < other.id;
    }
};

#endif