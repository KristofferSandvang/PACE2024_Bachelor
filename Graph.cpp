#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm> 
#include <utility>
#include <stdexcept>
#include <cmath>
#include <unordered_map>

// Constructor 
Graph::Graph(std::string inputFilename) {
    std::ifstream inputFile(inputFilename);
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line[0] == 'c') {
            continue;
        }
        if (line.substr(0, 5) == "p ocr") {            
            std::sscanf(line.c_str(),"p ocr %d %d %d", &n0, &n1, &numberOfEdges);
            // Ínitialzing the A and B sides of graph
            for (int a_i = 1; a_i <= std::max(n0, n1); a_i++)
            {
                if (a_i <= n0) {
                    A.push_back(Vertex(a_i));
                }
                if (a_i <= n1) {
                    B.push_back(Vertex(a_i + n0));
                }
            }
        }
        // Adds edges to the corresponding vertexs.
        int x, y;
        if (std::sscanf(line.c_str(), "%d %d", &x, &y) == 2)
        {
            // We have to add edges to the leftmost vertex only.
            if (y - n0 < x) {
                B.at(y - n0 - 1).addEdge(Vertex(A.at(x - 1)));
            } else {
                A.at(x - 1).addEdge(Vertex(B.at(y - n0 - 1)));
            }
            // Ensure that the edges list always has the endpoint
            // at the second postion of pair.
            // if (x < y - n0) {
            //     std::swap(x, y);
            // }
            // edges.push_back({x, y});
        }
    }
    inputFile.close();
}

// Destructor 
Graph::~Graph() {
    return;
}

double Graph::calculateGraphDensity() {
    double numerator = numberOfEdges;
    double denominator = n0 * n1;
    return numerator / denominator;
}

int Graph::findVertexIndex(int vertexID) {
    std::vector<Vertex> vertices;
    if (vertexID <= n0) {
        vertices = Graph::A;
    } else {
        vertices = Graph::B;
    }
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.at(i).getVertexID() == vertexID) {
            return i;
        }
    }
    throw std::runtime_error("Vertex (ID = " + std::to_string(vertexID) + ") not found.");
}

int Graph::countCrossings(std::vector<Vertex> A, std::vector<Vertex> B) {
    int crossings = 0;
    for (int i = 0; i < B.size(); i++)
    {
        Vertex currentVertex = B.at(i);
        for (Vertex endOfEdge : currentVertex.getEdges()) {
            // If the edge is a straghtline from either the start or end of B,
            // we can skip it, as it will not have any crossings.
            if (i == 0 && endOfEdge.getVertexID() == 0 || 
                i == B.size() - 1 && endOfEdge.getVertexID() == A.size() ) {
                    continue;
            }
            for (int j = i + 1; j < B.size(); j++)
            {
                Vertex nextVertex = B.at(j);
                for (Vertex v2 : nextVertex.getEdges()) {
                    if (v2.getVertexID() < endOfEdge.getVertexID()) {
                        crossings++;
                    }
                }            
            }
        }
    }
    return crossings;
}

int Graph::countCrossings() {
    return countCrossings(A, B);
}

int Graph::countCrossings(std::string B_file) {
    std::vector<Vertex> newB;
    std::ifstream inputFile(B_file);
    std::string line;
    
    while (std::getline(inputFile, line)) {
        int vertexID;
        if (std::sscanf(line.c_str(),"%d", &vertexID)) {
            newB.push_back(B.at(findVertexIndex(vertexID)));
        }
    }
    return countCrossings(Graph::A, newB);
}

int Graph::countCrossingsSweep(std::vector<Vertex> A, std::vector<Vertex> B) {
    int crossings = 0;
    std::vector<int> UL, LL;
    // last occurence
    std::unordered_map<int, int> last_occurence;
    for (int i = 1; i <= A.size() + B.size(); i++) {
        last_occurence[i] = -1;
    }

    // main loop 
    int AIndex = 0;
    int BIndex = 0;
    for (int iteration = 1; iteration <= A.size() + B.size(); iteration++) {

        // odd = Upper level of graph
        if ((iteration % 2 && AIndex < A.size()) || (B.size() <= BIndex && AIndex < A.size())) {
            int k1 = 0, k2 = 0, k3 = 0;
            int lastOccurrence = last_occurence[A.at(AIndex).getVertexID()];
            if (lastOccurrence != -1) {
                for (int j = 0; j <= lastOccurrence && j < UL.size(); j++) {
                    if (UL.at(j) == A.at(AIndex).getVertexID()) {
                        k1++;
                        k3 += k2;
                        UL.erase(UL.begin() + j);
                        j--;
                        lastOccurrence--;
                    } else {k2++;}
                }
                crossings += (k1 * LL.size()) + k3;
            }
            
            std::vector<Vertex> edges = A.at(AIndex).getEdges();
            for (Vertex edgeEnd : edges) {
                int endpoint = edgeEnd.getVertexID();
                LL.push_back(endpoint);
                last_occurence[endpoint] = LL.size() -1;
            }
            AIndex++;
        }
        // Even = lower level of graph
        else if (iteration % 2 == 0 && BIndex < B.size() || (A.size() <= AIndex && BIndex < B.size())){
            int k1 = 0, k2 = 0, k3 = 0;
            int lastOccurrence = last_occurence[B.at(BIndex).getVertexID()];
            if (lastOccurrence != -1) {
                for (int j = 0; j <= lastOccurrence && j < LL.size(); j++) {
                    if (LL.at(j) == B.at(BIndex).getVertexID()) {
                        k1++;
                        k3 += k2;
                        LL.erase(LL.begin() + j);
                        j--;
                        lastOccurrence--;
                    } else {k2++;}
                }
                crossings += (k1 * UL.size()) + k3;
            }

            std::vector<Vertex> edges = B.at(BIndex).getEdges();
            for (Vertex edgeEnd : edges) {
                int endpoint = edgeEnd.getVertexID();
                UL.push_back(endpoint);
                last_occurence[endpoint] = UL.size() - 1;
            }
            BIndex++;
        }
    }
    return crossings;
}

int Graph::countCrossingsSweep() {
    return countCrossingsSweep(A, B);
}

int Graph::countCrossingsSweep(std::string B_file) {
    std::vector<Vertex> newB;
    std::ifstream inputFile(B_file);
    std::string line;
    
    while (std::getline(inputFile, line)) {
        int vertexID;
        if (std::sscanf(line.c_str(),"%d", &vertexID)) {
            newB.push_back(B.at(findVertexIndex(vertexID)));
        }
    }
    return countCrossingsSweep(Graph::A, newB);
}

void Graph::switchVertices(int v1ID, int v2ID) {
    if (v1ID < n0 || v2ID < n0) {
        throw std::runtime_error("Vertices must be both be in the B graph");
    }
    try {
        int v1_index = Graph::findVertexIndex(v1ID);
        int v2_index = Graph::findVertexIndex(v2ID);
        std::swap(B.at(v1_index), B.at(v2_index));
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return;
    }
}

std::vector<Vertex> Graph::getB() {
    return B;
}

std::vector<Vertex> Graph::getA() {
    return A;
}
