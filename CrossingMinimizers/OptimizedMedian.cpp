#include "OptimizedMedian.h"
#include <algorithm>
#include <map>
#include <math.h>
#include <iostream>

OptimizedMedian::OptimizedMedian(Graph* graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName)
{
}
void OptimizedMedian::optimizeOrder(std::vector<int>* vertexIndices) {
    if (vertexIndices->size() > 4) {
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

void OptimizedMedian::handleSameMedianVal(std::vector<std::pair<float, Vertex> >* MedValues) {
    std::map<float, std::vector<int> > MedMap;
    for (int i = 0; i < MedValues->size(); i++)
    {
        MedMap[MedValues->at(i).first].push_back(i); 
    }

    for (auto& entry : MedMap) {
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
        std::vector<int> edgeIDs;
        for (Vertex* edgeVertex : B.at(i).getEdges()) {
            edgeIDs.push_back(edgeVertex->getVertexID());
        }
        std::sort(edgeIDs.begin(), edgeIDs.end());
        float medianValue = 0;
        //da rulez
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

    for (int i = 0; i < medianValues.size(); i++)
    {
        B.at(i) = medianValues.at(i).second;
    }
    
    handleSameMedianVal(&medianValues);

}




OptimizedMedian::~OptimizedMedian()
{
}