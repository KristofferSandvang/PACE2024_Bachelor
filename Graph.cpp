#include "Graph.h"
#include <iostream>

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
            A.at(x - 1).addEdge(y);
            B.at(y - n0 - 1).addEdge(x);
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

int Graph::countCrossings() {
    int crossings = 0;
    for (int a_i = 0; a_i < n0; a_i++)
    {   
        Vertex aVertex = A.at(a_i);        
        for (int b_i = 0; b_i < n1; b_i++)
        {
            Vertex bVertex = B.at(b_i);
            for (int b: aVertex.getEdges()) {
                for (int a: bVertex.getEdges()) {
                    if ((a_i < a && b_i > b) ||  (a_i > a && b_i < b)){
                        crossings++;
                    }
                }
            }
        }
        
    }
    std::cout << crossings << std::endl;
    return crossings;
}
/*In this corrected version, we iterate over all pairs of vertices in A. 
For each pair of vertices, we then iterate over all pairs of edges from those vertices. 
If the edges cross, we increment the crossings counter. 
An edge from A[a_i] to B[b_i] crosses an edge from A[a_j] to B[b_j] if a_i < a_j and b_i > b_j or a_i > a_j and b_i < b_j.*/
/* int Graph::countCrossings() {
    int crossings = 0;
    for (int a_i = 0; a_i < n0; a_i++) {
        for (int a_j = a_i + 1; a_j < n0; a_j++) {
            for (int b_i: A.at(a_i).getEdges()) {
                for (int b_j: A.at(a_j).getEdges()) {
                    if ((b_i < b_j && a_i > a_j) || (b_i > b_j && a_i < a_j)) {
                        crossings++;
                    }
                }
            }
        }
    }
    std::cout << crossings << std::endl;
    return crossings;
} */