#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>

class Vertex
{
private:
    int id;
    int degree;
    std::vector<Vertex*> edges;
public:
    Vertex(int vertexID);
    Vertex() : id(0), degree(0) {}
    ~Vertex();
    void addEdge(Vertex* vertex);
    std::vector<Vertex*> getEdges();
    std::string toString();
    void updateEdgeOrder(std::vector<Vertex>* newBorder);
    int getVertexID();
    int getVertexDegree();
    bool operator < (const Vertex& other) const {
        return this->id < other.id;
    }
};

#endif
