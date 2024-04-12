#include "OptimizedBC.h"
#include <algorithm>
#include <map>
#include <iostream>

OptimizedBC::OptimizedBC(Graph* graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName)
{
}

void OptimizedBC::optimizeOrder(std::vector<int>* vertexIndices) {
    if (vertexIndices->size() > 7) {
        return;
    }

    int bestCrossings = graph->countCrossingsSweep(graph->getA(), &B);
    std::vector<Vertex> bestOrder = B;

    while (std::next_permutation(vertexIndices->begin(), vertexIndices->end()))
    {
        std::vector<Vertex> tmpB = B;
        for (int i = 0; i < vertexIndices->size(); i++)
        {
            for (int j = i + 1; j < vertexIndices->size(); j++)
            {
                std::swap(tmpB.at(vertexIndices->at(i)), tmpB.at(vertexIndices->at(j)));
            }
        }
        int newCrossings = graph->countCrossingsSweep(graph->getA(), &tmpB);
        if (newCrossings < bestCrossings) {
            bestCrossings = newCrossings;
            bestOrder = tmpB;
        }        
    }
    B = bestOrder;
}


void OptimizedBC::handleSameBCVal(std::vector<std::pair<float, Vertex> >* bcValues) {
    std::map<float, std::vector<int> > BCmap;
    for (int i = 0; i < bcValues->size(); i++)
    {
        BCmap[bcValues->at(i).first].push_back(i); 
    }

    for (auto& entry : BCmap) {
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

    for (int i = 0; i < barycenterValues.size(); i++)
    {
        B.at(i) = barycenterValues.at(i).second;
    }
    handleSameBCVal(&barycenterValues);
}




OptimizedBC::~OptimizedBC()
{
}
