#include "OptimizedBCRight.h"
#include <algorithm>
#include <map>
#include <iostream>

OptimizedBCRight::OptimizedBCRight(Graph* graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName)
{

}

void OptimizedBCRight::optimizeOrder(std::vector<int>* vertexIndices) {
    //std::cout << "1Number of same bc val: " << vertexIndices.size() << std::endl;
    // Kigge på forældre knuderne, også den der har den forældre med højst x, skal vi til sidst. 
    // Måske bedre at kigge på den laveste forældre knude?
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


void OptimizedBCRight::handleSameBCVal(std::vector<std::pair<float, Vertex> >* bcValues) {
    std::map<float, std::vector<int> > BCmap;
    for (int i = 0; i < bcValues->size(); i++)
    {
        B.at(i) = bcValues->at(i).second;
        BCmap[bcValues->at(i).first].push_back(i); 
    }

    for (auto& entry : BCmap) {
        std::vector<int>& vertices = entry.second;
        if (vertices.size() == 1) {
            continue;
        }
        optimizeOrder(&vertices);
    }
}


bool compareBCVALSRight(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void OptimizedBCRight::minimizeCrossings() {
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

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareBCVALSRight);
    //sorting the barycenter values and vertices to the right order if the barycenter values are the same
    
    //What this do? Could take a long time on larger graphs
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < barycenterValues.size(); i++) {
            for (int j = i+1; j < barycenterValues.size(); j++) {
                if (barycenterValues.at(j).first == barycenterValues.at(i).first && 
                    barycenterValues.at(j).second.getVertexID() < barycenterValues.at(i).second.getVertexID()) {
                    //std::cout << "Swapped vertices: " << barycenterValues.at(j).second.getVertexID() << " and " << barycenterValues.at(i).second.getVertexID() << std::endl;
                    std::swap(barycenterValues.at(j), barycenterValues.at(i));
                    swapped = true;
                }
            }
        }
    }

    handleSameBCVal(&barycenterValues);

}


OptimizedBCRight::~OptimizedBCRight()
{
}
