#include "MedianBary.h"
#include "Barycenter.h"
#include <algorithm>
#include <map>
#include <math.h>
#include <iostream>

MedianBary::MedianBary(Graph* graph) : CrossingMinimizer(graph)
{
}

bool compareMedianBary(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first < b.first;
}

void MedianBary::optimizeOrderMedianBary(std::vector<int>* vertexIndices) {
    /* if (vertexIndices->size() > 4) {
        return;
    } */

    std::vector <std::pair<float, Vertex> > barycenterValues;
    for (int i = 0; i < vertexIndices->size(); i++){
        float barycenterValue = 0;
        for (Vertex* edgeVertex : B.at(vertexIndices->at(i)).getEdges()) {
            barycenterValue += edgeVertex->getVertexID();
        }
        barycenterValue = barycenterValue / B.at(vertexIndices->at(i)).getEdges().size();
        barycenterValues.push_back(std::make_pair(barycenterValue, B.at(vertexIndices->at(i))));
    }

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareMedianBary);

    for (int i = 0; i < barycenterValues.size(); i++)
    {
        B.at(vertexIndices->at(i)) = barycenterValues.at(i).second;
    }
}

void MedianBary::handleSameMedianBaryVal(std::vector<std::pair<float, Vertex> >* MedValues) {
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
        optimizeOrderMedianBary(&indices);
    }
}

void MedianBary::minimizeCrossings() {
   std::vector <std::pair<float, Vertex> > medianValues;
    for (int i = 0; i < B.size(); i++){
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

    std::sort(medianValues.begin(), medianValues.end(), compareMedianBary);

    for (int i = 0; i < medianValues.size(); i++)
    {
        B.at(i) = medianValues.at(i).second;
    }
    
    handleSameMedianBaryVal(&medianValues);

}




MedianBary::~MedianBary()
{
}