#include "OptimizedBC.h"
#include <algorithm>
#include <iostream>

OptimizedBC::OptimizedBC(Graph* graph) : CrossingMinimizer(graph)
{
}

void OptimizedBC::optimizeOrder(std::vector<int>* vertexIndices) {
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


void OptimizedBC::handleSameBCVal(std::map<float, std::vector<int> >* BCmap) {
    for (auto& entry : *BCmap) {
        std::vector<int>& indices = entry.second;
        if (indices.size() == 1) {
            continue;
        }
        optimizeOrder(&indices);
    }
}


bool compareBCVALS(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void OptimizedBC::minimizeCrossings() {
    //std::vector<Vertex> B = *graph->getB();
    std::vector <std::pair<float, Vertex> > barycenterValues;
    for (int i = 0; i < B.size(); i++)
    {
        float barycenterValue = 0;
        for (Vertex* edgeVertex : B.at(i).getEdges()) {
            barycenterValue += edgeVertex->getVertexID();
        }
        barycenterValue = barycenterValue / B.at(i).getEdges().size();
        barycenterValues.push_back(std::make_pair(barycenterValue, B.at(i)));
    }

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareBCVALS);
    std::map<float, std::vector<int> > BCmap;

    for (int i = 0; i < barycenterValues.size(); i++)
    {
        B.at(i) = barycenterValues.at(i).second;
        BCmap[barycenterValues.at(i).first].push_back(i);
    }
    handleSameBCVal(&BCmap);
}




OptimizedBC::~OptimizedBC()
{
}
