#include "Median.h"
#include <algorithm>
#include <math.h>
#include <iostream>

Median::Median(Graph* graph, std::string solutionFileName) : CrossingMinimizer(graph, solutionFileName)
{
    
}

bool compareMedian(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void Median::minimizeCrossings() {
    std::vector<Vertex> B = *graph->getB();
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

    std::sort(medianValues.begin(), medianValues.end(), compareMedian);

    for (int i = 0; i < medianValues.size(); i++)
    {
        B.at(i) = medianValues.at(i).second;
    }

    writeSolution(&B);
}




Median::~Median()
{
}