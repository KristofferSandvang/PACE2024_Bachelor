#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm> 
#include <utility>
#include <stdexcept>
#include <cmath>
#include <unordered_map>

// Constructor 
Graph::Graph(std::istream& inputStream) {
    std::string line;
    while (std::getline(inputStream, line))
    {
        if (line[0] == 'c') {
            continue;
        }
        if (line.compare(0, 5, "p ocr") == 0) {            
            std::sscanf(line.c_str(),"p ocr %d %d %d", &n0, &n1, &numberOfEdges);
            A.reserve(n0);
            B.reserve(n1);
            // Ínitialzing the A and B sides of graph
            for (int a_i = 1; a_i <= std::max(n0, n1); a_i++)
            {
                if (a_i <= n0) {
                    A.emplace_back(Vertex(a_i));
                }
                if (a_i <= n1) {
                    B.emplace_back(Vertex(a_i + n0));
                }
            }
        }
        // Adds edges to the corresponding vertexs.
        int x, y;
        if (std::sscanf(line.c_str(), "%d %d", &x, &y) == 2)
        {
            B.at(y - n0 - 1).addEdge(&A.at(x - 1));
            A.at(x - 1).addEdge(&B.at(y - n0 - 1));
            edges.push_back(std::make_pair(x, y));
        }
    }
}

// Destructor 
Graph::~Graph() {
    return;
}

long double Graph::calculateGraphDensity() {
    long double numerator = numberOfEdges;
    long double denominator = n0 * n1;
    return numerator / denominator;
}

unsigned long int Graph::findVertexIndex(int vertexID) {
    std::vector<Vertex>* vertices;
    if (vertexID <= n0) {
        vertices = &A;
    } else {
        vertices = &B;
    }
    for (int i = 0; i < vertices->size(); i++)
    {
        if (vertices->at(i).getVertexID() == vertexID) {
            return i;
        }
    }
    throw std::runtime_error("Vertex (ID = " + std::to_string(vertexID) + ") not found.");
}

unsigned long Graph::countCrossings(std::vector<Vertex> A, std::vector<Vertex> B) {
    unsigned long int crossings = 0;
    for (int i = 0; i < B.size(); i++)
    {
        Vertex currentVertex = B.at(i);
        for (Vertex* endOfEdge : currentVertex.getEdges()) {
            // If the edge is a straghtline from either the start or end of B,
            // we can skip it, as it will not have any crossings.
            if (i == 0 && endOfEdge->getVertexID() == 0 || 
                i == B.size() - 1 && endOfEdge->getVertexID() == A.size() ) {
                    continue;
            }
            for (int j = i + 1; j < B.size(); j++)
            {
                Vertex nextVertex = B.at(j);
                for (Vertex* v2 : nextVertex.getEdges()) {
                    if (v2->getVertexID() < endOfEdge->getVertexID()) {
                        crossings++;
                    }
                }            
            }
        }
    }
    return crossings;
}

unsigned long int Graph::countCrossings() {
    return countCrossings(A, B);
}

unsigned long int Graph::countCrossings(std::string B_file) {
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

int Graph::findVertexByID(std::vector<Vertex>* vertices, int vertexID) {
    for (int i = 0; i < vertices->size(); i++)
    {
        if (vertices->at(i).getVertexID() == vertexID)
        {
            return i;
        }
    }
    return -1;
}

unsigned long int Graph::countCrossingsSweep(std::vector<Vertex>* A, std::vector<Vertex>* B) {
    // Skal lige opdatere B edges hvis B ikke er lig med graph.B
    if (B != &this->B) {
        for (int i = 0; i < n0; i++) {
            this->A.at(i).updateEdgeOrder(B);
        }
    }
    unsigned long int crossings = 0;
    std::vector<int> UL, LL;
    UL.reserve(A->size());
    LL.reserve(B->size());
    // last occurence
    std::unordered_map<int, int> last_occurence;
    for (int i = 1; i <= A->size() + B->size(); i++) {
        last_occurence[i] = -1;
    }

    // main loop 
    int AIndex = 0;
    int BIndex = 0;
    for (int iteration = 1; iteration <= A->size() + B->size() + 1; iteration++) {
        // odd = Upper level of graph
        if ((iteration % 2 && AIndex < A->size()) || (B->size() <= BIndex && AIndex < A->size())) {
            int k1 = 0, k2 = 0, k3 = 0;
            int lastOccurrence = last_occurence[A->at(AIndex).getVertexID()];
            if (lastOccurrence != -1) {
                for (int j = 0; j <= lastOccurrence && j < UL.size(); j++) {
                    if (UL.at(j) == A->at(AIndex).getVertexID()) {
                        k1++;
                        k3 += k2;
                        UL.erase(UL.begin() + j);
                        j--;
                    } else {k2++;}
                }
                crossings += (k1 * LL.size()) + k3;
            }
            
            const std::vector<Vertex*>& edges = A->at(AIndex).getEdges();
            for (Vertex* edgeEnd : edges) {
                int endpoint = edgeEnd->getVertexID();
                // Have to search B array to find index of the endpoint, as it can change.
                int endpointX = findVertexByID(B, endpoint);
                if (AIndex <= endpointX && endpointX != -1) {
                    LL.push_back(endpoint);
                    last_occurence[endpoint] = LL.size() -1;
                }
            }
            AIndex++;
        }
        // Even = lower level of graph
        else if (iteration % 2 == 0 && BIndex < B->size() || (A->size() <= AIndex && BIndex < B->size())){
            int k1 = 0, k2 = 0, k3 = 0;
            int lastOccurrence = last_occurence[B->at(BIndex).getVertexID()];
            if (lastOccurrence != -1) {
                for (int j = 0; j <= lastOccurrence && j < LL.size(); j++) {
                    if (LL.at(j) == B->at(BIndex).getVertexID()) {
                        k1++;
                        k3 += k2;
                        LL.erase(LL.begin() + j);
                        j--;
                    } else {k2++;}
                }
                crossings += (k1 * UL.size()) + k3;
            }

            const std::vector<Vertex*>& edges = B->at(BIndex).getEdges();
            for (Vertex* edgeEnd : edges) {
                int endpoint = edgeEnd->getVertexID();
                if (BIndex + 1 < endpoint) {
                    UL.push_back(endpoint);
                    last_occurence[endpoint] = UL.size() - 1;
                }
            }
            BIndex++;
        }
    }
    return crossings;
}


unsigned long int Graph::countCrossingsSweep() {
    return countCrossingsSweep(&A, &B);
}

unsigned long int Graph::countCrossingsSweep(std::string B_file) {
    std::vector<Vertex> newB;
    std::ifstream inputFile(B_file);
    std::string line;
    
    while (std::getline(inputFile, line)) {
        int vertexID;
        if (std::sscanf(line.c_str(),"%d", &vertexID)) {
            newB.push_back(B.at(findVertexIndex(vertexID)));
        }
    }
    
    for (int i = 0; i < n0; i++)
    {
        A.at(i).updateEdgeOrder(&newB);
    }

    return countCrossingsSweep(&A, &newB);
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


std::vector<std::vector<int> > Graph::createAdjacencyMatrix(){
    std::vector<std::vector<int> > adjacencyMatrix;
    adjacencyMatrix.assign(n0, std::vector<int>(n1, 0));
    for (auto edge : edges) {
        int x, y;
        x = edge.first - 1;
        y = edge.second - n0 - 1; 
        adjacencyMatrix[x][y] = 1;
    }
    return adjacencyMatrix;
}


std::vector<Vertex>* Graph::getB() {
    return &B;
}

std::vector<Vertex>* Graph::getA() {
    return &A;
}

int Graph::getNumVertices() {
    return n0 + n1;
}

int Graph::getNumEdges() {
    return numberOfEdges;
}

int Graph::getn0() {
    return n0;
}

int Graph::getn1() {
    return n1;
}
std::vector<std::pair<int, int> > Graph::getEdges() {
    return edges;
}