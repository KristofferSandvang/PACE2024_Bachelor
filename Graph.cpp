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
        A.reserve(n0);
        B.reserve(n1);
        int x, y;
        if (std::sscanf(line.c_str(), "%d %d", &x, &y) == 2)
        {
            B.at(y - n0 - 1).addEdge(&A.at(x - 1));
            A.at(x - 1).addEdge(&B.at(y - n0 - 1));
        }
    }

    for (int i = 0; i < n0; i++)
    {   
        std::cout << "ID = " << A.at(i).getVertexID() << " Edges = [ ";
        for (int j = 0; j < A.at(i).getEdges().size(); j++) {
                std::cout << A.at(i).getEdges().at(j)->getVertexID() << ", ";
        }
        std::cout << "]" <<std::endl;
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

int Graph::countCrossingsSweep(std::vector<Vertex>* A, std::vector<Vertex>* B) {
    int crossings = 0;
    std::vector<int> UL, LL;
    // last occurence
    std::unordered_map<int, int> last_occurence;
    for (int i = 1; i <= A->size() + B->size(); i++) {
        last_occurence[i] = -1;
    }

    // main loop 
    int AIndex = 0;
    int BIndex = 0;
    for (int iteration = 1; iteration <= A->size() + B->size() + 1; iteration++) {
        std::cout << "iteration " << iteration << std::endl;
        std::cout << "Aindex = " << AIndex << " BIndex = " << BIndex << std::endl;
        for (const auto& pair : last_occurence) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
        std::cout << std::endl;
        std::cout << "UL of size " << UL.size() << std::endl;
        for (const auto& num : UL) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "LL of size " << LL.size() << std::endl;
        for (const auto& num : LL) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;  
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
            
            std::vector<Vertex*> edges = A->at(AIndex).getEdges();
            for (Vertex* edgeEnd : edges) {
                int endpoint = edgeEnd->getVertexID();
                // Have to search B array to find index of the endpoint, as it can change.
                int endpointX = findVertexByID(B, endpoint);
                std::cout << "endpoint " << endpoint << ", X = " << endpointX << std::endl;
                std::cout << "Aindex = " << AIndex << " val = " << A->at(AIndex).getVertexID() << std::endl;
                if (AIndex <= endpointX && endpointX != -1) {
                    std::cout << "endpoint (" << endpoint << ", " << endpointX << ") was greater or equal to X" << std::endl;
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

            std::vector<Vertex*> edges = B->at(BIndex).getEdges();
            for (Vertex* edgeEnd : edges) {
                int endpoint = edgeEnd->getVertexID();
                if (BIndex + 1 < endpoint) {
                    UL.push_back(endpoint);
                    last_occurence[endpoint] = UL.size() - 1;
                }
            }
            BIndex++;
        }
        std::cout << "===============================================================================" <<std::endl;
    }
    return crossings;
}


int Graph::countCrossingsSweep() {
    return countCrossingsSweep(&A, &B);
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
    // Update directions on edges according to new B
    // meaning we only have to update A
    std::cout << "Before updating edges: " << std::endl;
    for (int i = 0; i < n0; i++)
    {
        std::cout << "ID = " << A.at(i).getVertexID() << " Edges = [ ";
        for (int j = 0; j < A.at(i).getEdges().size(); j++) {
                std::cout << A.at(i).getEdges().at(j)->getVertexID() << ", ";
        }
        std::cout << "]" <<std::endl;
        A.at(i).updateEdgeOrder(&newB);
    }
    std::cout << "======================================================" << std::endl;

    for (int i = 0; i < n0; i++)
    {   
        std::cout << "ID = " << A.at(i).getVertexID() << " Edges = [ ";
        for (int j = 0; j < A.at(i).getEdges().size(); j++) {
                std::cout << A.at(i).getEdges().at(j)->getVertexID() << ", ";
        }
        std::cout << "]" <<std::endl;
    }
    std::cout << "======================================================" << std::endl;

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

std::vector<Vertex>* Graph::getB() {
    return &B;
}

std::vector<Vertex>* Graph::getA() {
    return &A;
}
