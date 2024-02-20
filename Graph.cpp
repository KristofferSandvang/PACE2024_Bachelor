#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm> 
#include <utility>
#include <stdexcept>

// Constructor 
Graph::Graph(std::ifstream& inputFile, std::string solutionFileName) {
    Graph::solutionFileName = SOLUTION_PATH + solutionFileName + ".sol";

    std::string line;

    while (std::getline(inputFile, line))
    {
        if (line[0] == 'c') {
            continue;
        }
        if (line.substr(0, 5) == "p ocr") {            
            std::sscanf(line.c_str(),"p ocr %d %d %d", &n0, &n1, &numberOfEdges);
            
            // Skal måske laves til en funktion for sig?
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
    
        int x, y;
        if (std::sscanf(line.c_str(), "%d %d", &x, &y) == 2)
        {
            A.at(x - 1).addEdge(Vertex(y));
            B.at(y - n0 - 1).addEdge(Vertex(x));
        }
    
    }
}

// Destructor 
Graph::~Graph() {
    return;
}

// Write the current graph as a solution
void Graph::writeSolution() {
    std::ofstream solutionFile(solutionFileName);
    if (!solutionFile.is_open()) {
        std::cout << "Unable to write to " << solutionFileName << std::endl;
        return;
    }
    for (auto vertex: B) {
        solutionFile << vertex.toString() << std::endl;
    }

    solutionFile.close();
    return;
};

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

int Graph::countCrossings() {
    int crossings = 0;
    for (int i = 0; i < n1; i++)
    {
        Vertex currentVertex = B.at(i);
        for (Vertex endOfEdge : currentVertex.getEdges()) {
            // If the edge is a straghtline from either the start or end of B,
            // we can skip it, as it will not have any crossings.
            if (i == 0 && endOfEdge.getVertexID() == 0 || 
                i == n1 - 1 && endOfEdge.getVertexID() == n0 ) {
                    continue;
            }
            
            for (int j = i + 1; j < n1; j++)
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

void Graph::switchVertices(int v1ID, int v2ID) {
    if (v1ID < n0 || v2ID < n0) {
        throw std::runtime_error("Vertices must be both be in the B graph");
    }
    try {
        int v1_index = Graph::findVertexIndex(v1ID);
        int v2_index = Graph::findVertexIndex(v2ID);
        
        Vertex tmp = Graph::B.at(v1_index);
        Graph::B.at(v1_index) = Graph::B.at(v2_index);
        Graph::B.at(v2_index) = tmp;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return;
    }
}

void Graph::minimizeNumberOfCrossings() {
    //Crossing number matrix
    std::vector<std::vector<int>> crossingNumberMatrix = calculateCrossingNumberMatrix();
    for (int i = 0; i < n1; i++) {
            for (int j = i + 1; j < n1; j++) {
                int curCrossings = crossingNumberMatrix[i][j];
                switchVertices(B.at(i).getVertexID(), B.at(j).getVertexID());
                crossingNumberMatrix = calculateCrossingNumberMatrix();
                int newCrossings = crossingNumberMatrix[i][j];
                if (newCrossings > curCrossings) {
                    curCrossings = newCrossings;
                } else {
                    switchVertices(B.at(i).getVertexID(), B.at(j).getVertexID());
                    crossingNumberMatrix = calculateCrossingNumberMatrix();
                }
            }
        }
}

std::vector<std::vector<int>> Graph::calculateCrossingNumberMatrix() {
    std::vector<std::vector<int>> crossingNumberMatrix(n1, std::vector<int>(n1, 0));
    // Calculate the number of crossings for each pair of vertices
    for (int i = 0; i < n1; i++) {
        for (int j = i + 1; j < n1; j++) {
            int crossings = 0;
            for (Vertex v1 : B.at(i).getEdges()) {
                for (Vertex v2 : B.at(j).getEdges()) {
                    if (v1.getVertexID() < v2.getVertexID()) {
                        crossings++;
                    }
                }
            }
            crossingNumberMatrix[i][j] = crossings;
            crossingNumberMatrix[j][i] = crossings;
        }
    }
    /* for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            std::cout << crossingNumberMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    } */
    
    return crossingNumberMatrix;
}