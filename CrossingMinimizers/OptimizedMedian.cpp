#include "OptimizedMedian.h"
#include <algorithm>
#include <map>
#include <math.h>
#include <iostream>

OptimizedMedian::OptimizedMedian(Graph* graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName)
{
    B = graph->getB();
}
void OptimizedMedian::optimizeOrder(std::vector<int>* vertexIndices) {
    if (vertexIndices->size() > 6) {
        return;
    }

    int bestCrossings = graph->countCrossingsSweep(graph->getA(), B);
    std::vector<Vertex>* bestOrder = B;

    while (std::next_permutation(vertexIndices->begin(), vertexIndices->end()))
    {
        std::vector<Vertex>* tmpB = B;
        for (int i = 0; i < vertexIndices->size(); i++)
        {
            for (int j = i + 1; j < vertexIndices->size(); j++)
            {
                std::swap(tmpB->at(vertexIndices->at(i)), tmpB->at(vertexIndices->at(j)));
            }
        }
        int newCrossings = graph->countCrossingsSweep(graph->getA(), tmpB);
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
        B->at(i) = MedValues->at(i).second;
        MedMap[MedValues->at(i).first].push_back(i); 
    }

    for (auto& entry : MedMap) {
        std::vector<int>* indices = &entry.second;
        if (indices->size() == 1) {
            continue;
        }
        optimizeOrder(indices);
    }
}

bool compareMEDIAN(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

void OptimizedMedian::minimizeCrossings() {
    std::vector <std::pair<float, Vertex> > medianValues;
    medianValues.reserve(B->size());
    for (int i = 0; i < B->size(); i++){
        std::vector<int> edgeIDs;
        edgeIDs.reserve(B->at(i).getEdges().size());
        for (Vertex* edgeVertex : B->at(i).getEdges()) {
            edgeIDs.emplace_back(edgeVertex->getVertexID());
        }
        std::sort(edgeIDs.begin(), edgeIDs.end());
        float medianValue = 0;
        //da rulez
        if (edgeIDs.empty()) {
            medianValue = 0;
        }
        if (edgeIDs.size() % 2 == 0){
            // if even
            medianValue = edgeIDs[edgeIDs.size()/2];
        } else {
            // if odd
            medianValue = edgeIDs[floor(edgeIDs.size())/2];
        }
        
        medianValues.push_back(std::make_pair(medianValue, B->at(i)));
    }

    std::sort(medianValues.begin(), medianValues.end(), compareMEDIAN);

    for (int i = 0; i < medianValues.size(); i++)
    {
        B->at(i) = medianValues.at(i).second;
    }
    
    handleSameMedianVal(&medianValues);

    writeSolution(B);
}




OptimizedMedian::~OptimizedMedian()
{
}