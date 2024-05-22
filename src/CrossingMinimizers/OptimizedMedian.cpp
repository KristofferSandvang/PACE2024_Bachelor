#include "OptimizedMedian.h"
#include "Utils.h"
#include <algorithm>
#include <map>
#include <math.h>
#include <iostream>
#include <chrono>
#include <csignal>

extern volatile sig_atomic_t flag;
extern std::chrono::steady_clock::time_point start;
extern int timeLimit;

OptimizedMedian::OptimizedMedian(Graph* graph) : CrossingMinimizer(graph)
{
}

void OptimizedMedian::optimizeOrder(std::vector<int>* vertexIndices) {
    if (vertexIndices->size() > 8) {
        return;
    }
    std::vector<Vertex> tmpB;
    for (int index : *vertexIndices) {
        tmpB.push_back(B.at(index));
    }
    std::vector<Vertex> bestOrder = tmpB;
    bool zeroCrossings = false;
    int bestCrossings = graph->countCrossingsSweep(graph->getA(), &tmpB);
    if (bestCrossings == 0) {
        zeroCrossings = true;
    }
    while (std::next_permutation(tmpB.begin(), tmpB.end()) && !zeroCrossings)
    {
        if (flag || !timeRemaining(start, timeLimit - 20)) return;  // Check for signal or time limit
        int newCrossings = graph->countCrossingsSweep(graph->getA(), &tmpB);
        if (newCrossings < bestCrossings) {
            bestCrossings = newCrossings;
            bestOrder = tmpB;
            if (bestCrossings == 0) {
                break;
            }
        }        
    }
    for (int i = 0; i < vertexIndices->size(); i++)
    {
        B.at(vertexIndices->at(i)) = bestOrder.at(i);
    }
}

void OptimizedMedian::handleSameMedianVal(std::map<float, std::vector<int> >* MedMap) {
    for (auto& entry : *MedMap) {
        if (flag || !timeRemaining(start, timeLimit - 20)) return;  // Check for signal or time limit
        std::vector<int>& indices = entry.second;
        if (indices.size() == 1) {
            continue;
        }
        optimizeOrder(&indices);
    }
}

bool compareMedianOptimized(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void OptimizedMedian::minimizeCrossings() {
   std::vector <std::pair<float, Vertex> > medianValues;
    for (int i = 0; i < B.size(); i++){
        if (flag || !timeRemaining(start, timeLimit - 20)) return;  // Check for signal or time limit
        std::vector<int> edgeIDs;
        for (Vertex* edgeVertex : B.at(i).getEdges()) {
            edgeIDs.push_back(edgeVertex->getVertexID());
        }
        std::sort(edgeIDs.begin(), edgeIDs.end());
        float medianValue = 0;

        if (edgeIDs.empty()) {
            medianValue = 0;
        }
        else if (edgeIDs.size() % 2){
            // if odd
            medianValue = edgeIDs[floor(edgeIDs.size())/2];
        } else {
            // if even
            medianValue = edgeIDs[edgeIDs.size()/2];
        }
        
        medianValues.push_back(std::make_pair(medianValue, B.at(i)));
    }

    std::sort(medianValues.begin(), medianValues.end(), compareMedianOptimized);
    std::map<float, std::vector<int> > MedMap;

    for (int i = 0; i < medianValues.size(); i++)
    {
        if (flag || !timeRemaining(start, timeLimit - 20)) return;  // Check for signal or time limit
        B.at(i) = medianValues.at(i).second;
        MedMap[medianValues.at(i).first].push_back(i);
    }
    
    handleSameMedianVal(&MedMap);
}

OptimizedMedian::~OptimizedMedian()
{
}
