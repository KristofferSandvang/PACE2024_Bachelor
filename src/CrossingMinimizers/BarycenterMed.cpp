#include "BarycenterMed.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <math.h>

BarycenterMed::BarycenterMed(Graph* graph) : CrossingMinimizer(graph)
{
}
bool compareBCMEDVALS(const std::pair<float, Vertex>& a, const std::pair<float, Vertex>& b) {
    return a.first > b.first;
}

void BarycenterMed::optimizeOrderBCMED(std::vector<int>* vertexIndices) {
    /* if (vertexIndices->size() > 4) {
        return;
    } */
    std::vector <std::pair<float, Vertex> > medianValues;
    for (int i = 0; i < vertexIndices->size(); i++){
        std::vector<int> edgeIDs;
        for (Vertex* edgeVertex : B.at(vertexIndices->at(i)).getEdges()) {
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

        medianValues.push_back(std::make_pair(medianValue, B.at(vertexIndices->at(i))));

    }
    std::sort(medianValues.begin(), medianValues.end(), compareBCMEDVALS);
    for (int i = 0; i < medianValues.size(); i++)
        {
            B.at(vertexIndices->at(i)) = medianValues.at(i).second;
        }
}


void BarycenterMed::handleSameBCMEDVal(std::vector<std::pair<float, Vertex> >* bcValues) {
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
        optimizeOrderBCMED(&indices);
    }
}

void BarycenterMed::minimizeCrossings() {
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

    std::sort(barycenterValues.begin(), barycenterValues.end(), compareBCMEDVALS);

    for (int i = 0; i < barycenterValues.size(); i++)
    {
        B.at(i) = barycenterValues.at(i).second;
    }
    handleSameBCMEDVal(&barycenterValues);
}




BarycenterMed::~BarycenterMed()
{
}
