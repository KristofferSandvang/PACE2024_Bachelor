#include <iostream>
#include "Assignment.h"
#include <queue> 
#include "../Vertex.h"


Assignment::Assignment(Graph* graph) : CrossingMinimizer(graph)
{
    adjacencyMatrix = graph->createAdjacencyMatrix();
    createCrossingMatrix(graph);
    minimizeCrossings();
}


void Assignment::createCrossingMatrix(Graph* graph) {
    int m = graph->getn1();
    int n = graph->getn0();
    crossingMatrix.resize(m, std::vector<int>(m)); 

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            crossingMatrix[i][j] = calculateCost(i, j, n, m);
        }
    }
}

int Assignment::calculateCost(int i, int j, int n, int m) {
    int cost = 0;
    for (int h = 0; h < n; h++) {
        int tempSum = 0;
        for (int c = 0; c < m; c++) {
            for (int d = 0; d < n; d++) {
                if ((c > j && d < h) || (c < j && d > h)) {
                    tempSum++;
                }
            }
        }
        cost += adjacencyMatrix[h][i] * tempSum;
    }
    return cost;
}

void Assignment::minimizeCrossings() {
    // Skal lave reduction trin
    std::unordered_map<int, std::vector<int>> zeroIndices;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> zeroHeap;
    // vertexID reduction
    for (int i = 0; i < crossingMatrix.size(); i++) {
        int minElement = *std::min_element(crossingMatrix[i].begin(),crossingMatrix[i].end());
        for (int j = 0; j < crossingMatrix[i].size(); j++) {
            crossingMatrix[i][j] = crossingMatrix[i][j] - minElement;
        }
    }
    //column reduction
    for (int j = 0; j < crossingMatrix[0].size(); j++) {
        int minElement = crossingMatrix[0][j];
        for (int i = 1; i < crossingMatrix.size(); i++) {
            minElement = std::min(minElement, crossingMatrix[i][j]);
        }
        for (int i = 0; i < crossingMatrix.size(); i++) {
            crossingMatrix[i][j] -= minElement;
        }
    }
    // initalizing hashmaps:
    for (int i = 0; i < crossingMatrix.size(); i++)
    {
        int zeroCount = 0;
        std::vector<int> indices;
        for (int j = 0; j < crossingMatrix[i].size(); j++)
        {
            if (crossingMatrix[i][j] == 0) {
                zeroCount++;
                indices.push_back(j);
            }
        }
        zeroIndices[i] = indices;
        zeroHeap.push({zeroCount, i}); 
    }
    for (const auto& row : crossingMatrix) {
        // Iterate over each element of the row and print it
        for (int element : row) {
            std::cout << element << " ";
        }
        // Print a newline after each row
        std::cout << std::endl;
    }

    std::unordered_map<int, bool> indexAssigned;
    std::vector<std::pair<int, int>> vertexAndPosition;
    // skal på en måde finde ud af hvordan man gør det her xD med stregerne..
    while (!zeroHeap.empty()) {
        // zeroHeap = number of zeros, vertexIndexInB
        auto [zeroCount, vertexIndex] = zeroHeap.top();
        zeroHeap.pop();
        // filtering already used indices.
        std::vector<int> filteredIndices;
        std::copy_if(zeroIndices[vertexIndex].begin(), zeroIndices[vertexIndex].end(), std::back_inserter(filteredIndices), 
            [&](int x) { return !(indexAssigned[x]); });
        if (filteredIndices.empty()) {
            std::cout << "UHOH!" << std::endl;
        }
        vertexAndPosition.emplace_back(vertexIndex, filteredIndices[0]);
        indexAssigned[filteredIndices[0]] = true;
    }
    //updating B based on the new Positions
    std::vector<Vertex> tmpB;
    tmpB.resize(B.size());
    for (auto vertexAndPos : vertexAndPosition)
    {
        tmpB[vertexAndPos.second] = B[vertexAndPos.first];
    }
    B = tmpB;
}

Assignment::~Assignment()
{

}
